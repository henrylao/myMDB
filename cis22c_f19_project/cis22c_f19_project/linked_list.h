
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "head_node.h"

template <class T>
class LinkedList {

private:
	HeadNode<T>				__list;
	LinkNode<T>*			__nav;

protected:
	/* Helper function for traversing through the list
	@return*/
	LinkNode<T>* navigate(int index) const;

public:
	//----------------------------------------------------
	// Constructor and Destructor Section
	//----------------------------------------------------

	LinkedList();
	LinkedList(const LinkedList<T>& copy);
	virtual				~LinkedList();
	
	//----------------------------------------------------
	// Mutators Section
	//----------------------------------------------------
	
	/** Appends a new item to the front of the list
	@pre There is sufficient memory to be allocated for node creation
	@post The item inserted is the first item on the list
	@return True if removal is successful, or false if not. */
	void				insert_front(T t_item);
	/** Prepends a new item to the back of the list
	@pre There is sufficient memory to be allocated for node creation
	@post The item inserted is the last item on the list */
	void				insert_back(T t_item);
	/** Inserts an entry into this list at a given position.
	@pre requires there to be enough memory for allocating during node insertion
	@post If 1 <= position <= getLength() + 1 and the insertion is
	successful, newEntry is at the given position in the list,
	other entries are renumbered accordingly, and the returned
	value is true.
	@param newPosition The list position at which to insert newEntry.
	@param newEntry The entry to insert into the list.
	@return True if insertion is successful, or false if not. */
	bool				insert(int index, T t_item);
	/** Removes the first item in the list
	@pre List is not empty
	@post First item is removed
	@return True if removal is successful, or false if not. */
	void				remove_front();
	/** Removes the last item in the list
	@pre List is not empty
	@post Last item is removed
	@return True if removal is successful, or false if not. */
	void				remove_back();
	/** Removes the entry at a given position from this list.
	@pre List is not empty
	@post If 1 <= position <= getLength() and the removal is successful,
	the entry at the given position in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@param position The list position of the entry to remove.
	@return True if removal is successful, or false if not. */
	bool				remove(int index);
	/** Removes all entries from this list.
	@post List contains no entries and the count of items is 0. */
	void				clear();
	/** Replaces the entry at the given position in this list.
	@pre 1 <= position <= getLength().
	@post The entry at the given position is newEntry.
	@param position The list position of the entry to replace.
	@param newEntry The replacement entry. */
	void				set_item(int index, T t_item);
	/* Insert in ascending order such that the first node in the
	linked list is smaller than the preceding nodes
	@pre a new entry needs to be inserted in to the list
	@post the entry is inserted into its appropriate position mainting list sort-order
	@return true if successful else false
	@param newItem is the new item to insert into the list*/
	bool				sorted_insert(const T& newItem);

	//----------------------------------------------------
	// Getters Section
	//----------------------------------------------------

	/** Sees whether this list is empty.
	@return True if the list is empty; otherwise returns false. */
	bool				is_empty() const;
	/** Gets the current number of entries in this list.
	@return The integer number of entries currently in the list. */
	int					size() const;
	/** Gets the entry at the given position in this list.
	@pre 1 <= position <= getLength().
	@post The desired entry has been returned.
	@param position The list position of the desired entry.
	@return The entry at the given position. */
	T					get_item(int index) const;
	T&					__get_item(int index);
};

template <class T>
LinkedList<T>::LinkedList() {
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& copy)
{ 
	int SIZE = copy.size();
	this->clear();
	for (int i = 0; i < SIZE; i++)
	{
		this->insert_back(copy.get_item(i));
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
	clear();
	delete __nav;
}

// returns true if the linked list is empty
template <class T>
bool LinkedList<T>::is_empty() const {
	return __list.get_first() == nullptr;
}

// adds to front of linked list and points head to new node
template <class T>
void LinkedList<T>::insert_front(T t_item) {
	LinkNode<T>* toAdd = new LinkNode<T>(t_item, nullptr);

	if (is_empty()) {
		__list.set_first(toAdd); // point head from nullptr to new node
		__list.set_last(toAdd); // point tail from nullptr to new node
		__list.set_size(__list.size() + 1); // size ++
		return;
	}

	toAdd->set_next(__list.get_first()); // point new node's next to where head points to
	__list.set_first(toAdd); // point headNode to new node
	__list.set_size(__list.size() + 1); // size ++
}

// adds to back of linked list and points tail to new node
template <class T>
void LinkedList<T>::insert_back(T t_item) {
	LinkNode<T>* toAdd = new LinkNode<T>(t_item, nullptr);
	if (is_empty()) {
		insert_front(t_item);
		return;
	}
	__list.get_last()->set_next(toAdd); // point tail's next from nullptr to new node
	__list.set_last(__list.get_last()->get_next()); // point tail to new node
	__list.set_size(__list.size() + 1); // size ++
}

// adds to linked list at index.. starts with 0 as first index and size() - 1 as last index
template <class T>
bool LinkedList<T>::insert(int index, T t_item) {
	if (index < 0 || index > size())	return false;

	if (is_empty() || index == 0) {
		insert_front(t_item);
		return true;
	}

	if (index == size()) {
		insert_back(t_item);
		return true;
	}

	LinkNode<T>* toAdd = new LinkNode<T>(t_item, nullptr);
	__nav = navigate(index - 1); // __nav points to prev of index
	toAdd->set_next(__nav->get_next()); // new node's next points to __nav's next
	__nav->set_next(toAdd); // __nav points to new node
	__list.set_size(__list.size() + 1); // size ++
	return true;
}

// removes the front node at index 0 and points head to its next node
template <class T>
void LinkedList<T>::remove_front() {
	if (is_empty()) return;

	// if 1 entry
	if (size() == 1 || __list.get_first() == __list.get_last()) {
		__list.set_size(__list.size() - 1); // size --
		delete __list.get_first();
		__list.set_first(nullptr);
		__list.set_last(nullptr);
		return;
	}

	LinkNode<T>* toRemove(__list.get_first());
	__list.set_first(__list.get_first()->get_next());
	__list.set_size(__list.size() - 1); // size --
	delete toRemove;
}

// removes tail node points tail to its prev node
template <class T>
void LinkedList<T>::remove_back() {
	if (is_empty()) return;

	// if 1 entry
	if (size() == 1 || __list.get_first() == __list.get_last()) {
		__list.set_size(__list.size() - 1); // size --
		delete __list.get_first();
		__list.set_first(nullptr);
		__list.set_last(nullptr);
		return;
	}

	__list.set_last(navigate(size() - 2)); // tail points to its prev
	__list.set_size(__list.size() - 1); // size --
	delete (__list.get_last())->get_next(); // delete what new tail's next
}

// removes the node at the index
template <class T>
bool LinkedList<T>::remove(int index) {
	if (index < 0 || index >= size())	return false;

	if (is_empty())	return false;

	if (index == 0) {
		remove_front();
		return true;
	}

	if (index == size() - 1) {
		remove_back();
		return true;
	}

	__nav = navigate(index - 1); // points __nav to the prev of node to remove
	LinkNode<T>* toRemove(__nav->get_next()); // point to node to remove
	__nav->set_next(toRemove->get_next()); // point __nav's next to node to remove's next
	__list.set_size(__list.size() - 1); // size --
	delete toRemove;
	return true;
}

// clears the linked list
template <class T>
void LinkedList<T>::clear() {
	int s = size();
	for (int i = 0; i < s; ++i) {
		remove_front();
	}
	__list.set_size(0); // set size to 0
}

// returns the number of entries in the linked list
template <class T>
int LinkedList<T>::size() const {
	return __list.size();
}

// returns the data at the index
template <class T>
T LinkedList<T>::get_item(int index) const
{
	T item = this->navigate(index)->get_item();
	return item;
}
template <class T>
T& LinkedList<T>::__get_item(int index)
{
	return this->navigate(index)->__get_item();
}

// sets the data at index
template <class T>
void LinkedList<T>::set_item(int index, T t_item) {
	navigate(index)->set_item(t_item);
}

// traverses through linked list and returns a pointer to the node at the given index
template <class T>
LinkNode<T>* LinkedList<T>::navigate(int index) const{
	LinkNode<T>* nav;
	if (is_empty()) {
		return nullptr;
	}
	if (index < 0 || index >= __list.size()) {
		return nullptr;
	}
	nav = __list.get_first();
	for (int i = 0; i < index; ++i) {
		nav = nav->get_next();
	}
	return nav;
}
template<class T>
bool LinkedList<T>::sorted_insert(const T& newItem)
{
	if (__list.size() < 2) {
		if (__list.size() == 0)
		{
			this->insert_back(newItem);
			return true;
		}
		else if (__list.size() == 1)
		{
			if (__list.get_first()->get_item() < newItem)
			{
				this->insert_back(newItem);
			}
			else
				this->insert_front(newItem);
		}
	}
	else
	{

		if (__list.get_last()->get_item() <= newItem) {
			/*  new > last --> append */
			LinkNode<T>* pNew = new LinkNode<T>(newItem);
			__list.get_last()->set_next(pNew);	// point old last to the new node
			__list.set_last(pNew);	// retarget head node's "last node" pointer to the new
			__list.set_size(__list.size() + 1);
			return true;
			//this->display();		// DEBUG
		}
		else if (__list.get_first()->get_item() >= newItem) {
			/* first > new --> prepend */
			LinkNode<T>* pNew = new LinkNode<T>(newItem);
			pNew->set_next(__list.get_first());	// new points to the old head
			__list.set_first(pNew);				// sentinel's "first node" pointer points to new node
			__list.set_size(__list.size() + 1);
			//this->display();	// DEBUG
			return true;
		}

		LinkNode<T>* pNew = new LinkNode<T>(newItem);
		LinkNode<T>* pPrev = nullptr;
		LinkNode<T>* pCurr = __list.get_first();
		while (pCurr != __list.get_last() && __list.get_first()->get_item() < newItem
			&& __list.get_last()->get_item() > newItem)
		{
			pPrev = pCurr;
			pCurr = pCurr->get_next();
			if (newItem <= pCurr->get_item() && pPrev->get_item() < newItem) {
				pPrev->set_next(pNew);
				pNew->set_next(pCurr);
				__list.set_size(__list.size() + 1);
				return true;
			}

		}
	}
}
#endif // LINKED_LIST_H
