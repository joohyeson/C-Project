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
    clear();
}

//copy constructor(deep copy)
template<typename T>
List<T>::List(const List<T>& rhs)
{
    deep_copy(rhs);
}

//move constructor 
template<typename T>
List<T>::List(List<T>&& rhs)
{
    pHead = rhs.pHead;
    pTail = rhs.pTail;
    mSize = rhs.mSize;

    rhs.pHead = nullptr;
    rhs.pTail = nullptr;
    rhs.mSize = 0;
}

//copy assignment operator(deep copy)
template<typename T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
    clear();
    deep_copy(rhs);

    return *this;
}

//move assignmnet operator
template<typename T>
List<T>& List<T>::operator=(List<T>&& rhs)
{
    if (this != &rhs)
    {
        clear();

        pHead = rhs.pHead;
        pTail = rhs.pTail;
        mSize = rhs.mSize;

        rhs.pHead = nullptr;
        rhs.pTail = nullptr;
        rhs.mSize = 0;
    }

    return *this;
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
    Node* pTemp = pHead;

    if (pHead == pTail)
    {
        delete pHead;
        pHead = nullptr;
        pTail = nullptr;
    }
    else
    {
        pHead = pTemp->pNext;
        delete pTemp;
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

template<typename T>
typename List<T>::Iterator List<T>::erase(typename List<T>::Iterator target)
{
    auto current = begin().nodePtr;

    while (current != target.nodePtr)
    {
        current = current->pNext;
    }

    auto after = current->pNext;

    if (current->pPrev != nullptr)
    {
        current->pPrev->pNext = after;
    }
    else //current target is Head.
    {
        if (after != nullptr)
        {
            pHead = after;
        }
        else
        {
            pHead->pNext = nullptr;
            pHead = nullptr;
        }
    }

    if (after != nullptr)
    {
        after->pPrev = current->pPrev;
    }
    else //current target is Tail.
    {
        pTail = nullptr;
        pTail->pPrev = nullptr;
    }

    delete current;
    current = nullptr;

    mSize--;

    return after;
}

template<typename T>
void List<T>::clear()
{
    Node* current = pHead;
    Node* next;

    while (current != nullptr)
    {
        next = current->pNext;
        delete current;
        --mSize;
        current = next;
    }

    pHead = nullptr;
    pTail = nullptr;
}

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

template<typename T>
inline void List<T>::deep_copy(const List<T>& rhs)
{
    if (rhs.pHead != nullptr)
    {
        pHead = MakeNode(rhs.pHead->data);

        Node* pTemp = pHead;
        Node* rhsTemp = rhs.pHead->pNext;

        while (rhsTemp != nullptr)
        {
            pTemp->pNext = MakeNode(rhsTemp->data, nullptr, pTemp);
            pTemp = pTemp->pNext;
            rhsTemp = rhsTemp->pNext;
        }

        pTail = pTemp;
    }

    mSize = rhs.mSize;
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
T List<T>::Iterator::operator*()
{
    if (nodePtr == nullptr)
    {
        std::string exception = "Value is nullptr.";

        throw exception;
    }

    return nodePtr->data;
}