#ifndef _BINARY_NODE
#define _BINARY_NODE

template <typename K, typename V>
class BinaryNode {
private:
	K					__key;
	V					__val;
	BinaryNode*			__leftChild;
	BinaryNode*			__rightChild;
public:
	//-----------------------------
	// CONSTRUCTORS 
	//-----------------------------
	// default constructor
	BinaryNode<K, V>();
	// init node with item with no child nodes
	BinaryNode<K, V>(const K& t_key, const V& t_val);
	// init with item with with child nodes
	BinaryNode<K, V>(const K& t_key, const V& t_val, BinaryNode<K, V>* t_left_child, BinaryNode<K, V>* t_right_child);
	//-----------------------------
	// GETTERS
	//-----------------------------
	/* Get the key stored in the calling node
	@pre None
	@post None
	@return The item stored in the calling node */
	K getKey() const;			// return current node's stored item
	/* Get the value stored in the calling node
	@pre None
	@post None
	@return The item stored in the calling node */
	V getVal() const;			// return current node's stored item
	/* Get the left node pointed by the calling node
	@pre None
	@post None
	@return a BinaryNode address representing the left node pointed by the caller
	else nullptr */
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
	// MUTATORS 
	//-----------------------------
	/* Modify the item stored in the calling node
	@post item is modified to reflect the value of the input item
	@param t_new_item is the new value for the calling node to store*/
	void setKey(const K& t_new_key);				
	void setVal(const V& t_new_val);
	/* Modify the calling node's left child 
	@post left child node changed to the input BinaryNode pointer
	@param t_new_node is the new left node */
	void setLeftChildPtr(BinaryNode<K, V>* t_new_node);
	/* Modify the calling node's left child
	@post right child node changed to the input BinaryNode pointer
	@param t_new_node is the new right node */	
	void setRightChildPtr(BinaryNode<K, V>* t_new_node);

	BinaryNode<K, V>& operator==(const BinaryNode<K, V>& t_rhs);
	BinaryNode<K, V>& operator>(const BinaryNode<K, V>& t_rhs);
	BinaryNode<K, V>& operator<(const BinaryNode<K, V>& t_rhs);
};
template <typename K, typename V>
BinaryNode<K, V>::BinaryNode() : __leftChild(nullptr), __rightChild(nullptr)
{} // end default constructor

template <typename K, typename V>
BinaryNode<K, V>::BinaryNode(const K& t_key, const V& t_val) :
	__key(t_key), __val(t_val), __leftChild(nullptr), __rightChild(nullptr)
{} // end constructor

template <typename K, typename V>
BinaryNode<K, V>::BinaryNode(const K& t_key, const V& t_val, BinaryNode<K, V>* t_left_child, BinaryNode<K, V>* t_right_child) :
	__key(t_key), __val(t_val), __leftChild(t_left_child), __rightChild(t_right_child)
{}	// end constructor

template <typename K, typename V>
void BinaryNode<K, V>::setKey(const K& t_new_key) {
	this->__key = t_new_key;
}	// end setKey

template<typename K, typename V>
void BinaryNode<K, V>::setVal(const V & t_new_val)
{
	this->__val = t_new_val;
}

template <typename K, typename V>
void BinaryNode<K, V>::setLeftChildPtr(BinaryNode<K, V>* t_left_child) {
	this->__leftChild = t_left_child;
}	// end set
template <typename K, typename V>
void BinaryNode<K, V>::setRightChildPtr(BinaryNode<K, V>* t_right_child) {
	this->__rightChild = t_right_child;
}	// end set_next

template<typename K, typename V>
BinaryNode<K, V> & BinaryNode<K, V>::operator==(const BinaryNode<K, V> & t_rhs)
{
	if (this->__key == t_rhs.__key && this->__val == t_rhs.__val) return true;
	else false;
}

template<typename K, typename V>
BinaryNode<K, V> & BinaryNode<K, V>::operator>(const BinaryNode<K, V> & t_rhs)
{
	if (this->__key > t_rhs.__key && this->__val > t_rhs.__val) return true;
	else false;
}

template<typename K, typename V>
BinaryNode<K, V> & BinaryNode<K, V>::operator<(const BinaryNode<K, V> & t_rhs)
{
	if (this->__key < t_rhs.__key && this->__val < t_rhs.__val) return true;
	else false;
}

template <typename K, typename V>
K BinaryNode<K, V>::getKey() const {
	return this->__key;
}	// end getKey

template<typename K, typename V>
V BinaryNode<K, V>::getVal() const
{
	return this->__val;
}

template <typename K, typename V>
BinaryNode<K, V>* BinaryNode<K, V>::getLeftChildPtr() const {
	return (this->__leftChild);
}	// end get_next

template <typename K, typename V>
bool BinaryNode<K, V>::isLeaf() const {
	return (__leftChild == nullptr && __rightChild == nullptr? true: false);
}	// a node is a leaf 

template <typename K, typename V>
BinaryNode<K, V>* BinaryNode<K, V>::getRightChildPtr() const {
	return (this->__rightChild);
}	// end get_next

#endif 