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
	size_t size() const { return List<T>::getLength(); }
    bool pop();
    T peek() const;
	template <class U>
	friend std::ostream& operator<< (std::ostream &out, const Stack<U>& stack);
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
    return List<T>::insert(0, newItem);
}

template <class T>
bool Stack<T>::pop()
{
    return List<T>::remove(0);
}

template <class T>
T Stack<T>::peek() const
{
    return List<T>::getEntry(0);
}
template <typename T>
std::ostream& operator<< (std::ostream &out, const Stack<T>& stack)
{
	out << "[ ";
	int SIZE = stack.getLength();
	T item = stack.getEntry(0);
	if (SIZE == 1) {
		out << item << " ]\n";
		return out;
	}
	for (int i = 0; i < SIZE - 1; i++) {
		item = stack.getEntry(i);
		out << item;
		out << ", ";
	}
	out << stack.getEntry(SIZE - 1);
	out << " ]";
	return out;
}
#endif // !_STACK_H
