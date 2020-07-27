/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: List.hpp
Purpose: This is implementation for the List.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 7/24/2020
-----------------------------------------------------------------*/

#include "List.h"

template<typename T>
List<T>::List() : pHead(nullptr), pTail(nullptr), mSize(0) {}

template<typename T>
List<T>::~List()
{
    Node* temp = NULL;
    Node* nodeptr = pHead;

    while (nodeptr != pTail)
    {
        temp = nodeptr->pNext;
        delete nodeptr;
        nodeptr = temp;
    }

    delete temp;
}

template<typename T>
void List<T>::push_front(T value)
{
    if (pHead == nullptr)
    {
        pHead = MakeNode(value);
        
        if (pTail == nullptr)
        {
            pTail = pHead;
        }
    }
    else
    {
        Node* pTemp = MakeNode(value);
        pTemp->pNext = pHead;
        pHead->pPrev = pTemp;
        pHead = pTemp;
    }
    
    ++mSize;
}

template<typename T>
void List<T>::push_back(T value)
{
    if (pTail == nullptr)
    {
        pTail = MakeNode(value);

        if (pHead == nullptr)
        {
            pHead = pTail;
        }
    }
    else
    {
        Node* pTemp = MakeNode(value);
        pTail->pNext = pTemp;
        pTemp->pPrev = pTail;
        pTail = pTemp;
    }
    
    ++mSize;
}

template<typename T>
T List<T>::pop_front(void)
{
    T poppedValue = pHead->data;

    if(pHead == pTail)
    {
        pHead = nullptr;
        pTail = nullptr;
    }
    else
    {
        pHead = pHead->pNext;
    }

    --mSize;

    return poppedValue;
}

template<typename T>
T List<T>::pop_back(void)
{
    T poppedValue = pTail->data;

    if (pTail == pHead)
    {
        pTail = nullptr;
        pHead = nullptr;
    }
    else
    {
        pTail = pTail->pPrev;
    }
    
    --mSize;

    return poppedValue;
}

template<typename T>
typename List<T>::Iterator List<T>::begin(void)
{
    return Iterator(pHead);
}

template<typename T>
typename List<T>::Iterator List<T>::end(void)
{
    return Iterator(pTail);
}

//template<typename T>
//List<T>::Iterator List<T>::erase(List<T>::Iterator target)
//{
//}

template<typename T>
T List<T>::back(void)
{
    return pTail->data;
}

template<typename T>
T List<T>::front(void)
{
    return pHead->data;
}

template<typename T>
bool List<T>::empty(void)
{
    if (pHead == nullptr)
    {
        return true;
    }

    return false;
}

template<typename T>
int List<T>::size(void)
{
    return mSize;
}

template <typename T>
List<T>::Iterator::Iterator(typename List<T>::Node* newValue) :nodePtr(newValue) {};

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()//pre++
{
    nodePtr = nodePtr->pNext;

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)//post ++
{
    Iterator temp = *this;

    ++(*this);

    return temp;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--()//pre --
{
    nodePtr = nodePtr->pPrev;

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)//post --
{
    Iterator temp = *this;

    --(*this);

    return temp;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return nodePtr != rhs.nodePtr;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& rhs) const
{
    return nodePtr == rhs.nodePtr;
}

template <typename T>
bool List<T>::Iterator::operator<=(const Iterator& rhs) const
{
    return nodePtr <= rhs.nodePtr;
}

template <typename T>
bool List<T>::Iterator::operator>=(const Iterator& rhs) const
{
    return nodePtr >= rhs.nodePtr;
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& rhs) const
{
    return nodePtr < rhs.nodePtr;
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& rhs) const
{
    return nodePtr > rhs.nodePtr;
}

template <typename T>
typename List<T>::Node& List<T>::Iterator::operator*()
{
    if (nodePtr == nullptr)
    {
        std::string exception = "Value is nullptr.";

        throw exception;
    }

    return nodePtr;
}