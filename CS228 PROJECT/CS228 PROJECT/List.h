/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: List.h
Purpose: This is declaration for the List.
Project: CS280
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
        Node* pNewNode = new Node; 
        pNewNode->data = data; 
        pNewNode->pNext = nullptr; 
  
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
        T& operator*();
        Iterator operator+(int offset);
        Iterator operator-(int offset);

    private:
        friend class List<T>;
        Iterator(T* value, int index);
        List<T>::Node nodePtr;

    };

    List();
    ~List();

    List(const List<T>& rhs) = delete;
    List<T>& operator=(const List<T>& rhs) = delete;
    List<T>& operator=(List<T>&& rhs) = delete;

    void push_front(T value);
    void push_back(T value);

    T pop_front(void);
    T pop_back(void);

    Iterator begin(void);
    Iterator end(void);

    Iterator erase(Iterator target);

    T back(void);
    T front(void);

    bool empty(void);
    int size(void);

private:
    Node* pHead;
    Node* pTail;
    int mSize;
};

#include "List.hpp" //template list usage