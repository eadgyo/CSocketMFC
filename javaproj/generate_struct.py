import re
import codecs
import sys
import json

DEBUG_PRINT = False

variables = {}
current_struct_name = ""
current_variable_name = ""

def write_variables():
	global variables
	f = open("./variables.json", "w")
	content = json.dumps(variables, indent=4, separators=(',', ': '))
	f.write(content)
	f.close()

def register_variable(struct_name, variable_name, variable_type, other_content, isArray, array_content):
	global variables
	global current_variable_name
	current_variable_name = variable_name
	variables[struct_name][variable_name] = {
		"variable_name" : variable_name,
		"variable_type" : variable_type,
		"other_content" : other_content,
		"isArray" : isArray,
		"array_content" : array_content
	}

def register_variable_dict(key, value):
	global variables
	global current_struct_name
	global current_variable_name
	variables[current_struct_name][current_variable_name][key] = value

def create_variable(variable : re.match):
	global current_struct_name
	typeVariable = variable.group(1)
	nameVariable = variable.group(2)
	otherVariable = variable.group(3)
	arrayReg = re.compile("\[(\d+)\]")
	contentVariable = "\t" + typeVariable + " " + nameVariable
	isArray = False
	array_content = []
	if re.match("\[\d+\]+", otherVariable.strip()):
		isArray = True
		arrayIter = arrayReg.finditer(otherVariable)
		for arr in arrayIter:
			number = arr.group(1)
			array_content += [number]
			contentVariable += "[]"

		contentVariable += " = new " + typeVariable + otherVariable

	contentVariable += ";\n"
	print("\t" +  nameVariable + " --> " + typeVariable + (" with array of size " + otherVariable if (isArray) else ""))
	if (DEBUG_PRINT):
		print("\t  > " + contentVariable.replace("\n", "").replace("\t", ""))

	register_variable(current_struct_name, nameVariable, typeVariable, otherVariable, isArray, array_content)
	register_variable_dict("fullContent", contentVariable)
	register_variable_dict("fullContent", contentVariable)
	return contentVariable

def register_struct(name):
	global current_struct_name
	current_struct_name = name
	variables[name] = {}

def main(argv):
	f = open(argv[1], "r")
	content = f.read()
	structReg = re.compile("struct (\w+) {([\s\S]*?)}")
	variableReg = re.compile("(\w+) (\w+)(.*?);")

	structIter = structReg.finditer(content)
	for st in structIter:
		name = st.group(1)
		
		register_struct(name)
		print ("==>" + name)
		contentStruct = "class " + name + "{\n";

		varIter = variableReg.finditer(st.group(2))
		for variable in varIter:
			contentStruct += create_variable(variable)

		contentStruct += "}"
		f2 = open("./structs/" + name + ".java", "w")
		f2.write(contentStruct)
		f.close()

if __name__ == '__main__':
	main(sys.argv)
	write_variables()
