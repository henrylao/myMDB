#ifndef _LIST
#define _LIST
#include "linked_list.h"
#include "CustomException.h"
#include "ListInterface.h"
#include <iostream>
template <typename T>
class List {
	LinkedList<T>* __list;
public:
	//----------------------------------------------------
	// Constructor and Destructor Section
	//----------------------------------------------------

	List() { __list = new LinkedList<T>(); }
	virtual ~List() { __list->~LinkedList(); }
	//----------------------------------------------------
	// Getters Section
	//----------------------------------------------------

	//List(const List<T>& copy) { __list = LinkedList(copy); }
	/** Sees whether this list is empty.
	@return True if the list is empty; otherwise returns false. */
	bool isEmpty() const { return __list->is_empty(); }
	/** Gets the current number of entries in this list.
	@return The integer number of entries currently in the list. */
	int getLength() const { return __list->size(); }

	//----------------------------------------------------
	// Mutators Section
	//----------------------------------------------------

	bool sortedInsert(const T* newEntry) { return __list->sorted_insert(newEntry); }
	/** Inserts an entry into this list at a given position.
	@pre None.
	@post If 1 <= position <= getLength() + 1 and the insertion is
	successful, newEntry is at the given position in the list,
	other entries are renumbered accordingly, and the returned
	value is true.
	@param newPosition The list position at which to insert newEntry.
	@param newEntry The entry to insert into the list.
	@return True if insertion is successful, or false if not. */
	bool insert(int newPosition, const T & newEntry) { return __list->insert(newPosition, newEntry); }
	/** Removes the entry at a given position from this list.
	@pre None.
	@post If 1 <= position <= getLength() and the removal is successful,
	the entry at the given position in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@param position The list position of the entry to remove.
	@return True if removal is successful, or false if not. */
	bool remove(int position) { return __list->remove(position); }
	/** Removes all entries from this list.
	@post List contains no entries and the count of items is 0. */
	void clear() { __list->clear(); }
	/* Add to the end of the list
	@pre None
	@post newEntry added to the end of the list */
	bool append(const T& newEntry) { return this->insert(getLength(), newEntry); }
	/** Gets the entry at the given position in this list.
	@pre 1 <= position <= getLength().
	@post The desired entry has been returned.
	@param position The list position of the desired entry.
	@return The entry at the given position. */
	T  getEntry(int position)  const { return __list->get_item(position); }
	/** Replaces the entry at the given position in this list.
	@pre 1 <= position <= getLength().
	@post The entry at the given position is newEntry.
	@param position The list position of the entry to replace.
	@param newEntry The replacement entry. */
	void setEntry(int position, const T & newEntry) { __list->set_item(position, newEntry); }

	//--------------------------------
	// Operator Overload Section
	//------------------------------
	//T& operator[](const int& idx);
	T operator[](const int& idx) const;
	template <class U>
	friend std::ostream& operator<< (std::ostream &out,  const List<U>& list);
	
};
template <typename T>
std::ostream& operator<< (std::ostream &out,  const List<T>& list) 
{
	out << "[ ";
	int SIZE = list.getLength();
	T item = list.getEntry(0);
	if (SIZE == 1) {
		out << item << " ]\n";
		return out;
	}
	for (int i = 0; i < SIZE - 1; i++) {
		item = list.getEntry(i);
		out << item;
		out << ", ";
	}
	out << list.getEntry(SIZE - 1);
	out << " ]";
	return out;
}
template <typename T>
T List<T>::operator[] (const int& index) const
{
	if (index > this->getLength())
		throw CustomException("Index Out of Bounds");
	return __list->get_item(index);
}
#endif // !1
