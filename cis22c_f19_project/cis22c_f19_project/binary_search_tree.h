#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include <sstream>
#include "binary_node.h"
#include "binary_tree.h"
#include "binary_tree_interface.h"

template <typename T>
class BinarySearchTree : protected BinaryNodeTree<T>
{
private:
	BinaryNode<T>* m_root;
	int m_out_traverse;
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	BinaryNode<T>* insertInorder(BinaryNode<T>* t_sub_tree_ptr, BinaryNode<T>* newNode);
	// Removes the given t_target value from the tree while maintaining a
	// binary search tree.
	BinaryNode<T>* removeValue(BinaryNode<T>* t_sub_tree_ptr, const T t_target, bool& success);
	// Removes a given node from a tree while maintaining a
	// binary search tree.
	BinaryNode<T>* removeNode(BinaryNode<T>* t_node_ptr);
	// Removes the leftmost node in the left subtree of the node
	// pointed to by t_node_ptr.
	// Sets t_inorder_successor to the value in this node.
	// Returns a pointer to the revised subtree.
	BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* t_sub_tree_ptr, T& t_inorder_successor);
	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	BinaryNode<T>* findNode(BinaryNode<T>* t_tree_ptr, const T& t_target) const;
	// call on root or parent tree to find the leftmost node
	BinaryNode<T>* getLeftmostNode(BinaryNode<T>* t_root);
	// fileIO helper functions
	std::ostream& serializeInorder(std::ostream& t_out, BinaryNode<T>* t_node_ptr);
	std::ostream& serializePostorder(std::ostream& t_out, BinaryNode<T>* t_node_ptr);
	std::ostream& serializePreorder(std::ostream& t_out, BinaryNode<T>* t_node_ptr);
	std::ostream& serializeBreadthFirst(std::ostream& t_out, BinaryNode<T>* t_node_ptr);
public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree() : m_root(nullptr), m_out_traverse(0) {}
	BinarySearchTree(const T& t_root_item) : m_root(t_root_item) {}
	// Copy constructor
	BinarySearchTree(const BinarySearchTree<T>& t_tree) : BinaryNodeTree<T>(t_tree) {}
	virtual ~BinarySearchTree();
	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const { return (this->m_root == nullptr ? true : false); }
	int getHeight() const { return BinaryNodeTree<T>::getHeightHelper(this->m_root); }
	int getNumberOfNodes() const { return BinaryNodeTree<T>::getNumberOfNodesHelper(this->m_root); }
	T getRootData() const throw (PrecondViolatedExcep);
	void setRootData(const T& t_new_item) { this->m_root->setItem(t_new_item); }
	//const throw (PrecondViolatedExcep);
	bool add(const T& t_new_item);
	bool remove(const T& t_item);
	void clear() { BinaryNodeTree<T>::destroyTree(this->m_root); }
	T getItem(const T& t_item) const throw (NotFoundException);
	bool contains(const T& t_item) const;
	/* Set the current order of traversal for output
	0 - inorder | 1 - preorder | 2 - postorder | 3 - breadthFirst |
	@pre integer between 0 and 3 (inclusive)
	@post integer representing the order of traversal */
	void setOutTraverse(const int& t_op) { this->m_out_traverse = t_op; }
	/* Get the current order of traversal for output
	0 - inorder | 1 - preorder | 2 - postorder | 3 - breadthFirst |
	@return integer representing the order of traversal */
	int getOutTraverse() const { return this->m_out_traverse; }
	//------------------------------------------------------------
	// Public Traversal Section
	//------------------------------------------------------------
	//	Order Traversal (Recursive) Section
	void preorderTraverse(void visit(T&)) const { BinaryNodeTree<T>::preorder(visit, this->m_root); }
	void inorderTraverse(void visit(T&)) const { BinaryNodeTree<T>::inorder(visit, this->m_root); }
	void postorderTraverse(void visit(T&)) const { BinaryNodeTree<T>::postorder(visit, this->m_root); }
	void breadthFirstTraverse(void visit(T&)) const { BinaryNodeTree<T>::breadthFirst(visit, this->m_root); }
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& t_rhs);
	/* Outputs to the ostream object using the << operator
	@pre the order for traversal is between 0 and 3 (inclusive)
	@post binarySearchTree data is written to the ostream object according to the current set
	order of output traversal*/
	template <typename U>      // all instantiations of this template are my friends
	friend std::ostream& operator<<(std::ostream& t_out, BinarySearchTree<U>& t_bst);
	//------------------------------------------------------------
	//  Serialization Section
	//------------------------------------------------------------
	std::ostream& serializeInorderTraverse(std::ostream& t_out) { return this->serializeInorder(t_out, this->m_root); }
	std::ostream& serializePostorderTraverse(std::ostream& t_out) { return this->serializePostorder(t_out, this->m_root); }
	std::ostream& serializePreorderTraverse(std::ostream& t_out) { return this->serializePreorder(t_out, this->m_root); }
	std::ostream& serializeBreadthFirstTraverse(std::ostream& t_out) { return this->serializeBreadthFirst(t_out, this->m_root); }
}; // end BinarySearchTree
template <typename T>
std::ostream& BinarySearchTree<T>::serializeBreadthFirst(std::ostream& t_out, BinaryNode<T>* t_node_ptr)
{
	Queue<BinaryNode<T>*> node_q;
	if (t_node_ptr == nullptr)
		return t_out;
	node_q.enqueue(t_node_ptr);

	while (!node_q.is_empty())
	{
		BinaryNode<T>* pNode = node_q.front();
		if (pNode != nullptr)
		{
			T item = pNode->getItem();
			t_out << item ;
			node_q.dequeue();
			if (pNode->getLeftChildPtr() != nullptr)
				node_q.enqueue(pNode->getLeftChildPtr());
			if (pNode->getRightChildPtr() != nullptr)
				node_q.enqueue(pNode->getRightChildPtr());
		}
	}
	return t_out;
}

template <typename T>
T BinarySearchTree<T>::getRootData() const throw (PrecondViolatedExcep)
{
	if (!this->isEmpty())
		return this->m_root->getItem();
	else
		throw PrecondViolatedExcep("No data in root node");
}
template <typename T>
std::ostream& operator<<(std::ostream& t_out, BinarySearchTree<T>& t_bst)
{
	if (t_bst.getOutTraverse() == 0) {
		t_bst.serializeInorderTraverse(t_out);
		return t_out;
	}
	else if (t_bst.getOutTraverse() == 1) {
		t_bst.serializePreorderTraverse(t_out);
		return t_out;
	}
	else if (t_bst.getOutTraverse() == 2) {
		t_bst.serializePostorderTraverse(t_out);
		return t_out;
	}
	else if (t_bst.getOutTraverse() == 3) {
		t_bst.serializeBreadthFirstTraverse(t_out);
		return t_out;
	}
	else 
		return t_out;
}
template <typename T>
std::ostream& BinarySearchTree<T>::serializeInorder(std::ostream& t_out, BinaryNode<T>* t_node_ptr)
{
	if (t_node_ptr != nullptr)
	{
		this->serializeInorder(t_out, t_node_ptr->getLeftChildPtr());
		t_out << t_node_ptr->getItem() ;
		this->serializeInorder(t_out, t_node_ptr->getRightChildPtr());
	}
	return t_out;

}
template <typename T>
std::ostream&  BinarySearchTree<T>::serializePreorder(std::ostream& t_out, BinaryNode<T>* t_node_ptr)
{
	if (t_node_ptr != nullptr)
	{
		t_out << t_node_ptr->getItem() ;
		this->serializePreorder(t_out, t_node_ptr->getLeftChildPtr());
		this->serializePreorder(t_out, t_node_ptr->getRightChildPtr());

	}
	return t_out;
}

template <typename T>
std::ostream& BinarySearchTree<T>::serializePostorder(std::ostream& t_out, BinaryNode<T>* t_node_ptr)
{
	if (t_node_ptr != nullptr)
	{
		this->serializeInorder(t_out, t_node_ptr->getLeftChildPtr());
		this->serializeInorder(t_out, t_node_ptr->getRightChildPtr());
		t_out << t_node_ptr->getItem() ;
	}
	return t_out;

}
template <class T>
bool BinarySearchTree<T>::remove(const T& t_item)
{
	bool success = false;
	this->m_root = this->removeValue(this->m_root, t_item, success);
	return (success ? true : false);
	//throw new NotFoundException("Item not found"));
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(
	BinaryNode<T>* t_node_to_delete,
	T& t_inorder_successor)
{
	if (t_node_to_delete->getLeftChildPtr() == nullptr)
	{
		t_inorder_successor = t_node_to_delete->getItem();
		return this->removeNode(t_node_to_delete);
	}
	else
	{
		t_node_to_delete->setLeftChildPtr(this->removeLeftmostNode(t_node_to_delete->getLeftChildPtr(), t_inorder_successor));
		return t_node_to_delete;
		//return this->removeLeftmostNode(t_node_to_delete->getLeftChildPtr, t_inorder_successor);
	}
}

template <class T>
T BinarySearchTree<T>::getItem(const T& t_item) const throw (NotFoundException)
{
	bool found_success = false;
	BinaryNode<T>* found_node_ptr = this->findNode(this->m_root, t_item);

	if (found_node_ptr == nullptr)
		throw NotFoundException("Item not found");
	else
		return found_node_ptr->getItem();
}
template <class T>
BinaryNode<T>* BinarySearchTree<T>::getLeftmostNode(BinaryNode<T>* t_root)
{
	// base case: leftmost child is null
	if (t_root->getLeftChildPtr() == nullptr)
		return t_root;
	// left child is not null case
	else
	{
		// recursive call to get the leftmost node
		return this->getLeftmostNode(t_root->getLeftChildPtr());
	}
}
template <class T>
BinaryNode<T>* BinarySearchTree<T>::removeNode(BinaryNode<T>* t_node_to_delete)
{
	// base case: null root case
	if (t_node_to_delete == nullptr)
		return nullptr;
	// tree is a leaf case
	if (t_node_to_delete->isLeaf())
	{
		delete t_node_to_delete;
		t_node_to_delete = nullptr;
		return t_node_to_delete;
	}
	// single child case
	else if ((t_node_to_delete->getLeftChildPtr() != nullptr && t_node_to_delete->getRightChildPtr() == nullptr)
		|| (t_node_to_delete->getLeftChildPtr() == nullptr && t_node_to_delete->getRightChildPtr() != nullptr))
	{
		BinaryNode<T>* node_to_connect = nullptr;
		if (t_node_to_delete->getLeftChildPtr() == nullptr)
			node_to_connect = t_node_to_delete->getRightChildPtr();
		delete t_node_to_delete;
		t_node_to_delete = nullptr;
		return node_to_connect;
	}
	// tree case
	else
	{
		T inord_succ_item;
		BinaryNode<T>* temp_node_ptr = this->removeLeftmostNode(t_node_to_delete->getRightChildPtr(), inord_succ_item);
		t_node_to_delete->setRightChildPtr(temp_node_ptr);
		t_node_to_delete->setItem(inord_succ_item);
		return t_node_to_delete;
	}
	return t_node_to_delete;

}
template <class T>
BinaryNode<T>* BinarySearchTree<T>::removeValue(
	BinaryNode<T>* t_sub_tree_ptr,
	const T t_target,
	bool& t_success)
{
	// tree node is null case
	if (t_sub_tree_ptr == nullptr)
	{
		t_success = false;
		return nullptr;
	}
	// target found case
	else if (t_sub_tree_ptr->getItem() == t_target)
	{
		t_sub_tree_ptr = this->removeNode(t_sub_tree_ptr);
		t_success = true;
		return t_sub_tree_ptr;
	}
	// handle left of tree case
	else if (t_sub_tree_ptr->getItem() > t_target)
	{
		BinaryNode<T>* temp_node_ptr = nullptr;
		temp_node_ptr = this->removeValue(t_sub_tree_ptr->getLeftChildPtr(), t_target, t_success);
		t_sub_tree_ptr->setLeftChildPtr(temp_node_ptr);
		return t_sub_tree_ptr;
	}
	// handle right of tree case
	else
	{
		BinaryNode<T>* temp_node_ptr = nullptr;
		temp_node_ptr = this->removeValue(t_sub_tree_ptr->getRightChildPtr(), t_target, t_success);
		t_sub_tree_ptr->setRightChildPtr(temp_node_ptr);
		return t_sub_tree_ptr;
	}
}
template <class T>
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* t_tree_ptr, const T& t_target) const
{
	bool success = false;
	BinaryNode<T>* found_ptr = BinaryNodeTree<T>::findNode(t_tree_ptr, t_target, success);
	return found_ptr;
}
template <class T>
bool BinarySearchTree<T>::contains(const T& t_target) const
{
	BinaryNode<T>* node_found_ptr = nullptr;
	node_found_ptr = this->findNode(this->m_root, t_target);
	return (node_found_ptr != nullptr ? true : false);
}
template <class T>
bool BinarySearchTree<T>::add(const T& t_new_item)
{
	BinaryNode<T>* new_node = new BinaryNode<T>(t_new_item);
	this->m_root = this->insertInorder(this->m_root, new_node);
	return true;
}	// end add
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	this->clear();
}	// end destructor
template <class T>
BinaryNode<T>* BinarySearchTree<T>::insertInorder(BinaryNode<T>* tree_node, BinaryNode<T>* add_node) {
	if (tree_node == nullptr)
		return add_node;
	else if (tree_node->getItem() > add_node->getItem()) {
		BinaryNode<T>* temp_node = this->insertInorder(tree_node->getLeftChildPtr(), add_node);
		tree_node->setLeftChildPtr(temp_node);
	}
	else {
		BinaryNode<T>* temp_node = insertInorder(tree_node->getRightChildPtr(), add_node);
		tree_node->setRightChildPtr(temp_node);
	}
	return tree_node;
}	// end insertInorder
template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& t_rhs)
{
	this->clear();
	this->m_root = this->copyTree(t_rhs.m_root);
	return *this;
}

#endif
