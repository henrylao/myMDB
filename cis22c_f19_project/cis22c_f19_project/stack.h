#pragma once
#include "linked_list.h"

template <class T>
class Stack : private LinkedList<T>
{
public:
    Stack();
    virtual ~Stack();
    bool push(const T &newItem);
    bool pop();
    T peek() const;
};

template <class T>
Stack<T>::Stack() : LinkedList() {}

template <class T>
Stack<T>::~Stack()
{
    clear();
}

template <class T>
bool Stack<T>::push(const T &newItem)
{
    return insert(1, newItem);
}

template <class T>
bool Stack<T>::pop()
{
    return remove(1);
}

template <class T>
T Stack<T>::peek() const
{
    return getEntry(1);
}
