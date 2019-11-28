#ifndef QUEUE_H
#define QUEUE_H
#include "linked_list.h"

template <class T>
class Queue : protected LinkedList<T> {
public:
	Queue() : LinkedList<T>() {}
	~Queue() { LinkedList<T>::~LinkedList(); }
	/** Adds a new entry to the back of this queue.
	@post If the operation was successful, newEntry is at the
	back of the queue.
	@param newEntry The object to be added as a new entry.
	@return True if the addition is successful or false if not. */
	bool enqueue(const T& data) { LinkedList<T>::insert_back(data); return true; }
	/** Removes the front of this queue.
	@post If the operation was successful, the front of the queue
	has been removed.
	@return item removed from the end of the queue */
	T dequeue() { T item_removed = front(); LinkedList<T>::remove_front(); return item_removed; }
	/** Returns the last item of this queue.
	@pre The queue is not empty.
	@post The last item of the queue has been returned, and the
	queue is unchanged.
	@return The last item of the queue. */
	bool is_empty() { return LinkedList<T>::is_empty(); }
	/** Returns the front of this queue.
	@pre The queue is not empty.
	@post The front of the queue has been returned, and the
	queue is unchanged.
	@return The front of the queue. */
	T front() { return LinkedList<T>::get_item(0); }
	/** Returns the end of this queue.
	@pre The queue is not empty.
	@post The front of the queue has been returned, and the
	queue is unchanged.
	@return The front of the queue. */
	T rear() { return LinkedList<T>::get_item(LinkedList<T>::size() - 1 ); }
	/* Returns the size of this queue
	@return An integer value of the queue's size */
	int size() { return LinkedList<T>::size(); }
	/** Delete all items on the queue.
	@post all items are removed from the queue */
	void clear() { return LinkedList<T>::empty(); }
};

#endif // QUEUE_H