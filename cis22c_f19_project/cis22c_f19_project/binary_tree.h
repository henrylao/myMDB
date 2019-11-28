#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "binary_node.h"
#include "binary_tree_interface.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include "queue.h"

template <typename T>
class BinaryNodeTree : public BinaryTreeInterface<T> 
{
private:
	BinaryNode<T>* m_root;	// pointer to root node
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively count the height of the tree
	int getHeightHelper(BinaryNode<T>* t_sub_node_ptr) const;
	// Recursively count the number of the nodes
	int getNumberOfNodesHelper(BinaryNode<T>* t_sub_node_ptr) const;
	// Recursively deletes all nodes from the tree.
	void destroyTree(BinaryNode<T>* t_sub_node_ptr);
	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced.
	BinaryNode<T>* balancedAdd(BinaryNode<T>* t_sub_node_ptr,
		BinaryNode<T>* new_node_ptr);
	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	BinaryNode<T>* removeValue(BinaryNode<T>* t_sub_node_ptr, const T t_target, bool& t_success);
	// Copies values up the tree to overwrite value in current node until
	// a leaf is reached; the leaf is then removed, since its value is
	// stored in the parent.
	BinaryNode<T>* moveValuesUpTree(BinaryNode<T>* t_sub_node_ptr);
	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	BinaryNode<T>* findNode(BinaryNode<T>* t_node_ptr,
		const T& t_target,
		bool& t_success) const;
	// Copies the tree rooted at t_node_ptr and returns a pointer to
	// the copy.
	BinaryNode<T>*copyTree(const BinaryNode<T>* t_node_ptr) const;
	// Recursive traversal helper methods:
	void preorder(void visit(T&),
		BinaryNode<T>* t_node_ptr) const;
	void inorder(void visit(T&),
		BinaryNode<T>* t_node_ptr) const;
	void postorder(void visit(T&),
		BinaryNode<T>* t_node_ptr) const;
	void breadthFirst(void visit(T&),
		BinaryNode<T>* t_node_ptr) const;
	// Returns the bigger input
	int max(const int& a, const int& b) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const T& t_root_item);
	BinaryNodeTree(const T& t_root_item,
		const BinaryNodeTree<T>* left_node_ptr,
		const BinaryNodeTree<T>* right_node_ptr);
	// Copy constructor
	BinaryNodeTree(const BinaryNodeTree<T>& tree);
	virtual ~BinaryNodeTree();
	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	virtual bool isEmpty() const;
	virtual int getHeight() const;
	virtual int getLevel(const T& target);
	int getNumberOfNodes() const;
	T getRootData() const throw (PrecondViolatedExcep);
	void setRootData(const T& t_item);
	bool add(const T& t_item); // Adds a node
	bool remove(const T& data); // Removes a node
	void clear();
	T getItem(const T& t_item) const throw (NotFoundException);
	bool contains(const T& t_item) const;
	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(T&)) const;
	void inorderTraverse(void visit(T&)) const;
	void postorderTraverse(void visit(T&)) const;
	void breadthFirstTraverse(void visit(T&)) const;
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinaryNodeTree& operator=(const BinaryNodeTree& t_rhs);
}; // end BinaryNodeTree
template <class T>
T BinaryNodeTree<T>::getItem(const T& t_item) const throw (NotFoundException)
{
	bool found_success = false;
	BinaryNode<T>* found_node_ptr = this->findNode(this->m_root, t_item, found_success);

	if (found_node_ptr == nullptr)
		throw NotFoundException("Item not found");
	else 
		return found_node_ptr->getItem();
}

template <class T>
void BinaryNodeTree<T>::setRootData(const T& t_item) 
{
	this->m_root->setItem(t_item);
}	// end setRootData

template <class T>
bool BinaryNodeTree<T>::remove(const T& t_target)
{
	bool removed = false;
	this->removeValue(this->m_root, t_target, removed);
	return removed;
}
template <class T>
BinaryNode<T>* BinaryNodeTree<T>::findNode(BinaryNode<T>* t_node_ptr,
	const T& t_target,
	bool& t_success) const
{
	if (t_node_ptr == nullptr)
	{
		t_success = false;
		return t_node_ptr;
	}
	else {
		if (t_node_ptr->getItem() == t_target)
		{
			t_success = true;
			return t_node_ptr;
		}
		else
		{
			// found on left child node of parent
			BinaryNode<T>* left_node_ptr = this->findNode(t_node_ptr->getLeftChildPtr(), t_target, t_success);
			if (left_node_ptr != nullptr)
			{
				return left_node_ptr;
			}
			// found on right child node of parent
			BinaryNode<T>* right_node_ptr = this->findNode(t_node_ptr->getRightChildPtr(), t_target, t_success);
			if (right_node_ptr != nullptr)
			{
				return right_node_ptr;
			}
		}
	}
	// not found
	return nullptr;
}	// end findNode

template <class T>
bool BinaryNodeTree<T>::contains(const T& t_target) const
{
	bool found = false;
	BinaryNode<T>* node_found_ptr = this->findNode(this->m_root, t_target, found);
	return found;
}	// end contains
template <class T>
int BinaryNodeTree<T>::getNumberOfNodes() const {
	return this->getNumberOfNodesHelper(this->m_root);
}	// end getNumberOfNodes
template <class T>
BinaryNodeTree<T>::~BinaryNodeTree()
{
	this->clear();
}	// end destructor
template <class T>
int BinaryNodeTree<T>::getHeight() const
{
	if (this->m_root == nullptr)
		return 0;
	else 
		return this->getHeightHelper(this->m_root);
}	// end getHeight
template<typename T>
int BinaryNodeTree<T>::getLevel(const T & target)
{	
	int height = this->getHeight();

	return 0;
}
template <class T>
T BinaryNodeTree<T>::getRootData() const throw (PrecondViolatedExcep) {
	if (this->isEmpty())
		throw new PrecondViolatedExcep();
	else
		return this->m_root->getItem();
}	// end getRootData
template <class T>
void BinaryNodeTree<T>::clear() 
{
	BinaryNode<T>* old_root = this->m_root;
	this->destroyTree(old_root);
	this->m_root = nullptr;
}	// end clear
template <class T>
BinaryNodeTree<T>::BinaryNodeTree() : m_root(nullptr)
{
} // end default constructor
template <class T>
BinaryNodeTree<T>::BinaryNodeTree(const T& t_root_item) {
	m_root = new BinaryNode<T>(t_root_item, nullptr, nullptr);
} // end constructor
template <class T>
BinaryNodeTree<T>::BinaryNodeTree(const T& t_root_item,
	const BinaryNodeTree<T>* left_node_ptr,
	const BinaryNodeTree<T>* right_node_ptr)
{
	m_root = new BinaryNode<T>(t_root_item,
		copyTree(left_node_ptr->m_root),
		copyTree(right_node_ptr->m_root));
} // end constructor
template < class T>
BinaryNode<T>* BinaryNodeTree<T>::copyTree(const BinaryNode<T>* t_old_root_ptr) const{
	BinaryNode<T>* new_node_ptr = nullptr;
	// Copy tree nodes during a preorder traversal
	if (t_old_root_ptr != nullptr)
	{
		// Copy node
		new_node_ptr = new BinaryNode<T>(t_old_root_ptr->getItem(),nullptr, nullptr);
		new_node_ptr->setLeftChildPtr(copyTree(t_old_root_ptr->getLeftChildPtr()));
		new_node_ptr->setRightChildPtr(copyTree(t_old_root_ptr->getRightChildPtr()));
	} // end if
	return new_node_ptr;
} // end copyTree
template < class T>
BinaryNodeTree<T>::
BinaryNodeTree(const BinaryNodeTree<T>& t_node_ptr)
{
	m_root = copyTree(t_node_ptr.m_root);
} // end copy constructor
template < class T>
void BinaryNodeTree<T>::
destroyTree(BinaryNode<T>* t_sub_node_ptr)
{
	if (t_sub_node_ptr != nullptr)
	{
		//  postorder tree destruction
		destroyTree(t_sub_node_ptr->getLeftChildPtr());
		destroyTree(t_sub_node_ptr->getRightChildPtr());
		delete t_sub_node_ptr;
	} // end if
} // end destroyTree
template < class T>
int BinaryNodeTree<T>::getHeightHelper(BinaryNode<T>* t_sub_node_ptr) const
{
	if (t_sub_node_ptr == nullptr)
		return 0;
	else
		return ( 1 + this->max(this->getHeightHelper(t_sub_node_ptr->getLeftChildPtr()),
			this->getHeightHelper(t_sub_node_ptr->getRightChildPtr())));
} // end getHeightHelper
template < class T>
bool BinaryNodeTree<T>::add(const T& t_item)
{
	BinaryNode<T>* new_node_ptr = new BinaryNode<T>(t_item);
	m_root = balancedAdd(m_root, new_node_ptr);
	return true;
} // end add
template < class T>
BinaryNode<T>* BinaryNodeTree<T>::balancedAdd(
	BinaryNode<T>* t_sub_node_ptr,
	BinaryNode<T>* t_new_node_ptr)
{
	if (t_sub_node_ptr == nullptr)
		return t_new_node_ptr;
	else
	{
		BinaryNode<T>* leftPtr = t_sub_node_ptr->getLeftChildPtr();
		BinaryNode<T>* rightPtr = t_sub_node_ptr->getRightChildPtr();
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

template < class T>
void BinaryNodeTree<T>::inorder(
	void visit(T&),
	BinaryNode<T>* t_node_ptr) const
{
	if (t_node_ptr != nullptr)
	{
		inorder(visit, t_node_ptr->getLeftChildPtr());
		T theItem = t_node_ptr->getItem();
		visit(theItem);
		inorder(visit, t_node_ptr->getRightChildPtr());
	} // end if
} // end inorder

template < class T>
void BinaryNodeTree<T>::preorder(
	void visit(T&),
	BinaryNode<T>* t_node_ptr) const
{
	if (t_node_ptr != nullptr)
	{
		T theItem = t_node_ptr->getItem();
		visit(theItem);
		preorder(visit, t_node_ptr->getLeftChildPtr());
		preorder(visit, t_node_ptr->getRightChildPtr());
	} // end if
} // end preorder
template < class T>
void BinaryNodeTree<T>::postorder(
	void visit(T&),
	BinaryNode<T>* t_node_ptr) const
{
	if (t_node_ptr != nullptr)
	{
		postorder(visit, t_node_ptr->getLeftChildPtr());
		postorder(visit, t_node_ptr->getRightChildPtr());
		T theItem = t_node_ptr->getItem();
		visit(theItem);
	} // end if
} // end postorder
template<typename T>
void BinaryNodeTree<T>::breadthFirst(void visit(T&), BinaryNode<T>* t_node_ptr) const
{
	Queue<BinaryNode<T>*> node_q;

	if (t_node_ptr == nullptr)
		return;
	node_q.enqueue(t_node_ptr);

	while (!node_q.is_empty())
	{
		BinaryNode<T>* pNode = node_q.front();
		if (pNode != nullptr)
		{
			T item = pNode->getItem();
			visit(item);
			node_q.dequeue();
			if (pNode->getLeftChildPtr() != nullptr)
				node_q.enqueue(pNode->getLeftChildPtr());
			if (pNode->getRightChildPtr() != nullptr)
				node_q.enqueue(pNode->getRightChildPtr());
		}
	}

}
template < class T>
int BinaryNodeTree<T>::getNumberOfNodesHelper(BinaryNode<T>* t_sub_node_ptr) const {
	if (t_sub_node_ptr == nullptr)
		return 0;
	else
		return (1 + this->getNumberOfNodesHelper(t_sub_node_ptr->getLeftChildPtr()) 
			+ this->getNumberOfNodesHelper(t_sub_node_ptr->getRightChildPtr()));
} // end getNumberOfNodesHelper

template < class T>
BinaryNode<T>* BinaryNodeTree<T>::moveValuesUpTree(BinaryNode<T>* t_sub_node_ptr) {
	BinaryNode<T>* left_child_ptr = nullptr;
	BinaryNode<T>* right_note_ptr = nullptr;
	left_child_ptr = t_sub_node_ptr->getLeftChildPtr();
	right_note_ptr = t_sub_node_ptr->getRightChildPtr();
	
	if (left_child_ptr == nullptr && right_note_ptr == nullptr)
	{
		if (t_sub_node_ptr == this->m_root)
			this->m_root = nullptr;
		t_sub_node_ptr = nullptr;
		return t_sub_node_ptr;
	}	
	else
	{
		if (left_child_ptr != nullptr)
		{
			t_sub_node_ptr->setItem(left_child_ptr->getItem());
			t_sub_node_ptr->setLeftChildPtr(this->moveValuesUpTree(left_child_ptr));
		}	
		else
		{
			t_sub_node_ptr->setItem(right_note_ptr->getItem());
			t_sub_node_ptr->setLeftChildPtr(this->moveValuesUpTree(right_note_ptr));

		}	// end if
	}	// end if
	return t_sub_node_ptr;
}	//	end moveValuesUpTree
template < class T>
BinaryNode<T>* BinaryNodeTree<T>::removeValue(
	BinaryNode<T>* t_sub_node_ptr,
	const T t_target, bool& t_success) 
{
	//// DEBUG
	//std::cout << "Parent: ";
	//if (t_sub_node_ptr != nullptr)
	//{
	//	std::cout << t_sub_node_ptr->getItem() << std::endl;

	//	std::cout << "Left: ";
	//	if (t_sub_node_ptr->getLeftChildPtr() != nullptr)
	//		std::cout << t_sub_node_ptr->getLeftChildPtr()->getItem();
	//	else
	//		std::cout << "None";
	//	std::cout << " Right: ";
	//	if (t_sub_node_ptr->getRightChildPtr() != nullptr)
	//		std::cout << t_sub_node_ptr->getRightChildPtr()->getItem() << std::endl;
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
		if (t_sub_node_ptr->getItem() == t_target)
		{
			t_sub_node_ptr = moveValuesUpTree(t_sub_node_ptr);
			t_success = true;
			return t_sub_node_ptr;
		}
		// check child nodes
		else 
		{
			// check left child
			BinaryNode<T>* target_node_ptr = removeValue(t_sub_node_ptr->getLeftChildPtr(), t_target, t_success);
			t_sub_node_ptr->setLeftChildPtr(target_node_ptr);
			if (!t_success)
			{
				target_node_ptr = removeValue(t_sub_node_ptr->getRightChildPtr(), t_target, t_success);
				t_sub_node_ptr->setRightChildPtr(target_node_ptr);
			}	// end if
			return t_sub_node_ptr;
		}
	}

}	// end removeValue
template < class T>
void BinaryNodeTree<T>::inorderTraverse(void visit(T&)) const
{
	this->inorder(visit, this->m_root);
}	// end inorderTraverse
template < class T>
void BinaryNodeTree<T>::preorderTraverse(void visit(T&)) const
{
	this->preorder(visit, this->m_root);
}	// end preorderTraverse
template < class T>
void BinaryNodeTree<T>::postorderTraverse(void visit(T&)) const
{
	this->postorder(visit, this->m_root);
}	// end postorderTraverse
template<typename T>
void BinaryNodeTree<T>::breadthFirstTraverse(void visit(T&)) const
{
	this->breadthFirst(visit, this->m_root);
}
template < class T>
bool BinaryNodeTree<T>::isEmpty() const {
	return (this->m_root == nullptr ? true : false);
} // end isEmpty
template <class T> 
int BinaryNodeTree<T>::max(const int& a, const int& b) const {
	return (a < b) ? b : a;     // or: return comp(a,b)?b:a; for version (2)

}// end max
template<class T>
BinaryNodeTree<T>& BinaryNodeTree<T>::operator=(const BinaryNodeTree<T>& t_rhs)
{
	this->clear();
	this->m_root = this->copyTree(t_rhs.m_root);
	return *this;
}  // end operator=
#endif