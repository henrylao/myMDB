#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "binary_node_kvpair.h"
#include "binary_tree_interface_kvpair.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include "queue.h"

template <typename K, typename V>
class BinaryNodeTree 
{
private:
	BinaryNode<K, V>*	__root;	// pointer to root node
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively count the height of the tree
	int getHeightHelper(BinaryNode<K, V>* t_sub_node_ptr) const;
	// Recursively count the number of the nodes
	int getNumberOfNodesHelper(BinaryNode<K, V>* t_sub_node_ptr) const;
	// Recursively deletes all nodes from the tree.
	void destroyTree(BinaryNode<K, V>* t_sub_node_ptr);
	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced.
	BinaryNode<K, V>* balancedAdd(BinaryNode<K, V>* t_sub_node_ptr,
		BinaryNode<K, V>* new_node_ptr);
	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	BinaryNode<K, V>* removeValue(BinaryNode<K, V>* t_sub_node_ptr, const K target, bool& t_success);
	// Copies values up the tree to overwrite value in current node until
	// a leaf is reached; the leaf is then removed, since its value is
	// stored in the parent.
	BinaryNode<K, V>* moveValuesUpTree(BinaryNode<K, V>* t_sub_node_ptr);
	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	BinaryNode<K, V>* findNode(BinaryNode<K, V>* pNode,
		const K& target,
		bool& t_success) const;
	// Copies the tree rooted at pNode and returns a pointer to
	// the copy.
	BinaryNode<K, V>*copyTree(const BinaryNode<K, V>* pNode) const;
	// Recursive traversal helper methods:
	void preorder(void visit(K&),
		BinaryNode<K, V>* pNode) const;
	void inorder(void visit(K&),
		BinaryNode<K, V>* pNode) const;
	void postorder(void visit(K&),
		BinaryNode<K, V>* pNode) const;
	void breadthFirst(void visit(K&),
		BinaryNode<K, V>* pNode) const;
	// Returns the bigger input
	int max(const int& a, const int& b) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const K& t_root_key, const V& t_root_val);
	BinaryNodeTree(const K& t_root_key, const V& t_root_val,
		const BinaryNodeTree<K, V>* lefpNode,
		const BinaryNodeTree<K, V>* righpNode);
	// Copy constructor
	BinaryNodeTree(const BinaryNodeTree<K, V>& tree);
	virtual ~BinaryNodeTree();
	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	virtual bool isEmpty() const;
	virtual int getHeight() const;
	virtual int getLevel(const K& target);
	int getNumberOfNodes() const;
	K getRootKey() const throw (PrecondViolatedExcep);
	V getRootVal() const throw (PrecondViolatedExcep);
	void setRootData(const K& t_key);
	bool add(const K& t_key, const V& t_val); // Adds a node
	bool remove(const K& data); // Removes a node
	void clear();
	K getKey(const K& t_key) const throw (NotFoundException);
	bool contains(const K& t_key) const;
	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(K&)) const;
	void inorderTraverse(void visit(K&)) const;
	void postorderTraverse(void visit(K&)) const;
	void breadthFirstTraverse(void visit(K&)) const;
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinaryNodeTree& operator=(const BinaryNodeTree& t_rhs);
}; // end BinaryNodeTree
template <class K, class V>
K BinaryNodeTree<K, V>::getKey(const K& t_key) const throw (NotFoundException)
{
	bool found_success = false;
	BinaryNode<K, V>* found_node_ptr = this->findNode(this->__root, t_key, found_success);

	if (found_node_ptr == nullptr)
		throw NotFoundException("Key not found");
	else 
		return found_node_ptr->getKey();
}

template <class K, class V>
void BinaryNodeTree<K, V>::setRootData(const K& t_key) 
{
	this->__root->setItem(t_key);
}	// end setRootData

template <class K, class V>
bool BinaryNodeTree<K, V>::remove(const K& target)
{
	bool removed = false;
	this->removeValue(this->__root, target, removed);
	return removed;
}
template <class K, class V>
BinaryNode<K, V>* BinaryNodeTree<K, V>::findNode(BinaryNode<K, V>* pNode,
	const K& target,
	bool& t_success) const
{
	if (pNode == nullptr)
	{
		t_success = false;
		return pNode;
	}
	else {
		if (pNode->getKey() == target)
		{
			t_success = true;
			return pNode;
		}
		else
		{
			// found on left child node of parent
			BinaryNode<K, V>* lefpNode = this->findNode(pNode->getLeftChildPtr(), target, t_success);
			if (lefpNode != nullptr)
			{
				return lefpNode;
			}
			// found on right child node of parent
			BinaryNode<K, V>* righpNode = this->findNode(pNode->getRightChildPtr(), target, t_success);
			if (righpNode != nullptr)
			{
				return righpNode;
			}
		}
	}
	// not found
	return nullptr;
}	// end findNode

template <class K, class V>
bool BinaryNodeTree<K, V>::contains(const K& target) const
{
	bool found = false;
	BinaryNode<K, V>* node_found_ptr = this->findNode(this->__root, target, found);
	return found;
}	// end contains
template <class K, class V>
int BinaryNodeTree<K, V>::getNumberOfNodes() const {
	return this->getNumberOfNodesHelper(this->__root);
}	// end getNumberOfNodes
template <class K, class V>
BinaryNodeTree<K, V>::~BinaryNodeTree()
{
	this->clear();
}	// end destructor
template <class K, class V>
int BinaryNodeTree<K, V>::getHeight() const
{
	if (this->__root == nullptr)
		return 0;
	else 
		return this->getHeightHelper(this->__root);
}	// end getHeight
template <typename K, typename V>
int BinaryNodeTree<K, V>::getLevel(const K& target)
{	
	int height = this->getHeight();

	return 0;
}
template <class K, class V>
K BinaryNodeTree<K, V>::getRootKey() const throw (PrecondViolatedExcep) {
	if (this->isEmpty())
		throw new PrecondViolatedExcep();
	else
		return this->__root->getKey();
}	// end getRootKey

template<typename K, typename V>
V BinaryNodeTree<K, V>::getRootVal() const throw(PrecondViolatedExcep)
{
	if (this->isEmpty())
		throw new PrecondViolatedExcep();
	else
		return this->__root->getVal();
}
template <class K, class V>
void BinaryNodeTree<K, V>::clear() 
{
	BinaryNode<K, V>* old_root = this->__root;
	this->destroyTree(old_root);
	this->__root = nullptr;
}	// end clear
template <class K, class V>
BinaryNodeTree<K, V>::BinaryNodeTree() : __root(nullptr)
{
} // end default constructor
template <class K, class V>
BinaryNodeTree<K, V>::BinaryNodeTree(const K& t_root_key, const V& t_root_val) {
	__root = new BinaryNode<K, V>(t_root_key, nullptr, nullptr);
} // end constructor
template <class K, class V>
BinaryNodeTree<K, V>::BinaryNodeTree(const K& t_root_key, const V& t_root_val,
	const BinaryNodeTree<K, V>* lefpNode,
	const BinaryNodeTree<K, V>* righpNode)
{
	__root = new BinaryNode<K, V>(t_root_key,
		copyTree(lefpNode->__root),
		copyTree(righpNode->__root));
} // end constructor
template <class K, class V>
BinaryNode<K, V>* BinaryNodeTree<K, V>::copyTree(const BinaryNode<K, V>* t_old_root_ptr) const{
	BinaryNode<K, V>* new_node_ptr = nullptr;
	// Copy tree nodes during a preorder traversal
	if (t_old_root_ptr != nullptr)
	{
		// Copy node
		new_node_ptr = new BinaryNode<K, V>(t_old_root_ptr->getKey(), t_old_root_ptr->getVal());
		new_node_ptr->setLeftChildPtr(copyTree(t_old_root_ptr->getLeftChildPtr()));
		new_node_ptr->setRightChildPtr(copyTree(t_old_root_ptr->getRightChildPtr()));
	} // end if
	return new_node_ptr;
} // end copyTree
template <class K, class V>
BinaryNodeTree<K, V>::
BinaryNodeTree(const BinaryNodeTree<K, V>& pNode)
{
	__root = copyTree(pNode.__root);
} // end copy constructor
template <class K, class V>
void BinaryNodeTree<K, V>::
destroyTree(BinaryNode<K, V>* t_sub_node_ptr)
{
	if (t_sub_node_ptr != nullptr)
	{
		//  postorder tree destruction
		destroyTree(t_sub_node_ptr->getLeftChildPtr());
		destroyTree(t_sub_node_ptr->getRightChildPtr());
		delete t_sub_node_ptr;
	} // end if
} // end destroyTree
template <class K, class V>
int BinaryNodeTree<K, V>::getHeightHelper(BinaryNode<K, V>* t_sub_node_ptr) const
{
	if (t_sub_node_ptr == nullptr)
		return 0;
	else
		return ( 1 + this->max(this->getHeightHelper(t_sub_node_ptr->getLeftChildPtr()),
			this->getHeightHelper(t_sub_node_ptr->getRightChildPtr())));
} // end getHeightHelper
template <class K, class V>
bool BinaryNodeTree<K, V>::add(const K& t_key, const V& t_val)
{
	BinaryNode<K, V>* new_node_ptr = new BinaryNode<K, V>(t_key, t_val);
	__root = balancedAdd(__root, new_node_ptr);
	return true;
} // end add
template <class K, class V>
BinaryNode<K, V>* BinaryNodeTree<K, V>::balancedAdd(
	BinaryNode<K, V>* t_sub_node_ptr,
	BinaryNode<K, V>* t_new_node_ptr)
{
	if (t_sub_node_ptr == nullptr)
		return t_new_node_ptr;
	else
	{
		BinaryNode<K, V>* leftPtr = t_sub_node_ptr->getLeftChildPtr();
		BinaryNode<K, V>* rightPtr = t_sub_node_ptr->getRightChildPtr();
		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, t_new_node_ptr);
			t_sub_node_ptr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, t_new_node_ptr);
			t_sub_node_ptr->setLeftChildPtr(leftPtr);
		} // end if
		return t_sub_node_ptr;
	} // end if
} // end balancedAdd

template <class K, class V>
void BinaryNodeTree<K, V>::inorder(
	void visit(K&),
	BinaryNode<K, V>* pNode) const
{
	if (pNode != nullptr)
	{
		inorder(visit, pNode->getLeftChildPtr());
		K theItem = pNode->getKey();
		visit(theItem);
		inorder(visit, pNode->getRightChildPtr());
	} // end if
} // end inorder

template <class K, class V>
void BinaryNodeTree<K, V>::preorder(
	void visit(K&),
	BinaryNode<K, V>* pNode) const
{
	if (pNode != nullptr)
	{
		K theItem = pNode->getKey();
		visit(theItem);
		preorder(visit, pNode->getLeftChildPtr());
		preorder(visit, pNode->getRightChildPtr());
	} // end if
} // end preorder
template <class K, class V>
void BinaryNodeTree<K, V>::postorder(
	void visit(K&),
	BinaryNode<K, V>* pNode) const
{
	if (pNode != nullptr)
	{
		postorder(visit, pNode->getLeftChildPtr());
		postorder(visit, pNode->getRightChildPtr());
		K theItem = pNode->getKey();
		visit(theItem);
	} // end if
} // end postorder
template <typename K, typename V>
void BinaryNodeTree<K, V>::breadthFirst(void visit(K&), BinaryNode<K, V>* pNode) const
{
	Queue<BinaryNode<K, V>*> node_q;

	if (pNode == nullptr)
		return;
	node_q.enqueue(pNode);

	while (!node_q.is_empty())
	{
		BinaryNode<K, V>* pNode = node_q.front();
		if (pNode != nullptr)
		{
			K item = pNode->getKey();
			visit(item);
			node_q.dequeue();
			if (pNode->getLeftChildPtr() != nullptr)
				node_q.enqueue(pNode->getLeftChildPtr());
			if (pNode->getRightChildPtr() != nullptr)
				node_q.enqueue(pNode->getRightChildPtr());
		}
	}

}
template <class K, class V>
int BinaryNodeTree<K, V>::getNumberOfNodesHelper(BinaryNode<K, V>* t_sub_node_ptr) const {
	if (t_sub_node_ptr == nullptr)
		return 0;
	else
		return (1 + this->getNumberOfNodesHelper(t_sub_node_ptr->getLeftChildPtr()) 
			+ this->getNumberOfNodesHelper(t_sub_node_ptr->getRightChildPtr()));
} // end getNumberOfNodesHelper

template <class K, class V>
BinaryNode<K, V>* BinaryNodeTree<K, V>::moveValuesUpTree(BinaryNode<K, V>* t_sub_node_ptr) {
	BinaryNode<K, V>* left_child_ptr = nullptr;
	BinaryNode<K, V>* right_note_ptr = nullptr;
	left_child_ptr = t_sub_node_ptr->getLeftChildPtr();
	right_note_ptr = t_sub_node_ptr->getRightChildPtr();
	
	if (left_child_ptr == nullptr && right_note_ptr == nullptr)
	{
		if (t_sub_node_ptr == this->__root)
			this->__root = nullptr;
		t_sub_node_ptr = nullptr;
		return t_sub_node_ptr;
	}	
	else
	{
		if (left_child_ptr != nullptr)
		{
			t_sub_node_ptr->setItem(left_child_ptr->getKey());
			t_sub_node_ptr->setLeftChildPtr(this->moveValuesUpTree(left_child_ptr));
		}	
		else
		{
			t_sub_node_ptr->setItem(right_note_ptr->getKey());
			t_sub_node_ptr->setLeftChildPtr(this->moveValuesUpTree(right_note_ptr));

		}	// end if
	}	// end if
	return t_sub_node_ptr;
}	//	end moveValuesUpTree
template <class K, class V>
BinaryNode<K, V>* BinaryNodeTree<K, V>::removeValue(
	BinaryNode<K, V>* t_sub_node_ptr,
	const K target, bool& t_success) 
{
	//// DEBUG
	//std::cout << "Parent: ";
	//if (t_sub_node_ptr != nullptr)
	//{
	//	std::cout << t_sub_node_ptr->getKey() << std::endl;

	//	std::cout << "Left: ";
	//	if (t_sub_node_ptr->getLeftChildPtr() != nullptr)
	//		std::cout << t_sub_node_ptr->getLeftChildPtr()->getKey();
	//	else
	//		std::cout << "None";
	//	std::cout << " Right: ";
	//	if (t_sub_node_ptr->getRightChildPtr() != nullptr)
	//		std::cout << t_sub_node_ptr->getRightChildPtr()->getKey() << std::endl;
	//	else
	//		std::cout << "None\n";
	//}
	//else 
	//	std::cout << "None\n";
	//// end DEBUG
	
	// empty tree case
	if (t_sub_node_ptr == nullptr)
	{
		t_success = false;
		return nullptr;
	}
	// non-empty tree
	else
	{
		// parent node contains target
		if (t_sub_node_ptr->getKey() == target)
		{
			t_sub_node_ptr = moveValuesUpTree(t_sub_node_ptr);
			t_success = true;
			return t_sub_node_ptr;
		}
		// check child nodes
		else 
		{
			// check left child
			BinaryNode<K, V>* targepNode = removeValue(t_sub_node_ptr->getLeftChildPtr(), target, t_success);
			t_sub_node_ptr->setLeftChildPtr(targepNode);
			if (!t_success)
			{
				targepNode = removeValue(t_sub_node_ptr->getRightChildPtr(), target, t_success);
				t_sub_node_ptr->setRightChildPtr(targepNode);
			}	// end if
			return t_sub_node_ptr;
		}
	}

}	// end removeValue
template <class K, class V>
void BinaryNodeTree<K, V>::inorderTraverse(void visit(K&)) const
{
	this->inorder(visit, this->__root);
}	// end inorderTraverse
template <class K, class V>
void BinaryNodeTree<K, V>::preorderTraverse(void visit(K&)) const
{
	this->preorder(visit, this->__root);
}	// end preorderTraverse
template <class K, class V>
void BinaryNodeTree<K, V>::postorderTraverse(void visit(K&)) const
{
	this->postorder(visit, this->__root);
}	// end postorderTraverse
template <typename K, typename V>
void BinaryNodeTree<K, V>::breadthFirstTraverse(void visit(K&)) const
{
	this->breadthFirst(visit, this->__root);
}
template <class K, class V>
bool BinaryNodeTree<K, V>::isEmpty() const {
	return (this->__root == nullptr ? true : false);
} // end isEmpty
template <class K, class V> 
int BinaryNodeTree<K, V>::max(const int& a, const int& b) const {
	return (a < b) ? b : a;     // or: return comp(a,b)?b:a; for version (2)

}// end max
template<class K, class V>
BinaryNodeTree<K, V>& BinaryNodeTree<K, V>::operator=(const BinaryNodeTree<K, V>& t_rhs)
{
	this->clear();
	this->__root = this->copyTree(t_rhs.__root);
	return *this;
}  // end operator=
#endif