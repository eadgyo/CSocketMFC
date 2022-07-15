from array import array
import re
import codecs
import sys
from tokenize import group
import json

DEBUG_PRINT_ARGUMENT = False
DEBUG_PRINT = True
variables = {}

functions_dict = {}

current_function = ""

def read_variables():
	global variables
	f = open("./variables.json", "r")
	content = f.read()
	variables = json.loads(content)

def write_functions():
	global functions_dict
	f = open("./functions.json", "w")
	content = json.dumps(functions_dict, indent=4, separators=(',', ': '))
	f.write(content)
	f.close()

def create_default_content(class_name, library_name):
	default_content = '''
import java.io.File;
import java.lang.reflect.Field ;

public final class JNINAME
{
	static {

		try
        {
			System.loadLibrary("JNILIBRARY");
        }
        catch ( UnsatisfiedLinkError e )
        {
            System.err.println ( "Native code library failed to load.\\n" + e ) ;
            System.exit ( 1 ) ; 
        }
	}
	
	/**
	 * Pointer to the c++ object
	 */
	private long nativeObjectPointer;
	
	/**
	 * Constructor
	 * @return
	 */
	private native long nativeNew();
	
	public JNINAME()
	{
		nativeObjectPointer = nativeNew();
	}

'''
	return default_content.replace("JNINAME", class_name).replace("JNILIBRARY", library_name)

def register_variable(arg: re.match):
	global functions_dict
	global current_function
	arrayReg = re.compile("\[(\d*)\]")
	variable_entry = {
		"type": arg.group(1),
		"reference": (True if (arg.group(2)) else False),
		"name": arg.group(3),
		"isArray": re.match("\[\d+\]+", arg.group(4)) != None,
		"array": arrayReg.findall(arg.group(4))
	}
	functions_dict[current_function]["args"] += [variable_entry]
	return variable_entry

def create_argument(arg: re.match):
	entry = register_variable(arg)
	typeVar =  arg.group(1)
	name = arg.group(3)
	contentArg = typeVar + " " + name + ("[]" * len(entry["array"]))
	return contentArg

def register_function(fun : re.match):
	global functions_dict
	global current_function
	current_function = fun.group(2)
	functions_dict[current_function] = {
		"name" : current_function,
		"return": fun.group(1),
		"argsFull": fun.group(3),
		"args": []
	}

def create_function(fun: re.match):
	register_function(fun)
	contentFunc = "public native " + fun.group(1) + " " + fun.group(2) + "(";
	
	# Create regex
	arguments = fun.group(3)
	regArg = re.compile("(\w+)\s*(&)?\s*(\w+)(.*?)\s*(,|$)")
	argIter = regArg.finditer(arguments)
	
	# Create arguments
	argumentsArr = []
	for arg in argIter:
		(print("\tCreating argument from: " + arg.group(0)) if DEBUG_PRINT_ARGUMENT else "")
		argumentsArr += [create_argument(arg)]
	contentFunc += ",".join(argumentsArr)
	contentFunc += ");"
	
	# End
	print("Creating function: " + contentFunc)
	return contentFunc

def main(argv):
	f = open(argv[3], "r")
	content = f.read()
	
	# Create regex
	funcReg = re.compile("__jniexport\s+(\w+)\s+(\w+)\(([\s\S]*?)\);")
	funcIter = funcReg.finditer(content)
	
	# Create function
	contentNative = create_default_content(argv[1], argv[2])
	for fun in funcIter:
		contentNative += "\t" + create_function(fun) + "\n\n"
	if len(argv) > 4 and argv[4] == "y":
		contentNative += "}"
	
	# Write content
	f2 = open(argv[1] + ".java", "w")
	f2.write(contentNative)
	f2.close()
	print("Writing to file " + argv[1] + ".java ...")

if __name__ == '__main__':
	if len(sys.argv) == 1:
		print("help:\n\tJNINAME\n\tLIBRARYNAME\n\tpath\n\tadd { at end: yes/empty")
	else:
		read_variables()
		main(sys.argv)
		write_functions()