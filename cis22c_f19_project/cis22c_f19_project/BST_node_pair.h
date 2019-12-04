
#ifndef _BINARY_NODE
#define _BINARY_NODE
#include "list.h"
template <typename K, typename V>
class BinaryNode {
private:
	K			__key;
	List<V>*	__values;
	BinaryNode* __leftChild;
	BinaryNode* __rightChild;
public:
	//-----------------------------
	// CONSTRUCTORS
	//-----------------------------
	// default constructor
	BinaryNode<K, V>();
	// init node with item with no child nodes
	BinaryNode<K, V>(const K& key);
	BinaryNode<K, V>(const K& key,  List<V>* values) : __key(key), __values(values) {}
	// init with item with with child nodes
	BinaryNode<K, V>(const K& key, BinaryNode<K, V>* t_left_child, BinaryNode<K, V>* t_right_child);
	//-----------------------------
	// GETTERS
	//-----------------------------
	/* Get the item stored in the calling node
	@pre None
	@post None
	@return Khe item stored in the calling node */
	K getKey() const;			// return current node's stored item
	/* Get the left node pointed by the calling node
	@pre None
	@post None
	@return a BinaryNode address representing the left node pointed by the caller
	else nullptr */
	List<V>* getValues() const;
	BinaryNode<K, V>* getRightChildPtr() const;
	/* Get the left node pointed by the calling node
	@pre None
	@post None
	@return a BinaryNode address representing the left node pointed by the caller
	else nullptr */
	BinaryNode<K, V>* getLeftChildPtr() const;
	/* Qualify this node as a leaf
	@pre None
	@post None
	@return true if this node does not point to a right or left node else false */
	bool isLeaf() const;
	//-----------------------------
	// MUKAKORS
	//-----------------------------
	/* Modify the item stored in the calling node
	@post item is modified to reflect the value of the input item
	@param t_new_item is the new value for the calling node to store*/
	void setKey(const K& t_new_item);
	/* Modify the calling node's left child
	@post left child node changed to the input BinaryNode pointer
	@param t_new_node is the new left node */
	void setLeftChildPtr(BinaryNode<K, V>* t_new_node);
	/* Modify the calling node's left child
	@post right child node changed to the input BinaryNode pointer
	@param t_new_node is the new right node */
	void setRightChildPtr(BinaryNode<K, V>* t_new_node);
	void setValue(List<V>* values);
	void removeByValue(const V& value);
	void addValue(const V& newValue) { __values->sortedInsert(newValue); }
};
template <typename K, typename V>
BinaryNode<K, V>::BinaryNode() : __leftChild(nullptr), __rightChild(nullptr), __values(new List<V>())
{} // end default constructor

template <typename K, typename V>
BinaryNode<K, V>::BinaryNode(const K& key) :
	__key(key), __leftChild(nullptr), __rightChild(nullptr), __values(new List<V>())
{} // end constructor

template <typename K, typename V>
BinaryNode<K, V>::BinaryNode(const K& key, BinaryNode<K, V>* t_left_child, BinaryNode<K, V>* t_right_child) :
	__key(key), __leftChild(t_left_child), __rightChild(t_right_child), __values(new List<V>())
{}	// end constructor

template<typename K, typename V>
List<V>* BinaryNode<K, V>::getValues() const
{
	return __values;
}

template <typename K, typename V>
void BinaryNode<K, V>::setKey(const K& key) {
	this->__key = key;
}	// end setKey

template <typename K, typename V>
void BinaryNode<K, V>::setValue(List<V>* values) {
	delete __values;
	__values = values;
}	// end setKey

template<typename K, typename V>
void BinaryNode<K, V>::removeByValue(const V & value)
{
	__values->removeByValue(value);
}

template <typename K, typename V>
void BinaryNode<K, V>::setLeftChildPtr(BinaryNode<K, V>* t_left_child) {
	this->__leftChild = t_left_child;
}	// end set
template <typename K, typename V>
void BinaryNode<K, V>::setRightChildPtr(BinaryNode<K, V>* t_right_child) {
	this->__rightChild = t_right_child;
}	// end set_next

template <typename K, typename V>
K BinaryNode<K, V>::getKey() const {
	return this->__key;
}	// end getKey

template <typename K, typename V>
BinaryNode<K, V>* BinaryNode<K, V>::getLeftChildPtr() const {
	return (this->__leftChild);
}	// end get_next

template <typename K, typename V>
bool BinaryNode<K, V>::isLeaf() const {
	return (__leftChild == nullptr && __rightChild == nullptr ? true : false);
}	// a node is a leaf

template <typename K, typename V>
BinaryNode<K, V>* BinaryNode<K, V>::getRightChildPtr() const {
	return (this->__rightChild);
}	// end get_next

#endif
