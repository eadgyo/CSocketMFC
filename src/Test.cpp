#include "Test.h"

Test::Test(/* args */)
{
}

Test::~Test()
{
}

int Test::Set_Dir(char str[])
{
    std::cout << str << std::endl;
    return 1;
}

void Test::Create_T1(T_TEST_1& t1)
{
    for (int i = 0; i < 50; i++)
    {
        strcpy(t1.chaine[i], "TEST " + i);
    }
    strcpy(t1.chaine2, "TEST CHAINE2\n");
    t1.entier1 = 1;
    t1.reel1 = 1.1f;
    for (int i = 0; i < 20; i++)
    {
        t1.tabEntier1[i] = i;
    }
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            t1.tabReel1[i][j] = i * 10 + j + 1000;
        }
    }
}

void Create_T2(T_TEST_2& t2)
{
    for (int i = 0; i < 20; i++)
    {
        t2.tabEntier2[i] = i + 100;
    }
    for (int i = 0; i < 30; i++)
    {
        t2.tabReel2[i] = i *10;
    }
    t2.entier1 = 505;
}

void Test::Test3(T_TEST_1& t1, T_TEST_2& t2)
{
    LOG_INFO("Modifying t1..");
    t1.entier1 = -3;

    LOG_INFO("Modifying t2..");
    t2.entier1 = -2;
}

void Test::Test1(T_TEST_1& t1)
{
    Print_T1(t1);

    LOG_INFO("Modifying t1..");
    strcpy(t1.chaine[20], "Modification de la chaine");
    strcpy(t1.chaine[14], "Test chaine");
    strcpy(t1.chaine2, "Test nouvelle chaine");
    t1.entier1 = 30;
    t1.reel1 = 10.0f;
    t1.tabEntier1[10] = 15;
    t1.tabReel1[10][1] = 20.0f;
    t1.tabReel1[13][3] = 550.0f;

    Print_T1(t1);
}

void Test::Test2(T_TEST_2& t2)
{
    print_T2(t2);
    
    LOG_INFO("Modifying t2..");
    t2.tabEntier2[10] = 20;
    t2.tabEntier2[13] = 45;
    t2.tabReel2[1] = 50;
    t2.tabReel2[30] = 505;
    t2.entier1 = -1;

    print_T2(t2);
}

void Test::Print_T1_SIMPLE(T_TEST_1& t1)
{
    std::cout << t1.entier1 << std::endl;
    
}

void Test::Print_T1(T_TEST_1& t1)
{
    std::cout << "START T1" << std::endl;
    /*std::cout << "chaine2 = " << t1.chaine2 << std::endl;
    std::cout << "entier1 = " << t1.entier1 << std::endl;
    std::cout << "reel1 = " << t1.reel1 << std::endl;
    for (int i = 0; i < 20; i++)
    {
        std::cout << "tabEntier1["<<i<<"] = " << t1.tabEntier1[i] << std::endl;
    }*/
    print_T1(t1);
    std::cout << "END T1" << std::endl;
}

void Test::Print_T2(T_TEST_2& t2)
{
    std::cout << "START T2" << std::endl;
    print_T2(t2);
    std::cout << "END T2" << std::endl;
}