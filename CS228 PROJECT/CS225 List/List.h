/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: List.h
Purpose: This is declaration for the List.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 7/24/2020
-----------------------------------------------------------------*/

#pragma once

template<typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* pNext;
        Node* pPrev;
    };

    Node* MakeNode(T data)
    {
        Node* pNewNode = new Node();
        pNewNode->data = data;
        pNewNode->pNext = nullptr;
        pNewNode->pPrev = nullptr;

        return pNewNode;
    }

    Node* MakeNode(T data, Node* next, Node* prev)
    {
        Node* pNewNode = new Node();
        pNewNode->data = data;
        if (next == nullptr)
        {
            pNewNode->pNext = next;
        }
        else
        {
            pNewNode->pNext = new Node();
            pNewNode->pNext->data = next->data;
        }

        pNewNode->pPrev = prev;


        return pNewNode;
    }

public:
    class Iterator
    {
    public:
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator!=(const Iterator& rhs) const;
        bool operator==(const Iterator& rhs) const;
        bool operator<=(const Iterator& rhs) const;
        bool operator>=(const Iterator& rhs) const;
        bool operator<(const Iterator& rhs) const;
        bool operator>(const Iterator& rhs) const;
        T operator*();

    private:
        friend class List<T>;
        Iterator(List<T>::Node* value);
        List<T>::Node* nodePtr;
    };

    List();
    ~List();

    List(const List<T>& rhs); // copy constructor
    List(List<T>&& rhs); // move constructor
    List<T>& operator=(const List<T>& rhs); // copy assignment
    List<T>& operator=(List<T>&& rhs); //move assignment

    void push_front(T value);
    void push_back(T value);

    T pop_front(void);
    T pop_back(void);

    Iterator begin(void);
    Iterator end(void);

    Iterator erase(Iterator target);
    void clear();

    T back(void);
    T front(void);

    bool empty(void);
    int size(void);

private:
    Node* pHead;
    Node* pTail;
    int mSize;
};

#include "List.hpp" //Template list usage