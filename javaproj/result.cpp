

#include <string>
#include <iostream>
#include <stdint.h>

#include "JNITest.h"
#include "helper.h"


static void ConvertTo_T_TEST_1(JNI *env, jobject jobj, T_TEST_1& obj)
{
	jfieldID fieldID;
	fieldID = getObjectFieldId(env, jobj,chaine, C);
	ConvertToCharArrayArray<50,50>(env, env->GetobjectArrayField(env, jobj, fieldID), obj.chaine)fieldID = getObjectFieldId(env, jobj,chaine2, C);
	ConvertToCharArray<50>(env, env->GetcharArrayField(env, jobj, fieldID), obj.chaine2)fieldID = getObjectFieldId(env, jobj,entier1, I);
	static_cast<int>(env->GetintField(env, jobj, fieldID))fieldID = getObjectFieldId(env, jobj,reel1, F);
	static_cast<float>(env->GetfloatField(env, jobj, fieldID))fieldID = getObjectFieldId(env, jobj,tabEntier1, I);
	ConvertToIntArray<20>(env, env->GetintArrayField(env, jobj, fieldID), obj.tabEntier1)fieldID = getObjectFieldId(env, jobj,tabReel1, F);
	ConvertToFloatArrayArray<30,10>(env, env->GetobjectArrayField(env, jobj, fieldID), obj.tabReel1)
}

static void ConvertTo_T_TEST_2(JNI *env, jobject jobj, T_TEST_2& obj)
{
	jfieldID fieldID;
	fieldID = getObjectFieldId(env, jobj,tabEntier2, I);
	ConvertToIntArray<20>(env, env->GetintArrayField(env, jobj, fieldID), obj.tabEntier2)fieldID = getObjectFieldId(env, jobj,tabReel2, F);
	ConvertToFloatArray<30>(env, env->GetfloatArrayField(env, jobj, fieldID), obj.tabReel2)fieldID = getObjectFieldId(env, jobj,entier1, I);
	static_cast<int>(env->GetintField(env, jobj, fieldID))
}

JNIEXPORT void JNICALL Java_Set_Test2
  (JNIEnv *env, jobject self, jobjectArray jtest2)
{
	int test2[20][50];
	ConvertToIntArrayArray<20,50>(env, jtest2, test2);
	Test *_self = getObject<Test>(env, self);
	_self->Set_Test2(test2);
}

JNIEXPORT jint JNICALL Java_Set_Dir
  (JNIEnv *env, jobject self, jcharArray jstr)
{
	char str[100];
	ConvertToCharArray<100>(env, jstr, str);
	Test *_self = getObject<Test>(env, self);
	jint res = static_cast<jint>(_self->Set_Dir(str));
	return res;
}

JNIEXPORT void JNICALL Java_Create_T1
  (JNIEnv *env, jobject self, jobject obj0)
{
	Test *_self = getObject<Test>(env, self);
	_self->Create_T1(t1);
}

JNIEXPORT void JNICALL Java_Create_T2
  (JNIEnv *env, jobject self, jobject obj0)
{
	Test *_self = getObject<Test>(env, self);
	_self->Create_T2(t2);
}

JNIEXPORT void JNICALL Java_Test3
  (JNIEnv *env, jobject self, jobject obj0, jobject obj1)
{
	Test *_self = getObject<Test>(env, self);
	_self->Test3(t1, t2);
}

JNIEXPORT void JNICALL Java_Test1
  (JNIEnv *env, jobject self, jobject obj0)
{
	Test *_self = getObject<Test>(env, self);
	_self->Test1(t1);
}

JNIEXPORT void JNICALL Java_Test2
  (JNIEnv *env, jobject self, jobject obj0)
{
	Test *_self = getObject<Test>(env, self);
	_self->Test2(t2);
}

JNIEXPORT void JNICALL Java_Print_T1
  (JNIEnv *env, jobject self, jobject obj0)
{
	Test *_self = getObject<Test>(env, self);
	_self->Print_T1(t1);
}

JNIEXPORT void JNICALL Java_Print_T2
  (JNIEnv *env, jobject self, jobject obj0)
{
	Test *_self = getObject<Test>(env, self);
	_self->Print_T2(t2);
}

