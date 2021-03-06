from dataclasses import replace
from glob import glob
import re
import codecs
import sys
from tokenize import group
import json
import replacement_variable

DEBUG_PRINT = True
variables = {}
functions_dict = {}
replacement_java = replacement_variable.replacement_java
JNIClassName = ""

context = {
	"cppClassVariable": "", 
	"currentVariable" : "null",
	"currentParamIndex" : 0,
	"currentParam": "null",
	"functionParams" : "",
	"functionCore" : "",
	"args": [],
	"return": "void"
}

def add_arg_raw(argcontent):
	if DEBUG_PRINT:
		print("Add arg \"" + argcontent + "\"")
	reg = re.compile("(\w+)\s*(\w+)(.*)")
	regArray = re.compile("\[(\d+)\]")
	m = reg.match(argcontent)
	assert(m != None), "Incorrect arg: \"" + argcontent + "\""
	array = []
	if m.group(3) != None:
		array = regArray.findall(m.group(3))
	add_arg(m.group(1), m.group(2), array)

def add_arg(variableName, variableType, array):
	global context
	
	context["args"] += [{
		"type": variableType,
		"name": variableName,
		"array": array
	}]
	context["currentParamIndex"] += 1

def format_jni(jni, variableName, array = []):
	global context
	if DEBUG_PRINT:
		print("format_jni()->")
		print("JNI=" + jni + ", variable=" + variableName + ", array=" + str(array))
	formattedJNI = ""
	if "VARIABLE" in jni:
		formattedJNI = jni.replace("VARIABLE", variableName)
		i = 1
		for a in array:
			formattedJNI = formattedJNI.replace("SIZE_"+str(i), a)
			i += 1
	else:
		formattedJNI = jni + " " + variableName
	if DEBUG_PRINT:
		print("formattedJNI=" + formattedJNI)
	return formattedJNI


def format_call(function):
	global context
	cppClassVariable = context["cppClassVariable"] 
	if DEBUG_PRINT:
		print("format_call()->")
		print("cppClassVariable=" + cppClassVariable + ", function=" + str(function))
	content = cppClassVariable + " *_self = getObject<" +  cppClassVariable + ">(env, self);\n"
	
	# Prepare return statement
	returnStr = ""
	if function["return"] != "void":
		replacementEntry = get_corresponding_replacement(function["return"])
		content += format_jni(replacementEntry["jni"], "res") + " = "
		returnStr += "return res;\n"
		context["return"] = replacementEntry["jni"]
	else:
		context["return"] = "void" 

	# Create call content
	call_content = "_self->" + function["name"] + "(" 
	arguments = []
	for arg in function["args"]:
		arguments += [arg["name"]]
	call_content += ", ".join(arguments)
	call_content += ")"
	if returnStr != "":
		call_content = format_jni_conv(replacementEntry["conv_jni"], call_content)

	# Create return
	content += call_content + ";\n"
	if DEBUG_PRINT:
		print("content=" + content + " result=" + returnStr)
	return content, returnStr

def format_cpp_conv(cpp_conv, variableName, array=[]):
	global context
	formattedcpp_conv = ""
	if DEBUG_PRINT:
		print("format_cpp_conv()->")
		print("cpp_conv=" + cpp_conv + ", variable=" + variableName + ", array=" + str(array))
	if "VARIABLE" in cpp_conv:
		formattedcpp_conv = cpp_conv.replace("VARIABLE", variableName)
		i = 1
		for a in array:
			formattedcpp_conv = formattedcpp_conv.replace("SIZE_"+str(i), a)
			i += 1
	else:
		formattedcpp_conv = cpp_conv + " " + variableName
	if DEBUG_PRINT:
		print("formattedcpp_conv=" + formattedcpp_conv)
	return formattedcpp_conv

def format_jni_conv(jni_conv, variableName, array=[]):
	global context
	formattedjni_conv = ""
	if DEBUG_PRINT:
		print("format_jni_conv()->")
		print("jni_conv=" + jni_conv + ", variable=" + variableName + ", array=" + str(array))
	if "VARIABLE" in jni_conv:
		formattedjni_conv = jni_conv.replace("VARIABLE", variableName)
		i = 1
		for a in array:
			formattedjni_conv = formattedjni_conv.replace("SIZE_"+str(i), a)
			i += 1
	else:
		formattedjni_conv = jni_conv + " " + variableName
	if DEBUG_PRINT:
		print("formattedjni_conv=" + formattedjni_conv)
	return formattedjni_conv

def format_cpp(cpp, variableName, array = []):
	global context
	formattedCpp = ""
	if DEBUG_PRINT:
		print("format_cpp()->")
		print("cpp=" + cpp + ", variable=" + variableName + ", array=" + str(array))
	if "VARIABLE" in cpp:
		formattedCpp = cpp.replace("VARIABLE", variableName)
		i = 1
		for a in array:
			formattedCpp = formattedCpp.replace("SIZE_"+str(i), a)
			i += 1
	else:
		formattedCpp = cpp + " " + variableName
	if DEBUG_PRINT:
		print("formattedCpp=" + formattedCpp)
	return formattedCpp


def read_variables():
	global variables
	f = open("./variables.json", "r")
	content = f.read()
	variables = json.loads(content)

def read_functions():
	global functions_dict
	f = open("./functions.json", "r")
	content = f.read()
	functions_dict = json.loads(content)


def create_default_content(class_name):
	global JNIClassName
	content = '''

#include <string>
#include <iostream>
#include <stdint.h>

#include "CLASS_NAME.h"
#include "helper.h"
#include "structures.h"
#include "Test.h"

JNIEXPORT jlong JNICALL Java_JNITest_nativeNew
  (JNIEnv *env, jobject self)
{
	Test *test = new Test();
	return reinterpret_cast<jlong>(test);
}



'''
	JNIClassName = class_name
	return content.replace("CLASS_NAME", class_name)

def format_function_name(function):
	return function["name"].replace("_", "_1")

def get_corresponding_replacement(typeName):
	global replacement_java
	if typeName in replacement_java:
		return replacement_java[typeName]
	else:
		return None

def get_corresponding(arg):
	typeName = arg["type"] + "[]" * len(arg["array"])
	return get_corresponding_replacement(typeName)

def create_jvariable_name(arg):
	return "j" + arg["name"]

def format_variable(arg):
	global context

	typeName = arg["type"]
	variableName = arg["name"]
	isArray = arg["isArray"]
	array = arg["array"]
	replacementEntry = get_corresponding(arg)

	if replacementEntry != None:
		context["currentParam"] = create_jvariable_name(arg)
		return format_jni(replacementEntry["jni"], create_jvariable_name(arg), array)
	else:
		context["currentParam"] = "obj" + str(context["currentParamIndex"])
		print(typeName + " Not found in variables dictionary !! Generating default " + "obj" + str(context["currentParamIndex"]))
		return "jobject obj" + str(context["currentParamIndex"])

def format_conversion(arg):
	global context
	typeName = arg["type"]
	variableName = arg["name"]
	isArray = arg["isArray"]
	array = arg["array"]
	print("format_conversion()-> array=" + str(array))
	replacementEntry = get_corresponding(arg)
	
	if replacementEntry != None:
		context["currentVariable"] = variableName
		content = ""
		content = format_cpp(replacementEntry["cpp"], variableName, array)
		if "OUTPUT" in replacementEntry["cpp"]:
			content += " = "
		else:
			content += ";\n" 
		result =  format_cpp_conv(replacementEntry["conv_cpp"], context["currentParam"], array) + ";\n"
		content += result.replace("OUTPUT", variableName)
		return content
	else:
		return ""

def format_conversion_back_jni(arg):
	global context
	typeName = arg["type"]
	variableName = arg["name"]
	isArray = arg["isArray"]
	array = arg["array"]
	print("format_conversion()-> array=" + str(array))
	replacementEntry = get_corresponding(arg)
	
	if replacementEntry != None:
		result =  format_jni_conv(replacementEntry["conv_jni"], variableName, array) + ";\n"
		content = result.replace("OUTPUT", context["currentParam"])
		return content
	else:
		return ""


def reset_context():
	global context
	context["currentVariable"] = "null"
	context["currentParamIndex"] = 0
	context["currentParam"] = "null"
	context["functionParams"] = ""
	context["functionCore"] = ""
	context["args"] = []
	context["return"] = "void"

def create_function_definition(function):
	global context
	global JNIClassName
	content = '''Java_FUNCTION_NAME
  (JNIEnv *env, jobject self'''
	content = content.replace("FUNCTION_NAME", JNIClassName + "_" + format_function_name(function))
	reset_context()
	functionCorePost = ""
	for a in function["args"]:
		context["functionParams"] += ", "
		argcontent = format_variable(a)
		add_arg_raw(argcontent)
		context["functionParams"] += argcontent
		context["functionCore"] += format_conversion(a)
		functionCorePost += format_conversion_back_jni(a)
	contentCall, returnStr = format_call(function)
	context["functionCore"] += contentCall
	context["functionCore"] += functionCorePost
	context["functionCore"] += returnStr

	content = "JNIEXPORT " + context["return"] + " JNICALL " + content

	content += context["functionParams"] + ")\n"
	content += "{\n"
	content += re.sub("\t$", "", re.sub("(^|\n)", "\\1\t", str(context["functionCore"])))
	content += "}\n"

	if DEBUG_PRINT:
		print("create_function_definition()->")
		print("context" + str(context))
		print("content" + content)
	return content	


def format_get_field_env(replacementEntry):
	content = "env->Get"
	if "Array" in replacementEntry["jni"]:
		content += "Object"
		content += "Field(jobj, fieldID)" 
		content = "reinterpret_cast<" + replacementEntry["jni"] + ">(" + content + ")"    
	else:
		content += (replacementEntry["jni"][1:]).capitalize()
		content += "Field(jobj, fieldID)" 
	
	return content

def format_set_field_env(replacementEntry):
	content = "env->Set"
	if "Array" in replacementEntry["jni"]:
		content += "Object"
		content += "Field(jobj, fieldID, VALUE)"  
	else:
		content += (replacementEntry["jni"][1:]).capitalize()
		content += "Field(jobj, fieldID, VALUE)" 
	
	return content

def create_helper_structs_to_cpp(structName):
	global variables
	global replacement_java
	content = "static void ConvertTo_" + structName + "(JNIEnv *env, jobject jobj, " + structName + "& obj)\n{\n"
	structVariables = variables[structName]
	contentCore = "jfieldID fieldID;\n"
	
	# Creating variables conversions in 2 parts (GetField and Convert)
	for v in structVariables:
		structVar = structVariables[v]
		typeName = structVar["variable_type"] + ("[]" * len(structVar["array_content"]))
		replacementEntry = get_corresponding_replacement(typeName)
		variableCPPName = "obj."+ structVar["variable_name"]
		if replacementEntry == None:
			contentCore += "//" + variableCPPName + " off type " + typeName + " not resolved!\n"  
			continue

		# Get Object
		variableJNINamePreparation = "fieldID = getObjectFieldId(env, jobj,\"" + structVar["variable_name"] + "\", \"" + replacementEntry["jvm"] + "\");\n"
		variableJNIName = format_get_field_env(replacementEntry)
		
		contentCore += variableJNINamePreparation
		if "OUTPUT" not in replacementEntry["conv_cpp"]:
			contentCore += variableCPPName + " = "
		contentCore += format_cpp_conv(replacementEntry["conv_cpp"], variableJNIName, structVar["array_content"]).replace("OUTPUT", variableCPPName) + ";\n"

	content += re.sub("\t$", "", re.sub("(^|\n)", "\\1\t", contentCore))
	content += "}\n\n"
	return content

def create_helper_structs_to_jni(structName):
	global variables
	global replacement_java
	content = "static void ConvertFrom_" + structName + "(JNIEnv *env, " + structName + "& obj, jobject& jobj)\n{\n"
	structVariables = variables[structName]
	contentCore = "jfieldID fieldID;\n"
	
	for v in structVariables:
		structVar = structVariables[v]
		typeName = structVar["variable_type"] + ("[]" * len(structVar["array_content"]))
		replacementEntry = get_corresponding_replacement(typeName)
		variableCPPName = "obj."+ structVar["variable_name"]
		if replacementEntry == None:
			contentCore += "//" + variableCPPName + " off type " + typeName + " not resolved!\n"  
			continue

		variableJNINamePreparation = "fieldID = getObjectFieldId(env, jobj,\"" + structVar["variable_name"] + "\", \"" + replacementEntry["jvm"] + "\");\n"
		variableJNIName = format_get_field_env(replacementEntry)
		variableJNINameSetter = format_set_field_env(replacementEntry)

		contentCore += variableJNINamePreparation
		core = format_jni_conv(replacementEntry["conv_jni"], variableCPPName, structVar["array_content"]).replace("OUTPUT", variableJNIName) 

		if "OUTPUT" not in replacementEntry["conv_jni"]:
			contentCore += variableJNINameSetter.replace("VALUE", core) + ";\n"
		else:
			contentCore += core + ";\n"


	content += re.sub("\t$", "", re.sub("(^|\n)", "\\1\t", contentCore))
	content += "}\n\n"
	return content


def create_helper_structs(structName):
	global replacement_java
	global variables
	if structName not in variables:
		print("generate_helper_structs()->")
		print("Error not found " + structName + " in variable")
		return
	
	replacement_java[structName] = {
		"jni": "jobject",
		"cpp": structName,
		"conv_cpp": "ConvertTo_" + structName + "(env, VARIABLE, OUTPUT)",
		"conv_jni": "ConvertFrom_" + structName + "(env, VARIABLE, OUTPUT)",
		"jvm": "L"
	}
	content = "// CONVERT " + structName + " //\n"
	content += create_helper_structs_to_cpp(structName)
	content += create_helper_structs_to_jni(structName)

	return content

	
def main(argv):
	global functions_dict
	global context
	content = create_default_content(argv[1])
	for v in variables:
		content += create_helper_structs(v)
		content += "\n"
	
	context["cppClassVariable"] = argv[2]
	for functionName in functions_dict:
		function = functions_dict[functionName]
		content += create_function_definition(function)
		content += "\n"

	f = open(argv[3], "w")
	f.write(content)
	f.close()

if __name__ == '__main__':
	if len(sys.argv) < 3:
		print("help:\n\tJNIINCLUDE (no .h)\n\tCPP Class Name\n\tcppPath")
	else:
		read_variables()
		read_functions()
		main(sys.argv)