
#ifndef HEAD_NODE_H
#define HEAD_NODE_H

#include "link_node.h"

template <class T>
class HeadNode : protected LinkNode<T> {
public:
	HeadNode();
	HeadNode(LinkNode<T>& t_node);
	HeadNode(LinkNode<T>* t_head);

	LinkNode<T>* get_first() const;
	void set_first(LinkNode<T>* t_head);

	LinkNode<T>* get_last() const;
	void set_last(LinkNode<T>* t_tail);

	size_t size() const;
	void set_size(int  t_size);

private:
	LinkNode<T>* m_tail;
	int m_size;
};

// creates a head node with pointing to nothing
template <class T>
HeadNode<T>::HeadNode() : LinkNode<T>(), m_tail{ nullptr }, m_size{ 0 } {

}

// creates a head node pointing to a given node
template <class T>
HeadNode<T>::HeadNode(LinkNode<T>& t_node) : LinkNode<T>(), m_tail{ &t_node }, m_size{ 1 } {
	set_first(&t_node);
}

// creates a head node pointing to a given node through a pointer
template <class T>
HeadNode<T>::HeadNode(LinkNode<T>* t_head) : LinkNode<T>(), m_tail{ t_head }, m_size{ 1 } {
	set_first(t_head);
}

template <class T>
LinkNode<T>* HeadNode<T>::get_first() const {
	return LinkNode<T>::get_next();
}

template <class T>
void HeadNode<T>::set_first(LinkNode<T>* t_head) {
	LinkNode<T>::set_next( t_head);
}

template <class T>
LinkNode<T>* HeadNode<T>::get_last() const {
	return m_tail;
}

template <class T>
void HeadNode<T>::set_last(LinkNode<T>* t_tail) {
	m_tail = t_tail;
}

template <class T>
size_t HeadNode<T>::size() const {
	return m_size;
}

template <class T>
void HeadNode<T>::set_size(int  t_size) {
	m_size =  t_size;
}

#endif // HEAD_NODE_H