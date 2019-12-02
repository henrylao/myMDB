/* SortedList Interface */

#ifndef _STACK_INTERFACE_H
#define _STACK_INTERFACE_H

template <typename T>
class StackInterface {
public:
	/** Sees whether this stack is empty.
	@return True if the stack is empty, or false if not. */
	virtual bool is_empty() const = 0;
	/** Adds a new entry to the top of this stack.
	@post If the operation was successful, newEntry is at the top of the stack.
	@param newEntry The object to be added as a new entry.
	@return True if the addition is successful or false if not. */
	virtual bool push(const T& newEntry) = 0;
	/** Removes the top of this stack.
	@post If the operation was successful, the top of the stack
	has been removed.
	@return item removed from the top of the stack */
	virtual T pop() = 0;
	/** Returns the top of this stack.
	@pre The stack is not empty.
	@post The top of the stack has been returned, and
	the stack is unchanged.
	@return The top of the stack. */
	virtual T peek() const = 0;
	/** Delete all items on the stack.
	@post all items are removed from the stack */
	virtual void clear() = 0;
};

#endif // !
