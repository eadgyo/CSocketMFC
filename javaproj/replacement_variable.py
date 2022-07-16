#https://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/types.html#wp276
replacement_java = {
	"long" : {
		"jni": "jlong", 
		"cpp" : "long",
		"conv_cpp": "static_cast<long>(VARIABLE)",
		"conv_jni": "static_cast<jlong>(VARIABLE)",
		"jvm": "J"
	},
	"boolean" : {
		"jni": "jboolean",
		"cpp" : "bool",
		"conv_cpp": "static_cast<bool>(VARIABLE)",
		"conv_jni": "static_cast<jboolean>(VARIABLE)",
		"jvm": "Z"
	},
	"int" : {
		"jni": "jint",
		"cpp": "int",
		"conv_cpp": "static_cast<int>(VARIABLE)",
		"conv_jni": "static_cast<jint>(VARIABLE)",
		"jvm": "I"
	},
	"int[]" : {
		"jni": "jintArray",
		"cpp": "int VARIABLE[SIZE_1]",
		"conv_cpp": "ConvertToIntArray<SIZE_1>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "I"
	},
	"int[][]" : {
		"jni": "jobjectArray",
		"cpp": "int VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "ConvertToIntArrayArray<SIZE_1,SIZE_2>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "I"
	},
	"float": {
		"jni": "jfloat",
		"cpp": "float",
		"conv_cpp": "static_cast<float>(VARIABLE)",
		"conv_jni": "static_cast<jfloat>(VARIABLE)",
		"jvm": "F"
	},
	"float[]": {
		"jni": "jfloatArray",
		"cpp": "float VARIABLE[SIZE_1]",
		"conv_cpp": "ConvertToFloatArray<SIZE_1>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "F"
	},
	"float[][]": {
		"jni": "jobjectArray",
		"cpp": "float VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "ConvertToFloatArrayArray<SIZE_1,SIZE_2>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "F"
	},
	"char" : {
		"jni": "jchar",
		"cpp": "char",
		"conv_cpp": "NOT IMPLEMENTED!",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "C"
	},
	"char[]" : {
		"jni": "jcharArray",
		"cpp": "char VARIABLE[SIZE_1]",
		"cpp2" : "char*",
		"conv_cpp": "ConvertToCharArray<SIZE_1>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "C"
	},
	"char[][]" : {
		"jni": "jobjectArray",
		"cpp": "char VARIABLE[SIZE_1][SIZE_2]",
		"conv_cpp": "ConvertToCharArrayArray<SIZE_1,SIZE_2>(env, VARIABLE, OUTPUT)",
		"conv_jni": "NOT IMPLEMENTED!",
		"jvm": "C"
	}
}
