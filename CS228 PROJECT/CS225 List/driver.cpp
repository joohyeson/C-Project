/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: driver.cpp
Purpose: This is a test driver source file to test 'List' class.
Project: CS225
Author: Juhye Son, Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <crtdbg.h> // debug memory tracking

#include <iostream> //std::cout, std::endl
#include <iomanip> //std::setw
#include "List.h"

constexpr int NUM_OF_NODES = 5;

void test1() //Test 'push_back', 'pop_back', 'back', 'size', 'empty'
{
    std::cout << "Test#1 - 'push_back', 'pop_back', 'back', 'size', 'empty', 'erase'" << std::endl;

    List<int> list;

    std::cout << "\n#PUSH_BACK" << std::endl;

    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        list.push_back(i);
        std::cout << "Size: " << list.size() << ", " << "Tail: " << list.back() << std::endl;
    }

    std::cout << "\n#POP_BACK" << std::endl;

    for (int i = 1; i <= NUM_OF_NODES - 1; i++)
    {
        list.pop_back();
        std::cout << "Size: " << list.size() << ", " << "Tail: " << list.back() << std::endl;
    }

    std::cout << "\n#ERASE LAST VALUE" << std::endl;

    List<int>::Iterator begin = list.begin();
    list.erase(begin);
    std::cout << "Size: " << list.size() << std::endl;

    if (list.empty() == true)
    {
        std::cout << "List is empty." << std::endl;
    }
    else
    {
        std::cout << "List is not empty." << std::endl;
    }
}

void test2() //Test 'push_front', 'pop_front', 'front', 'size', 'empty'
{
    std::cout << "\nTest#2 - 'push_front', 'pop_front', 'front', 'size', 'empty'" << std::endl;

    List<int> list;
    std::cout << "\n#PUSH_FRONT" << std::endl;
    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        list.push_front(i);
        std::cout << "Size: " << list.size() << ", " << "Head: " << list.front() << std::endl;
    }

    std::cout << "\n#POP_FRONT" << std::endl;
    for (int i = 1; i <= NUM_OF_NODES - 1; i++)
    {
        list.pop_front();
        std::cout << "Size: " << list.size() << ", " << "Head: " << list.front() << std::endl;
    }

    std::cout << "\n#One more POP_BACK" << std::endl;
    list.pop_front();
    std::cout << "Size: " << list.size() << std::endl;

    if (list.empty() == true)
    {
        std::cout << "List is empty." << std::endl;
    }
    else
    {
        std::cout << "List is not empty." << std::endl;
    }
}

void test3()
{
    std::cout << "\nTEST#3 'pre_increment++', 'post_increment++'" << std::endl;

    List<int> list;

    for (int i = 0; i <= NUM_OF_NODES; i++)
    {
        list.push_back(i);
    }

    List<int>::Iterator sum = list.begin();
    List<int>::Iterator preInc = list.begin();
    List<int>::Iterator postInc = list.begin();

    std::cout << "\n#PRE_INCREMENT ++" << std::endl;

    for (int i = 0; i < NUM_OF_NODES; i++)
    {
        preInc = ++sum;

        std::cout << "Current: " << std::setw(2) << *sum << ", Pre: " << std::setw(2) << *preInc << std::endl;
    }

    std::cout << "\n#POST_INCREMNET ++" << std::endl;

    sum = list.begin();

    for (int i = 0; i < NUM_OF_NODES; i++)
    {
        postInc = sum++;

        std::cout << "Current: " << std::setw(2) << *sum << ", Post: " << std::setw(2) << *postInc << std::endl;
    }
}

void test4()
{
    std::cout << "\nTEST#4 'pre_decrement--', 'post_decrement--'" << std::endl;

    List<int> list;

    for (int i = 0; i <= 5; i++)
    {
        list.push_back(i);
    }

    List<int>::Iterator sum = list.end();
    List<int>::Iterator predec = list.end();
    List<int>::Iterator postdec = list.end();

    std::cout << "\n#PRE_DECREMENT --" << std::endl;

    for (int i = NUM_OF_NODES; i > 0; i--)
    {
        predec = --sum;

        std::cout << "Current: " << std::setw(2) << *sum << ", Pre: " << std::setw(2) << *predec << std::endl;
    }

    std::cout << "\n#POST_DECREMENT --" << std::endl;
    sum = list.end();

    for (int i = NUM_OF_NODES; i > 0; i--)
    {
        postdec = sum--;

        std::cout << "Current: " << std::setw(2) << *sum << ", Post: " << std::setw(2) << *postdec << std::endl;
    }
}

void test5()
{
    std::cout << "\nTEST#5 operator ==, !=" << std::endl;

    List<int> list;

    list.push_back(0);
    list.push_back(1);

    List<int>::Iterator leftValue = list.begin();
    List<int>::Iterator rightValue = list.begin();

    std::cout << "\n#OPERATOR ==" << std::endl;

    std::cout << *leftValue << "  VS  " << *rightValue << std::endl;

    if (leftValue == rightValue)
    {
        std::cout << "They have same value" << std::endl;
    }
    else
    {
        std::cout << "They don't have same value" << std::endl;
    }

    rightValue++;

    std::cout << "\n#OPERATOR !=" << std::endl;

    std::cout << *leftValue << "  VS  " << *rightValue << std::endl;

    if (leftValue == rightValue)
    {
        std::cout << "They have same value" << std::endl;
    }
    else
    {
        std::cout << "They don't have same value" << std::endl;
    }

}

void test6()
{
    std::cout << "\nTEST#6 operator <=, <" << std::endl;

    List<int> list;

    list.push_back(0);
    list.push_back(1);

    List<int>::Iterator leftValue = list.begin();
    List<int>::Iterator rightValue = list.begin();

    std::cout << "\n#OPERATOR <=" << std::endl;

    std::cout << (*leftValue) << "  VS  " << *rightValue << std::endl;

    if (leftValue <= rightValue)
    {
        std::cout << "Right value is bigger than left value or same" << std::endl;
    }
    else
    {
        std::cout << "Left value is bigger than right value" << std::endl;
    }

    rightValue++;

    std::cout << "\n#OPERATOR <" << std::endl;

    std::cout << (*leftValue) << "  VS  " << (*rightValue) << std::endl;

    if (leftValue < rightValue)
    {
        std::cout << "Right value is bigger than left value" << std::endl;
    }
    else
    {
        std::cout << "Left value is bigger than right value" << std::endl;
    }

}

void test7()
{
    std::cout << "\nTEST#7 operator <=, <" << std::endl;

    List<int> list;

    list.push_back(0);
    list.push_back(1);

    List<int>::Iterator leftValue = list.begin();
    List<int>::Iterator rightValue = list.begin();

    std::cout << "\n#OPERATOR <=" << std::endl;

    std::cout << (*leftValue) << "  VS  " << (*rightValue) << std::endl;

    if (leftValue >= rightValue)
    {
        std::cout << " Left value is bigger than right value" << std::endl;
    }
    else
    {
        std::cout << "Right value is bigger than left value or same" << std::endl;
    }

    rightValue++;

    std::cout << "\n#OPERATOR <" << std::endl;

    std::cout << (*leftValue) << "  VS  " << (*rightValue) << std::endl;

    if (leftValue > rightValue)
    {
        std::cout << "Left value is bigger than right value" << std::endl;
    }
    else
    {
        std::cout << "Right value is bigger than left value" << std::endl;
    }
}

void test8()
{

    std::cout << "\nTEST#8 Rule of 5" << std::endl;
    List<int> listA;

    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        listA.push_back(i);
    }

    std::cout << "\n#MOVE CONSTRUCTOR" << std::endl;
    List<int> listB = std::move(listA); // move ctor

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listA)
    {
        std::cout << "Value : " << node << std::endl;
    }
    std::cout << "Address ListA :" << &listA << std::endl;

    std::cout << "\n#ListB" << std::endl;
    for (auto node : listB)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "Address ListB:" << &listB << std::endl;

    std::cout << "\n#MOVE ASSIGNMENT OPERATOR" << std::endl;
    List<int> listC;
    listC = std::move(listB); //move assign

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listB)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "Address ListA :" << &listB << std::endl;

    std::cout << "\n#ListB" << std::endl;
    for (auto node : listC)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "Address ListB :" << &listC << std::endl;

    std::cout << "\n#COPY CONSTRUCTOR" << std::endl;
    List<int> listE(listC); //copy ctor

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listC)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "Address ListA :" << &listC << std::endl;

    std::cout << "\n#ListB" << std::endl;
    for (auto node : listE)
    {
        std::cout << "Value : " << node << std::endl;
    }
    std::cout << "Address ListB :" << &listB << std::endl;

    std::cout << "\n#COPY ASSIGNMENT OPERATOR" << std::endl;
    List<int> listD;
    listD = listE; //copy assign

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listE)
    {
        std::cout << "Value : " << node << std::endl;
    }
    std::cout << "Address ListA :" << &listE << std::endl;
    std::cout << "\n#ListB" << std::endl;
    for (auto node : listD)
    {
        std::cout << "Value : " << node << std::endl;
    }
    std::cout << "Address ListB :" << &listD << std::endl;
}

void test9()
{
    std::cout << "\nTEST#9 COPY CONSTRUCTOR DEEP COPY" << std::endl;
    List<int> listA;

    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        listA.push_back(i);
    }

    std::cout << "\n#COPY CONSTRUCTOR" << std::endl;
    List<int> listB(listA); //copy ctor

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listA)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "\n#ListB" << std::endl;
    for (auto node : listB)
    {
        std::cout << "Value : " << node << std::endl;
    }

    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        listB.push_back(i);
    }

    std::cout << "\n===========AFTER PUSH_BACK TO LISTB===========" << std::endl;

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listA)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "\n#ListB" << std::endl;
    for (auto node : listB)
    {
        std::cout << "Value : " << node << std::endl;
    }

}

void test10()
{
    std::cout << "\nTEST#10 CLEAR" << std::endl;

    List<int> listA;

    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        listA.push_back(i);
    }

    std::cout << "\n#ListA" << std::endl;
    for (auto node : listA)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "Size : " << listA.size() << std::endl;

    listA.clear();
    std::cout << "\n===========AFTER CLEAR===========" << std::endl;

    std::cout << "Size : " << listA.size() << std::endl;
}

void test11()
{
    std::cout << "\nTEST#11 RAII TEST" << std::endl;
    
    List<int> listA(5);

    std::cout << "\n#ListA" << std::endl;
    
    for (auto node : listA)
    {
        std::cout << "Value : " << node << std::endl;
    }

    std::cout << "Value : " << listA.back()<< std::endl;

    std::cout << "Size : " << listA.size() << std::endl;
}

int main(int argc, char** argv)
{
#if defined(_DEBUG)
    {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    }
#endif

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
        test4();
        test5();
        test6();
        test7();
        test8();
        test9();
        test10();
        test11();
    }
    else
    {
        typedef void(*Test)(void);
        Test Tests[] = { test1, test2, test3, test4, test5, test6, test7, test8, test9, test10, test11 };

        Tests[testNum - 1]();
    }
}