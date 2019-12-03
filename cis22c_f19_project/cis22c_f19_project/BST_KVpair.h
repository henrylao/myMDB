#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include <sstream>
#include "binary_node_kvpair.h"
#include "binary_tree_kvpair.h"
#include "binary_tree_interface_kvpair.h"

template <typename K, typename V>
class BinarySearchTree : protected BinaryNodeTree<K, V>
{
private:
	BinaryNode<K, V>* m_root;
	int m_out_traverse;
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	BinaryNode<K, V>* insertInorder(BinaryNode<K, V>* subNode, BinaryNode<K, V>* newNode);
	// Removes the given t_target value from the tree while maintaining a
	// binary search tree.
	BinaryNode<K, V>* removeValue(BinaryNode<K, V>* subNode, const K& t_target, const V& value, bool& success);
	// Removes a given node from a tree while maintaining a
	// binary search tree.
	BinaryNode<K, V>* removeNode(BinaryNode<K, V>* t_node_ptr);
	// Removes the leftmost node in the left subtree of the node
	// pointed to by t_node_ptr.
	// Sets t_inorder_successor to the value in this node.
	// Returns a pointer to the revised subtree.
	BinaryNode<K, V>* removeLeftmostNode(BinaryNode<K, V>* subNode, K& t_inorder_successor);
	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	BinaryNode<K, V>* findNode(BinaryNode<K, V>* t_tree_ptr, const K& targeKey, const V& targeVal) const;
	// call on root or parent tree to find the leftmost node
	BinaryNode<K, V>* getLeftmostNode(BinaryNode<K, V>* t_root);
	void printBreadthFirstRecursively(BinaryNode<K,V>* t_node_ptr);
	void printSingleLevelRecursively(BinaryNode<K,V>* t_node_ptr, int level);
	// fileIO helper functions
	std::ostream& serializeInorder(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr);
	std::ostream& serializePostorder(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr);
	std::ostream& serializePreorder(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr);
	std::ostream& serializeBreadthFirst(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr);
public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree() : m_root(nullptr), m_out_traverse(0) {}
	BinarySearchTree(const K& t_root_key, const V& t_root_val) { m_root = new BinaryNode<K,V>(t_root_key, t_root_val); }
	// Copy constructor
	BinarySearchTree(const BinarySearchTree<K, V>& t_tree) : BinaryNodeTree<K, V>(t_tree) {}
	virtual ~BinarySearchTree();
	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const { return (this->m_root == nullptr ? true : false); }
	int getHeight() const { return BinaryNodeTree<K, V>::getHeightHelper(this->m_root); }
	int getNumberOfNodes() const { return BinaryNodeTree<K, V>::getNumberOfNodesHelper(this->m_root); }
	K getRootKey() const throw (PrecondViolatedExcep);
	void setRootKey(const K& t_new_key) { this->m_root->setKey(t_new_key); }
	void setRootVal(const K& t_new_val) { this->m_root->setVal(t_new_val); }
	//const throw (PrecondViolatedExcep);
	bool add(const K& t_new_item, const V& newValues);
	bool remove(const K& key, const V& value);
	void clear() { BinaryNodeTree<K, V>::destroyTree(this->m_root); }
	K getKey(const K& t_item) const throw (NotFoundException);
	bool contains(const K& t_item) const;
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
	void preorderTraverse(void visit(K&)) const { BinaryNodeTree<K, V>::preorder(visit, this->m_root); }
	void inorderTraverse(void visit(K&)) const { BinaryNodeTree<K, V>::inorder(visit, this->m_root); }
	void postorderTraverse(void visit(K&)) const { BinaryNodeTree<K, V>::postorder(visit, this->m_root); }
	void breadthFirstTraverse(void visit(K&)) const { BinaryNodeTree<K, V>::breadthFirst(visit, this->m_root); }
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<K, V>& operator=(const BinarySearchTree<K, V>& t_rhs);
	/* Outputs to the ostream object using the << operator
	@pre the order for traversal is between 0 and 3 (inclusive)
	@post binarySearchTree data is written to the ostream object according to the current set
	order of output traversal*/
	template <typename U, typename W>      // all instantiations of this template are my friends
	friend std::ostream& operator<<(std::ostream& t_out, BinarySearchTree<U, W>& t_bst);
	//------------------------------------------------------------
	//  Serialization Section
	//------------------------------------------------------------
	std::ostream& serializeInorderTraverse(std::ostream& t_out) { return this->serializeInorder(t_out, this->m_root); }
	std::ostream& serializePostorderTraverse(std::ostream& t_out) { return this->serializePostorder(t_out, this->m_root); }
	std::ostream& serializePreorderTraverse(std::ostream& t_out) { return this->serializePreorder(t_out, this->m_root); }
	std::ostream& serializeBreadthFirstTraverse(std::ostream& t_out) { return this->serializeBreadthFirst(t_out, this->m_root); }
	void printBreadthFirst() { this->printBreadthFirstRecursively(this->m_root); }

}; // end BinarySearchTree


template <typename K, typename V>
void BinarySearchTree<K,V>::printBreadthFirstRecursively(BinaryNode<K,V>* t_node_ptr)
{
	int height = this->getHeight();
	for (int i = 1; i <= height; i++)
	{
		std::cout << "Level " << i << " \t ";
		this->printSingleLevelRecursively(t_node_ptr, i);
		std::cout << std::endl;
	}
}
template <typename K, typename V>
void BinarySearchTree<K,V>::printSingleLevelRecursively(BinaryNode<K,V>* t_node_ptr, int level)
{
	if (t_node_ptr == nullptr)
		return;
	if (level == 1)
		std::cout << "Keyword: " << t_node_ptr->getKey() << "\nMovie: " << t_node_ptr->getVal();
	else if (level > 1)
	{
		this->printSingleLevelRecursively(t_node_ptr->getLeftChildPtr(), level - 1);
		this->printSingleLevelRecursively(t_node_ptr->getRightChildPtr(), level - 1);
	}
}
template <typename K, typename V>
std::ostream& BinarySearchTree<K, V>::serializeBreadthFirst(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr)
{
	Queue<BinaryNode<K, V>*> node_q;
	if (t_node_ptr == nullptr)
		return t_out;
	node_q.enqueue(t_node_ptr);

	while (!node_q.is_empty())
	{
		BinaryNode<K, V>* pNode = node_q.front();
		if (pNode != nullptr)
		{
			K item = pNode->getKey();
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

template <typename K, typename V>
K BinarySearchTree<K, V>::getRootKey() const throw (PrecondViolatedExcep)
{
	if (!this->isEmpty())
		return this->m_root->getKey();
	else
		throw PrecondViolatedExcep("No data in root node");
}
template <typename U, typename W>
std::ostream& operator<<(std::ostream& t_out, BinarySearchTree<U, W>& t_bst)
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
template <typename K, typename V>
std::ostream& BinarySearchTree<K, V>::serializeInorder(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr)
{
	if (t_node_ptr != nullptr)
	{
		this->serializeInorder(t_out, t_node_ptr->getLeftChildPtr());
		t_out << t_node_ptr->getKey() ;
		this->serializeInorder(t_out, t_node_ptr->getRightChildPtr());
	}
	return t_out;

}
template <typename K, typename V>
std::ostream&  BinarySearchTree<K, V>::serializePreorder(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr)
{
	if (t_node_ptr != nullptr)
	{
		t_out << t_node_ptr->getKey() ;
		this->serializePreorder(t_out, t_node_ptr->getLeftChildPtr());
		this->serializePreorder(t_out, t_node_ptr->getRightChildPtr());

	}
	return t_out;
}

template <typename K, typename V>
std::ostream& BinarySearchTree<K, V>::serializePostorder(std::ostream& t_out, BinaryNode<K, V>* t_node_ptr)
{
	if (t_node_ptr != nullptr)
	{
		this->serializeInorder(t_out, t_node_ptr->getLeftChildPtr());
		this->serializeInorder(t_out, t_node_ptr->getRightChildPtr());
		t_out << t_node_ptr->getKey() ;
	}
	return t_out;

}
template <class K, class V>
bool BinarySearchTree<K, V>::remove(const K& targetKey, const V& targetValue)
{
	bool success = false;
	this->m_root = this->removeValue(this->m_root, targetKey, targetValue, success);
	return (success ? true : false);
	//throw new NotFoundException("Item not found"));
}

template <class K, class V>
BinaryNode<K, V>* BinarySearchTree<K, V>::removeLeftmostNode(
	BinaryNode<K, V>* t_node_to_delete,
	K& t_inorder_successor)
{
	if (t_node_to_delete->getLeftChildPtr() == nullptr)
	{
		t_inorder_successor = t_node_to_delete->getKey();
		return this->removeNode(t_node_to_delete);
	}
	else
	{
		t_node_to_delete->setLeftChildPtr(this->removeLeftmostNode(t_node_to_delete->getLeftChildPtr(), t_inorder_successor));
		return t_node_to_delete;
		//return this->removeLeftmostNode(t_node_to_delete->getLeftChildPtr, t_inorder_successor);
	}
}

template <class K, class V>
K BinarySearchTree<K, V>::getKey(const K& t_item) const throw (NotFoundException)
{
	bool found_success = false;
	BinaryNode<K, V>* found_node_ptr = this->findNode(this->m_root, t_item);

	if (found_node_ptr == nullptr)
		throw NotFoundException("Item not found");
	else
		return found_node_ptr->getKey();
}
template <class K, class V>
BinaryNode<K, V>* BinarySearchTree<K, V>::getLeftmostNode(BinaryNode<K, V>* t_root)
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
template <class K, class V>
BinaryNode<K, V>* BinarySearchTree<K, V>::removeNode(BinaryNode<K, V>* t_node_to_delete)
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
		BinaryNode<K, V>* node_to_connect = nullptr;
		if (t_node_to_delete->getLeftChildPtr() == nullptr)
			node_to_connect = t_node_to_delete->getRightChildPtr();
		delete t_node_to_delete;
		t_node_to_delete = nullptr;
		return node_to_connect;
	}
	// tree case
	else
	{
		K inord_succ_item;
		BinaryNode<K, V>* temp_node_ptr = this->removeLeftmostNode(t_node_to_delete->getRightChildPtr(), inord_succ_item);
		t_node_to_delete->setRightChildPtr(temp_node_ptr);
		t_node_to_delete->setKey(inord_succ_item);
		return t_node_to_delete;
	}
	return t_node_to_delete;

}
template <class K, class V>
BinaryNode<K, V>* BinarySearchTree<K, V>::removeValue(
	BinaryNode<K, V>* subNode,
	const K& targeKey,
	const V& targetVal,
	bool& t_success)
{
	// tree node is null case
	if (subNode == nullptr)
	{
		t_success = false;
		return nullptr;
	}
	// target found case
	else if (subNode->getKey() == targeKey && subNode->getVal() == targetVal)
	{
		subNode = this->removeNode(subNode);
		t_success = true;
		return subNode;
	}
	// handle left of tree case
	else if (subNode->getKey() > targeKey)
	{
		BinaryNode<K, V>* temp_node_ptr = nullptr;
		temp_node_ptr = this->removeValue(subNode->getLeftChildPtr(), targeKey, targetVal, t_success);
		subNode->setLeftChildPtr(temp_node_ptr);
		return subNode;
	}
	// handle right of tree case
	else
	{
		BinaryNode<K, V>* temp_node_ptr = nullptr;
		temp_node_ptr = this->removeValue(subNode->getRightChildPtr(), targeKey, targetVal, t_success);
		subNode->setRightChildPtr(temp_node_ptr);
		return subNode;
	}
}
template <class K, class V>
BinaryNode<K, V>* BinarySearchTree<K, V>::findNode(
	BinaryNode<K, V>* t_tree_ptr,
	const K& targeKey,
	const V& targeVal) const
{
	bool success = false;
	BinaryNode<K, V>* found_ptr = BinaryNodeTree<K, V>::findNode(t_tree_ptr, targeKey, targeVal, success);
	return found_ptr;
}
template <class K, class V>
bool BinarySearchTree<K, V>::contains(const K& t_target) const
{
	BinaryNode<K, V>* node_found_ptr = nullptr;
	node_found_ptr = this->findNode(this->m_root, t_target);
	return (node_found_ptr != nullptr ? true : false);
}
template <class K, class V>
bool BinarySearchTree<K, V>::add(const K& t_new_item, const V& newValue)
{
	BinaryNode<K, V>* new_node = new BinaryNode<K, V>(t_new_item, newValue);
	this->m_root = this->insertInorder(this->m_root, new_node);
	return true;
}	// end add
template <class K, class V>
BinarySearchTree<K, V>::~BinarySearchTree()
{
	this->clear();
}	// end destructor
template <class K, class V>
BinaryNode<K, V>* BinarySearchTree<K, V>::insertInorder(BinaryNode<K, V>* tree_node, BinaryNode<K, V>* add_node) {
	if (tree_node == nullptr)
		return add_node;
	else if (tree_node->getKey() > add_node->getKey()) {
		BinaryNode<K, V>* temp_node = this->insertInorder(tree_node->getLeftChildPtr(), add_node);
		tree_node->setLeftChildPtr(temp_node);
	}
	else {
		BinaryNode<K, V>* temp_node = insertInorder(tree_node->getRightChildPtr(), add_node);
		tree_node->setRightChildPtr(temp_node);
	}
	return tree_node;
}	// end insertInorder
template <class K, class V>
BinarySearchTree<K, V>& BinarySearchTree<K, V>::operator=(const BinarySearchTree<K, V>& t_rhs)
{
	this->clear();
	this->m_root = this->copyTree(t_rhs.m_root);
	return *this;
}

#endif
