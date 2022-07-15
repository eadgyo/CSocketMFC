replacement_java = {
	"long" : {
		"jni": "jlong", 
		"cpp" : "long",
		"conv_cpp": "reinterpret_cast<long>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jlong>(VARIABLE)",
	},
	"boolean" : {
		"jni": "jboolean",
		"cpp" : "bool",
		"conv_cpp": "reinterpret_cast<long>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jlong>(VARIABLE)",
	},
	"int" : {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "reinterpret_cast<int>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	},
	"int[]" : {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "reinterpret_cast<int>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	},
	"int[][]" : {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"float": {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"float[]": {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "reinterpret_cast<int>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	},
	"float[][]": {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "reinterpret_cast<int>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	},
	"char" : {
		"jni": "jchar",
		"cpp": "char",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"char[]" : {
		"jni": "jcharArray",
		"cpp": "char VARIABLE[SIZE_1]",
		"cpp2" : "char*",
		"conv_cpp": "ConvertToCharArray<SIZE_1>(env, VARIABLE)",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"char[][]" : {
		"jni": "jobjectArray",
		"cpp": "char VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "reinterpret_cast<int>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	}
}
