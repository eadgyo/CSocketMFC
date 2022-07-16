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
		"conv_cpp": "static_cast<bool>(VARIABLE)",
		"conv_jni": "static_cast<jboolean>(VARIABLE)",
	},
	"int" : {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "reinterpret_cast<int>(VARIABLE)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	},
	"int[]" : {
		"jni": "jintArray",
		"cpp": "int VARIABLE[SIZE_1]",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"int[][]" : {
		"jni": "jobjectArray",
		"cpp": "int VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"float": {
		"jni": "jfloat",
		"cpp": "float",
		"conv_cpp": "static_cast<float>(VARIABLE)",
		"conv_jni": "static_cast<jfloat>(VARIABLE)",
	},
	"float[]": {
		"jni": "jfloatArray",
		"cpp": "float VARIABLE[SIZE_1]",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"float[][]": {
		"jni": "jobjectArray",
		"cpp": "float VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
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
		"conv_cpp": "ConvertToCharArray<SIZE_1>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
	},
	"char[][]" : {
		"jni": "jobjectArray",
		"cpp": "char VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "ConvertToCharArrayArray<SIZE_1,SIZE_2>(env, VARIABLE, OUTPUT)",
		"conv_jni": "reinterpret_cast<jint>(VARIABLE)",
	}
}
