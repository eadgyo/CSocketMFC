#pragma once
#include "structures.h"
#include <string.h>
#include <iostream>
#include "debug.h"
#define __jniexport 

class Test
{
private:
    /* data */
public:
    Test(/* args */);
    ~Test();

    __jniexport void Create_T1(T_TEST_1& t1);

    __jniexport void Create_T2(T_TEST_2& t2);

    __jniexport void Test3(T_TEST_1& t1, 
                            T_TEST_2& t2);

    __jniexport void Test1(T_TEST_1& t1);
   
    __jniexport void Test2(T_TEST_2& t2);

    __jniexport void Print_T1(T_TEST_1& t1);

    __jniexport void Print_T2(T_TEST_2& t2);
};