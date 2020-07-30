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
#include <iomanip>
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
    List<int> listA;

    for (int i = 1; i <= NUM_OF_NODES; i++)
    {
        listA.push_back(i);
    }

    std::cout << "\n#MOVE CONSTRUCTOR" << std::endl;
    List<int> listB = std::move(listA); // move ctor

    for (auto node : listB)
    {
        std::cout << "Value : " << node << std::endl;
        std::cout << "Value : " << &node << std::endl;
    }

    std::cout << "\n#MOVE ASSIGNMENT OPERATOR" << std::endl;
    List<int> listC;
    listC = std::move(listB); //move assign

    for (auto node : listC)
    {
        std::cout << "Value : " << node << std::endl;
        std::cout << "Value : " << &node << std::endl;
    }

    std::cout << "\n#COPY CONSTRUCTOR" << std::endl;
    List<int> listE(listC); //copy ctor

    for (auto node : listE)
    {
        std::cout << "Value : " << node << std::endl;
        std::cout << "Value : " << &node << std::endl;
    }

    std::cout << "\n#COPY ASSIGNMENT OPERATOR" << std::endl;
    List<int> listD;
    listD = listE; //copy assign

    for (auto node : listD)
    {
        std::cout << "Value : " << node << std::endl;
        std::cout << "Value : " << &node << std::endl;
    }
}

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
        test4();
        test5();
        test6();
        test7();
        test8();
    }
    else
    {
        typedef void(*Test)(void);
        Test Tests[] = { test1, test2, test3, test4, test5, test6, test7, test8 };

        Tests[testNum - 1]();
    }
}