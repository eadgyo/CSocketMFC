#pragma once
#include <iostream>
#include <string.h>

struct T_TEST_1 {
    char chaine[50][50];
    char chaine2[50];
    int entier1;
    float reel1;
    int tabEntier1[20];
    float tabReel1[30][10];
};

struct T_TEST_2 {
    int tabEntier2[20];
    float tabReel2[30];
    int entier1;
};


static void print_T1(const T_TEST_1 t1)
{
    for (int i = 0; i < 50; i++)
    {
        std::cout << "chaine[" << i << "] = " << t1.chaine[i] << std::endl;
    }
    std::cout << "chaine2 = " << t1.chaine2 << std::endl;
    std::cout << "entier1 = " << t1.entier1 << std::endl;
    std::cout << "reel1 = " << t1.reel1 << std::endl;

    for (int i = 0; i < 20; i++)
    {
        std::cout << "tabEntier1["<<i<<"] = " << t1.tabEntier1[i] << std::endl;
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << "tabReel1[" << i << "][" << j <<"] = " << t1.tabReel1[i][j] << std::endl;
        }
    }
}


static void print_T2(const T_TEST_2 t2)
{
    for (int i = 0; i < 20; i++)
    {
        std::cout << "tabEntier2[" << i << "] = " << t2.tabEntier2[i] << std::endl;
    }
    for (int i = 0; i < 30; i++)
    {
        std::cout << "tabReel2["<< i <<"] = " << t2.tabReel2[i] << std::endl;
    }
    std::cout << "entier1 = " << t2.entier1 << std::endl;
}