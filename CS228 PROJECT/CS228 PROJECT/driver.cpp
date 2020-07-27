/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: driver.cpp
Purpose: This is driver source file to test 'List' class.
Project: CS225
Author: Juhye Son, Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include <iostream> //std::cout, std::endl
#include "List.h"

void test1() //Test 'push_back', 'pop_back', 'back', 'size', 'empty'
{
    List<int> list;

    for (int i = 1; i <= 20; i++)
    {
        list.push_back(i);
        std::cout << "Current Size: " << list.size() << std::endl;
        std::cout << "Current Tail: " << list.back() << std::endl;
    }

    for (int i = 1; i <= 20; i++)
    {
        list.pop_back();
        std::cout << "Current Size: " << list.size() << std::endl;
        std::cout << "Current Tail: " << list.back() << std::endl;
    }

    if(list.empty() == true)
    {
        std::cout << "Current List is empty." << std::endl;
    }
    else
    {
        std::cout << "Current List is not empty." << std::endl;
    }
}

void test2() //Test 'push_front', 'pop_front', 'front', 'size', 'empty'
{
    List<int> list;

    for (int i = 1; i <= 20; i++)
    {
        list.push_front(i);
        std::cout << "Current Size: " << list.size() << std::endl;
        std::cout << "Current Head: " << list.front() << std::endl;
    }

    for (int i = 1; i <= 20; i++)
    {
        list.pop_front();
        std::cout << "Current Size: " << list.size() << std::endl;
        std::cout << "Current Head: " << list.front() << std::endl;
    }

    if(list.empty() == true)
    {
        std::cout << "Current List is empty." << std::endl;
    }
    else
    {
        std::cout << "Current List is not empty." << std::endl;
    }
}

void test3()
{
    std::cout << "TEST#3" << std::endl;
    
    List<int> list;

    for (int i = 1; i <= 20; i++)
    {
        list.push_back(i);
    }

    List<int>::Iterator sum = list.begin();
    
    for (int i = 1; i <= 20; i++)
    {
        sum++;
       // std::cout << "Current Iterator: " << *sum.front() << std::endl;
    }
}
//
//void test4()
//{
//    List<int> list;
//
//    for (int i = 1; i <= 20; i++)
//    {
//        list.push_back(i);
//    }
//}
//
//void test5()
//{
//    List<int> list;
//
//    for (int i = 1; i <= 10; i++)
//    {
//        list.push_back(i);
//    }
//}
//
//void test6()
//{
//    List<char> charList;
//
//    for (char i = 'a'; i <= 'z'; i++)
//    {
//        charList.push_back(i);
//    }
//
//    List<double> doubleList;
//
//    for (int i = 1; i <= 10; i++)
//    {
//        doubleList.push_back(i / 10.0);
//    }
//}
//
//void test7()
//{
//    try
//    {
//        List<int> vec;
//
//        for (int i = 1; i <= 20; i++)
//        {
//            vec.push_back(i);
//        }
//    }
//    catch (std::string exception)
//    {
//        std::cout << "Exception thrown : " << exception << std::endl;
//    }
//}

int main(int argc, char** argv)
{
    int testNum = -1;

    if (argc > 1)
    {
        testNum = atoi(argv[1]);
    }

    if (testNum == -1)
    {
        test1();
        test2();
        test3();
       // test4();
       // test5();
       // test6();
       // test7();
        //test8();
        //test9();
    }
    else
    {
        typedef void(*Test)(void);
        Test Tests[] = { test1, test2, test3,/* test4, test5, test6, test7, test8, test9*/};

        Tests[testNum - 1]();
    }
}