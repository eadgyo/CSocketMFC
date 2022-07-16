#include <jni.h>
#include <iostream>

#pragma once

static char * ConvertStrToCharArray(JNIEnv *env, jstring jstr)
{
    char *nativeString = const_cast<char*>(env->GetStringUTFChars(jstr, 0));
    return nativeString;
}   

template<int size1>
static void ConvertToCharArray(JNIEnv *env, jcharArray jcharArray, char (& strBuf)[size1])
{
    jboolean isCopy;
	jchar *jchars = const_cast<jchar*>(env->GetCharArrayElements(jcharArray, &isCopy));
	jstring str = env->NewString(jchars, reinterpret_cast<jsize>(size1));
	env->GetStringUTFRegion(str, static_cast<jsize>(0), static_cast<jsize>(size1), strBuf);
}

template<int size1, int size2>
static void ConvertToCharArrayArray(JNIEnv *env, jobjectArray jcharchar, char (& new_chars)[size1][size2])
{
	int size = static_cast<int>(env->GetArrayLength(jcharchar));
	if (size != size1)
	{
		std::cout << "ArrayLength does not match, received " << size << " asked " << size1 << std::endl;
	}

	for (int i = 0; i < size; i++)
	{
		jcharArray jcharArrayTmp = reinterpret_cast<jcharArray>(env->GetObjectArrayElement(jcharchar, static_cast<jsize>(i)));
		ConvertToCharArray<size2>(env, jcharArrayTmp, new_chars[i]);
	}
}

template<int size1>
static void ConvertToIntArray(JNIEnv *env, jintArray jintArray, int (& intBuf)[size1])
{
    jboolean isCopy;
	int size = env->GetArrayLength(jintArray);
	if (size != size1)
	{
		std::cout << "ArrayLength does not match, received " << size << " asked " << size1 << std::endl;
	}
	jint *jints = const_cast<jint*>(env->GetIntArrayElements(jintArray, &isCopy));
	for (int i = 0; i < size1; i++)
	{
		intBuf[i] = static_cast<int>(jints[i]);
	}
}

template<int size1, int size2>
static void ConvertToIntArrayArray(JNIEnv *env, jobjectArray jintint, int (& new_ints)[size1][size2])
{
	int size = static_cast<int>(env->GetArrayLength(jintint));
	if (size != size1)
	{
		std::cout << "ArrayLength does not match, received " << size << " asked " << size1 << std::endl;
	}
	for (int i = 0; i < size; i++)
	{
		jintArray jintArrayTmp = reinterpret_cast<jfloatArray>(env->GetObjectArrayElement(jintint, static_cast<jsize>(i)));
		ConvertToIntArray<size2>(env, jintArrayTmp, new_ints[i]);
	}
}


template<int size1>
static void ConvertToFloatArray(JNIEnv *env, jfloatArray jfloatArray, float (& floatBuf)[size1])
{
	jboolean isCopy;
	int size = env->GetArrayLength(jfloatArray);
	if (size != size1)
	{
		std::cout << "ArrayLength does not match, received " << size << " asked " << size1 << std::endl;
	}
	jfloat *jfloats = const_cast<jfloat*>(env->GetFloatArrayElements(jfloatArray, &isCopy));
	for (int i = 0; i < size1; i++)
	{
		floatBuf[i] = static_cast<float>(jfloats[i]);
	}
}

template<int size1, int size2>
static void ConvertToFloatArrayArray(JNIEnv *env, jobjectArray jfloatfloat, float (& new_floats)[size1][size2])
{
	int size = static_cast<int>(env->GetArrayLength(jfloatfloat));
	if (size != size1)
	{
		std::cout << "ArrayLength does not match, received " << size << " asked " << size1 << std::endl;
	}

	for (int i = 0; i < size; i++)
	{
		jfloatArray jfloatArrayTmp = reinterpret_cast<jfloatArray>(env->GetObjectArrayElement(jfloatfloat, static_cast<jsize>(i)));
		ConvertToFloatArray<size2>(env, jfloatArrayTmp, new_floats[i]);
	}
}



template<class T>
static T *getObject(JNIEnv *env, jobject self)
{
	jclass cls = env->GetObjectClass(self);
	if (!cls)
		env->FatalError("GetObjectClass failed");

	jfieldID nativeObjectPointerID = env->GetFieldID(cls, "nativeObjectPointer", "J");
	if (!nativeObjectPointerID)
		env->FatalError("GetFieldID failed");

	jlong nativeObjectPointer = env->GetLongField(self, nativeObjectPointerID);
	return reinterpret_cast<T *>(nativeObjectPointer);
}


static jfieldID getObjectFieldId(JNIEnv *env, jobject self, const char* fieldName, const char* fieldType)
{
	jclass cls = env->GetObjectClass(self);
	if (!cls)
		env->FatalError("GetObjectClass failed");

	jfieldID fieldID = env->GetFieldID(cls, fieldName, fieldType);
	if (!fieldID)
		env->FatalError("GetFieldID failed");
	return fieldID;
}