
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "head_node.h"

template <class T>
class LinkedList {
public:
	LinkedList();
	virtual ~LinkedList();
	/** Sees whether this list is empty.
	@return True if the list is empty; otherwise returns false. */
	bool is_empty() const;
	/** Appends a new item to the front of the list
	@pre There is sufficient memory to be allocated for node creation
	@post The item inserted is the first item on the list
	@return True if removal is successful, or false if not. */
	void insert_front(T t_item);
	/** Prepends a new item to the back of the list
	@pre There is sufficient memory to be allocated for node creation
	@post The item inserted is the last item on the list */
	void insert_back(T t_item);
	/** Inserts an entry into this list at a given position.
	@pre requires there to be enough memory for allocating during node insertion
	@post If 1 <= position <= getLength() + 1 and the insertion is
	successful, newEntry is at the given position in the list,
	other entries are renumbered accordingly, and the returned
	value is true.
	@param newPosition The list position at which to insert newEntry.
	@param newEntry The entry to insert into the list.
	@return True if insertion is successful, or false if not. */
	bool insert(int index, T t_item);
	/** Removes the first item in the list
	@pre List is not empty
	@post First item is removed
	@return True if removal is successful, or false if not. */
	void remove_front();
	/** Removes the last item in the list
	@pre List is not empty
	@post Last item is removed
	@return True if removal is successful, or false if not. */
	void remove_back();
	/** Removes the entry at a given position from this list.
	@pre List is not empty
	@post If 1 <= position <= getLength() and the removal is successful,
	the entry at the given position in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@param position The list position of the entry to remove.
	@return True if removal is successful, or false if not. */
	bool remove(int index);
	/** Removes all entries from this list.
	@post List contains no entries and the count of items is 0. */
	void clear();
	/** Gets the current number of entries in this list.
	@return The integer number of entries currently in the list. */
	int size() const;
	/** Gets the entry at the given position in this list.
	@pre 1 <= position <= getLength().
	@post The desired entry has been returned.
	@param position The list position of the desired entry.
	@return The entry at the given position. */
	T get_item(int index) const;
	T& __get_item(int index);
	/** Replaces the entry at the given position in this list.
	@pre 1 <= position <= getLength().
	@post The entry at the given position is newEntry.
	@param position The list position of the entry to replace.
	@param newEntry The replacement entry. */
	void set_item(int index, T t_item);
	bool sorted_insert(const T& newItem);
protected:
	/* Helper function for traversing through the list
	@return*/
	LinkNode<T>* navigate(int index) const;

private:
	HeadNode<T> m_list;
	LinkNode<T>* m_nav;
};

template <class T>
LinkedList<T>::LinkedList() {
}

template <class T>
LinkedList<T>::~LinkedList() {
	clear();
}

// returns true if the linked list is empty
template <class T>
bool LinkedList<T>::is_empty() const {
	return m_list.get_first() == nullptr;
}

// adds to front of linked list and points head to new node
template <class T>
void LinkedList<T>::insert_front(T t_item) {
	LinkNode<T>* toAdd = new LinkNode<T>(t_item, nullptr);

	if (is_empty()) {
		m_list.set_first(toAdd); // point head from nullptr to new node
		m_list.set_last(toAdd); // point tail from nullptr to new node
		m_list.set_size(m_list.size() + 1); // size ++
		return;
	}

	toAdd->set_next(m_list.get_first()); // point new node's next to where head points to
	m_list.set_first(toAdd); // point headNode to new node
	m_list.set_size(m_list.size() + 1); // size ++
}

// adds to back of linked list and points tail to new node
template <class T>
void LinkedList<T>::insert_back(T t_item) {
	LinkNode<T>* toAdd = new LinkNode<T>(t_item, nullptr);
	if (is_empty()) {
		insert_front(t_item);
		return;
	}
	m_list.get_last()->set_next(toAdd); // point tail's next from nullptr to new node
	m_list.set_last(m_list.get_last()->get_next()); // point tail to new node
	m_list.set_size(m_list.size() + 1); // size ++
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
	m_nav = navigate(index - 1); // m_nav points to prev of index
	toAdd->set_next(m_nav->get_next()); // new node's next points to m_nav's next
	m_nav->set_next(toAdd); // m_nav points to new node
	m_list.set_size(m_list.size() + 1); // size ++
	return true;
}

// removes the front node at index 0 and points head to its next node
template <class T>
void LinkedList<T>::remove_front() {
	if (is_empty()) return;

	// if 1 entry
	if (size() == 1 || m_list.get_first() == m_list.get_last()) {
		m_list.set_size(m_list.size() - 1); // size --
		delete m_list.get_first();
		m_list.set_first(nullptr);
		m_list.set_last(nullptr);
		return;
	}

	LinkNode<T>* toRemove(m_list.get_first());
	m_list.set_first(m_list.get_first()->get_next());
	m_list.set_size(m_list.size() - 1); // size --
	delete toRemove;
}

// removes tail node points tail to its prev node
template <class T>
void LinkedList<T>::remove_back() {
	if (is_empty()) return;

	// if 1 entry
	if (size() == 1 || m_list.get_first() == m_list.get_last()) {
		m_list.set_size(m_list.size() - 1); // size --
		delete m_list.get_first();
		m_list.set_first(nullptr);
		m_list.set_last(nullptr);
		return;
	}

	m_list.set_last(navigate(size() - 2)); // tail points to its prev
	m_list.set_size(m_list.size() - 1); // size --
	delete (m_list.get_last())->get_next(); // delete what new tail's next
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

	m_nav = navigate(index - 1); // points m_nav to the prev of node to remove
	LinkNode<T>* toRemove(m_nav->get_next()); // point to node to remove
	m_nav->set_next(toRemove->get_next()); // point m_nav's next to node to remove's next
	m_list.set_size(m_list.size() - 1); // size --
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
	m_list.set_size(0); // set size to 0
}

// returns the number of entries in the linked list
template <class T>
int LinkedList<T>::size() const {
	return m_list.size();
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
	if (index < 0 || index >= m_list.size()) {
		return nullptr;
	}
	nav = m_list.get_first();
	for (int i = 0; i < index; ++i) {
		nav = nav->get_next();
	}
	return nav;
}
template<class T>
bool LinkedList<T>::sorted_insert(const T& newItem)
{
	if (m_list.size() < 2) {
		if (m_list.size() == 0)
		{
			this->insert_back(newItem);
			return true;
		}
		else if (m_list.size() == 1)
		{
			if (m_list.get_first()->get_item() < newItem)
			{
				this->insert_back(newItem);
			}
			else
				this->insert_front(newItem);
		}
	}
	else
	{

		if (m_list.get_last()->get_item() <= newItem) {
			/*  new > last --> append */
			LinkNode<T>* pNew = new LinkNode<T>(newItem);
			m_list.get_last()->set_next(pNew);	// point old last to the new node
			m_list.set_last(pNew);	// retarget head node's "last node" pointer to the new
			m_list.set_size(m_list.size() + 1);
			return true;
			//this->display();		// DEBUG
		}
		else if (m_list.get_first()->get_item() >= newItem) {
			/* first > new --> prepend */
			LinkNode<T>* pNew = new LinkNode<T>(newItem);
			pNew->set_next(m_list.get_first());	// new points to the old head
			m_list.set_first(pNew);				// sentinel's "first node" pointer points to new node
			m_list.set_size(m_list.size() + 1);
			//this->display();	// DEBUG
			return true;
		}

		LinkNode<T>* pNew = new LinkNode<T>(newItem);
		LinkNode<T>* pPrev = nullptr;
		LinkNode<T>* pCurr = m_list.get_first();
		while (pCurr != m_list.get_last() && m_list.get_first()->get_item() < newItem
			&& m_list.get_last()->get_item() > newItem)
		{
			pPrev = pCurr;
			pCurr = pCurr->get_next();
			if (newItem <= pCurr->get_item() && pPrev->get_item() < newItem) {
				pPrev->set_next(pNew);
				pNew->set_next(pCurr);
				m_list.set_size(m_list.size() + 1);
				return true;
			}

		}
	}
}
#endif // LINKED_LIST_H
