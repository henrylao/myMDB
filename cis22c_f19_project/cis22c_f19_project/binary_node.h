
#ifndef _BINARY_NODE
#define _BINARY_NODE

template <typename T>
class BinaryNode {
private:
	T m_item;
	BinaryNode* m_left_child;
	BinaryNode* m_right_child;
public:
	//-----------------------------
	// CONSTRUCTORS 
	//-----------------------------
	// default constructor
	BinaryNode<T>();
	// init node with item with no child nodes
	BinaryNode<T>(const T& t_item);
	// init with item with with child nodes
	BinaryNode<T>(const T& t_item, BinaryNode<T>* t_left_child, BinaryNode<T>* t_right_child);
	//-----------------------------
	// GETTERS
	//-----------------------------
	/* Get the item stored in the calling node
	@pre None
	@post None
	@return The item stored in the calling node */
	T getItem() const;			// return current node's stored item
	/* Get the left node pointed by the calling node
	@pre None
	@post None
	@return a BinaryNode address representing the left node pointed by the caller
	else nullptr */
	BinaryNode<T>* getRightChildPtr() const;
	/* Get the left node pointed by the calling node 
	@pre None
	@post None
	@return a BinaryNode address representing the left node pointed by the caller
	else nullptr */
	BinaryNode<T>* getLeftChildPtr() const;
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
	void setItem(const T& t_new_item);				
	/* Modify the calling node's left child 
	@post left child node changed to the input BinaryNode pointer
	@param t_new_node is the new left node */
	void setLeftChildPtr(BinaryNode<T>* t_new_node);
	/* Modify the calling node's left child
	@post right child node changed to the input BinaryNode pointer
	@param t_new_node is the new right node */	
	void setRightChildPtr(BinaryNode<T>* t_new_node);
};
template <typename T>
BinaryNode<T>::BinaryNode() : m_left_child(nullptr), m_right_child(nullptr)
{} // end default constructor

template <typename T>
BinaryNode<T>::BinaryNode(const T& t_item) :
	m_item(t_item), m_left_child(nullptr), m_right_child(nullptr)
{} // end constructor

template <typename T>
BinaryNode<T>::BinaryNode(const T& t_item, BinaryNode<T>* t_left_child, BinaryNode<T>* t_right_child) :
	m_item(t_item), m_left_child(t_left_child), m_right_child(t_right_child)
{}	// end constructor

template <typename T>
void BinaryNode<T>::setItem(const T& t_item) {
	this->m_item = t_item;
}	// end setItem

template <typename T>
void BinaryNode<T>::setLeftChildPtr(BinaryNode<T>* t_left_child) {
	this->m_left_child = t_left_child;
}	// end set
template <typename T>
void BinaryNode<T>::setRightChildPtr(BinaryNode<T>* t_right_child) {
	this->m_right_child = t_right_child;
}	// end set_next

template <typename T>
T BinaryNode<T>::getItem() const {
	return this->m_item;
}	// end getItem

template <typename T>
BinaryNode<T>* BinaryNode<T>::getLeftChildPtr() const {
	return (this->m_left_child);
}	// end get_next

template <typename T>
bool BinaryNode<T>::isLeaf() const {
	return (m_left_child == nullptr && m_right_child == nullptr? true: false);
}	// a node is a leaf 

template <typename T>
BinaryNode<T>* BinaryNode<T>::getRightChildPtr() const {
	return (this->m_right_child);
}	// end get_next

#endif 