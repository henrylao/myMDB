#include "singly_linked_list.h"
#include "stack_interface.h"

#ifndef _STACK_H
#define _STACK_H

template <typename T>
class Stack : public LinkedList<T>, public StackInterface<T> {
	LinkedList<T>* m_list;
public:
	~Stack<T>();
	Stack<T>();
	/** Sees whether this stack is empty.
	@return True if the stack is empty, or false if not. */
	bool is_empty() const;
	/** Adds a new entry to the top of this stack.
	@post If the operation was successful, newEntry is at the top of the stack.
	@param newEntry The object to be added as a new entry.
	@return True if the addition is successful or false if not. */
	T push(const T& newEntry);
	/** Removes the top of this stack.
	@post If the operation was successful, the top of the stack
	has been removed.
	@return item removed from the top of the stack */
	T pop();
	/** Returns the top of this stack.
	@pre The stack is not empty.
	@post The top of the stack has been returned, and
	the stack is unchanged.
	@return The top of the stack. */
	T peek() const;
	void clear();
	// return the size of the stack
	int get_size() const;
	// display the current stack
	void display();
};

template<typename T>
void Stack<T>::display() {
	this->m_list->display();
}
template<typename T>
int Stack<T>::get_size() const {
	return this->m_list->get_length();
}
template<typename T>
Stack<T>::~Stack() {
	this->m_list->~LinkedList();
}	// end dtor
template<typename T>
Stack<T>::Stack() {
	this->m_list = new LinkedList<T>(0);
}	// end ctor
template<typename T>
bool Stack<T>::is_empty() const {
	return this->m_list->is_empty();
}	// end is_empty
template<typename T>
T Stack<T>::peek() const{ 
	return this->m_list->get_last();
}	// end peek
template<typename T>
T Stack<T>::pop()  {
	return this->m_list->pop();
}	// end pop
template<typename T>
T Stack<T>::push(const T& t_item) {
	return this->m_list->push(t_item);
}	// end push
template<typename T>
void Stack<T>::clear() {
	return this->m_list->clear();
}
#endif 
#pragma once
