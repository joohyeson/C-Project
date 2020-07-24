#include "List.h"

template<typename T>
List<T>::List()
{
    pHead = pTail = new Node<T>();
}

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

}

template<typename T>
void List<T>::push_back(T value)
{
    if (pTail == nullptr)
    {
        pTail = MakeNode(value);
    }
    else
    {
        Node* pTemp = MakeNode(value);
        pTail->pNext = pTemp;
        pTail = pTail->pNext;
    }
}

template<typename T>
T List<T>::pop_front(void)
{

}
template<typename T>
T List<T>::pop_back(void)
{

}

template<typename T>
List<T>::Iterator List<T>::begin(void)
{
    return Iterator(&data[0], 0);
}

template<typename T>
List<T>::Iterator List<T>::end(void)
{
    return Iterator(&data[mSize], mSize);
}

template<typename T>
List<T>::Iterator List<T>::erase(List<T>::Iterator target)
{

}

template<typename T>
T List<T>::back(void)
{
    return pTail.value;
}

template<typename T>
T List<T>::front(void)
{
    return pHead.value;
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
List<T>::Iterator::Iterator(T* newValue, int newIndex) : value(newValue), index(newIndex) {}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()//pre++
{
    ++index;
    ++(value);

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)//post ++
{
    Iterator temp = *this;
    nodePtr = nodePtr->pNext;

    return temp;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--()//pre --
{
    Iterator temp = *this;
    nodePtr = nodePtr->pPrev;

    return temp;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)//post --
{
    --index;
    --(value);

    return Iterator(value, index);
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return (index != rhs.index);
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (index == rhs.index);
}

template <typename T>
bool List<T>::Iterator::operator<=(const Iterator& rhs) const
{
    return (index <= rhs.index);
}

template <typename T>
bool List<T>::Iterator::operator>=(const Iterator& rhs) const
{
    return (index >= rhs.index);
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& rhs) const
{
    return (index < rhs.index);
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& rhs) const
{
    return (index > rhs.index);
}

template <typename T>
T& List<T>::Iterator::operator*()
{
    if (value == nullptr)
    {
        std::string exception = "Value is nullptr.";

        throw exception;
    }

    return *value;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(int offset)
{
    index += offset;
    (*value) += offset;

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(int offset)
{
    index -= offset;
    (*value) -= offset;

    return *this;
}