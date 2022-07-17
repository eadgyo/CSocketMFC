

#include <string>
#include <iostream>
#include <stdint.h>

#include "JNITest.h"
#include "helper.h"
#include "structures.h"
#include "Test.h"

JNIEXPORT jlong JNICALL Java_JNITest_nativeNew
  (JNIEnv *env, jobject self)
{
	Test *test = new Test();
	return reinterpret_cast<jlong>(test);
}



static void ConvertTo_T_TEST_1(JNIEnv *env, jobject jobj, T_TEST_1& obj)
{
	jfieldID fieldID;
	fieldID = getObjectFieldId(env, jobj,"chaine", "[[C");
	ConvertToCharArrayArray<50,50>(env, reinterpret_cast<jobjectArray>(env->GetObjectField(jobj, fieldID)), obj.chaine);
	fieldID = getObjectFieldId(env, jobj,"chaine2", "[C");
	ConvertToCharArray<50>(env, reinterpret_cast<jcharArray>(env->GetObjectField(jobj, fieldID)), obj.chaine2);
	fieldID = getObjectFieldId(env, jobj,"entier1", "I");
	obj.entier1 = static_cast<int>(env->GetIntField(jobj, fieldID));
	fieldID = getObjectFieldId(env, jobj,"reel1", "F");
	obj.reel1 = static_cast<float>(env->GetFloatField(jobj, fieldID));
	fieldID = getObjectFieldId(env, jobj,"tabEntier1", "[I");
	ConvertToIntArray<20>(env, reinterpret_cast<jintArray>(env->GetObjectField(jobj, fieldID)), obj.tabEntier1);
	fieldID = getObjectFieldId(env, jobj,"tabReel1", "[[F");
	ConvertToFloatArrayArray<30,10>(env, reinterpret_cast<jobjectArray>(env->GetObjectField(jobj, fieldID)), obj.tabReel1);

}
static void ConvertFrom_T_TEST_1(JNIEnv *env, T_TEST_1& obj, jobject& jobj)
{
	jfieldID fieldID;
	fieldID = getObjectFieldId(env, jobj,"chaine", "[[C");
	ConvertFromCharArrayArray<50,50>(env, obj.chaine, reinterpret_cast<jobjectArray>(env->GetObjectField(jobj, fieldID)));
	fieldID = getObjectFieldId(env, jobj,"chaine2", "[C");
	ConvertFromCharArray<50>(env, obj.chaine2, reinterpret_cast<jcharArray>(env->GetObjectField(jobj, fieldID)));
	fieldID = getObjectFieldId(env, jobj,"entier1", "I");
	env->SetIntField(jobj, fieldID, static_cast<jint>(obj.entier1));
	fieldID = getObjectFieldId(env, jobj,"reel1", "F");
	env->SetFloatField(jobj, fieldID, static_cast<jfloat>(obj.reel1));
	fieldID = getObjectFieldId(env, jobj,"tabEntier1", "[I");
	ConvertFromIntArray<20>(env, obj.tabEntier1, reinterpret_cast<jintArray>(env->GetObjectField(jobj, fieldID)));
	fieldID = getObjectFieldId(env, jobj,"tabReel1", "[[F");
	ConvertFromFloatArrayArray<30,10>(env, obj.tabReel1, reinterpret_cast<jobjectArray>(env->GetObjectField(jobj, fieldID)));

}

static void ConvertTo_T_TEST_2(JNIEnv *env, jobject jobj, T_TEST_2& obj)
{
	jfieldID fieldID;
	fieldID = getObjectFieldId(env, jobj,"tabEntier2", "[I");
	ConvertToIntArray<20>(env, reinterpret_cast<jintArray>(env->GetObjectField(jobj, fieldID)), obj.tabEntier2);
	fieldID = getObjectFieldId(env, jobj,"tabReel2", "[F");
	ConvertToFloatArray<30>(env, reinterpret_cast<jfloatArray>(env->GetObjectField(jobj, fieldID)), obj.tabReel2);
	fieldID = getObjectFieldId(env, jobj,"entier1", "I");
	obj.entier1 = static_cast<int>(env->GetIntField(jobj, fieldID));

}
static void ConvertFrom_T_TEST_2(JNIEnv *env, T_TEST_2& obj, jobject& jobj)
{
	jfieldID fieldID;
	fieldID = getObjectFieldId(env, jobj,"tabEntier2", "[I");
	ConvertFromIntArray<20>(env, obj.tabEntier2, reinterpret_cast<jintArray>(env->GetObjectField(jobj, fieldID)));
	fieldID = getObjectFieldId(env, jobj,"tabReel2", "[F");
	ConvertFromFloatArray<30>(env, obj.tabReel2, reinterpret_cast<jfloatArray>(env->GetObjectField(jobj, fieldID)));
	fieldID = getObjectFieldId(env, jobj,"entier1", "I");
	env->SetIntField(jobj, fieldID, static_cast<jint>(obj.entier1));

}

JNIEXPORT void JNICALL Java_JNITest_Set_1Test2
  (JNIEnv *env, jobject self, jobjectArray jtest2)
{
	int test2[20][50];
	ConvertToIntArrayArray<20,50>(env, jtest2, test2);
	Test *_self = getObject<Test>(env, self);
	_self->Set_Test2(test2);
}

JNIEXPORT jint JNICALL Java_JNITest_Set_1Dir
  (JNIEnv *env, jobject self, jcharArray jstr)
{
	char str[100];
	ConvertToCharArray<100>(env, jstr, str);
	Test *_self = getObject<Test>(env, self);
	jint res = static_cast<jint>(_self->Set_Dir(str));
	return res;
}

JNIEXPORT void JNICALL Java_JNITest_Create_1T1
  (JNIEnv *env, jobject self, jobject jt1)
{
	T_TEST_1 t1;
	ConvertTo_T_TEST_1(env, jt1, t1);
	Test *_self = getObject<Test>(env, self);
	_self->Create_T1(t1);
}

JNIEXPORT void JNICALL Java_JNITest_Create_1T2
  (JNIEnv *env, jobject self, jobject jt2)
{
	T_TEST_2 t2;
	ConvertTo_T_TEST_2(env, jt2, t2);
	Test *_self = getObject<Test>(env, self);
	_self->Create_T2(t2);
}

JNIEXPORT void JNICALL Java_JNITest_Test3
  (JNIEnv *env, jobject self, jobject jt1, jobject jt2)
{
	T_TEST_1 t1;
	ConvertTo_T_TEST_1(env, jt1, t1);
	T_TEST_2 t2;
	ConvertTo_T_TEST_2(env, jt2, t2);
	Test *_self = getObject<Test>(env, self);
	_self->Test3(t1, t2);
}

JNIEXPORT void JNICALL Java_JNITest_Test1
  (JNIEnv *env, jobject self, jobject jt1)
{
	T_TEST_1 t1;
	ConvertTo_T_TEST_1(env, jt1, t1);
	Test *_self = getObject<Test>(env, self);
	_self->Test1(t1);
}

JNIEXPORT void JNICALL Java_JNITest_Test2
  (JNIEnv *env, jobject self, jobject jt2)
{
	T_TEST_2 t2;
	ConvertTo_T_TEST_2(env, jt2, t2);
	Test *_self = getObject<Test>(env, self);
	_self->Test2(t2);
}

JNIEXPORT void JNICALL Java_JNITest_Print_1T1
  (JNIEnv *env, jobject self, jobject jt1)
{
	T_TEST_1 t1;
	ConvertTo_T_TEST_1(env, jt1, t1);
	Test *_self = getObject<Test>(env, self);
	_self->Print_T1(t1);
}

JNIEXPORT void JNICALL Java_JNITest_Print_1T2
  (JNIEnv *env, jobject self, jobject jt2)
{
	T_TEST_2 t2;
	ConvertTo_T_TEST_2(env, jt2, t2);
	Test *_self = getObject<Test>(env, self);
	_self->Print_T2(t2);
}

