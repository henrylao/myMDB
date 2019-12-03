#pragma once
#include "linked_list.h"
#include "list.h"
#ifndef _STACK_H
#define _STACK_H


template <class T>
class Stack : private List<T>
{
public:
    Stack();
    virtual ~Stack();
    bool push(const T &newItem);
	size_t size() { return List<T>::getLength(); }
    bool pop();
    T peek() const;
};

template <class T>
Stack<T>::Stack() : List<T>() {}

template <class T>
Stack<T>::~Stack()
{
	List<T>::clear();
}

template <class T>
bool Stack<T>::push(const T &newItem)
{
    return List<T>::insert(1, newItem);
}

template <class T>
bool Stack<T>::pop()
{
    return List<T>::remove(1);
}

template <class T>
T Stack<T>::peek() const
{
    return List<T>::getEntry(1);
}
#endif // !_STACK_H
