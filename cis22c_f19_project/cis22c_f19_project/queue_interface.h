/* SortedList Interface */

#ifndef _QUEUE_INTERFACE_H
#define _QUEUE_INTERFACE_H

template <typename T>
class QueueInterface {
public:
	/** Adds a new entry to the back of this queue.
	@post If the operation was successful, newEntry is at the
	back of the queue.
	@param newEntry The object to be added as a new entry.
	@return True if the addition is successful or false if not. */
	virtual bool enqueue(const T& t_item) = 0;
	/** Removes the front of this queue.
	@post If the operation was successful, the front of the queue
	has been removed.
	@return item removed from the end of the queue */
	virtual T dequeue() = 0;
	/** Returns the last item of this queue.
	@pre The queue is not empty.
	@post The last item of the queue has been returned, and the
	queue is unchanged.
	@return The last item of the queue. */
	virtual T rear() const = 0;
	/** Returns the front of this queue.
	@pre The queue is not empty.
	@post The front of the queue has been returned, and the
	queue is unchanged.
	@return The front of the queue. */
	virtual T front() const = 0;
	/** Delete all items on the queue.
	@post all items are removed from the queue */
	virtual void empty() = 0;
};

#endif // !
