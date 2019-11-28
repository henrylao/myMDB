
#ifndef LINK_NODE_H
#define LINK_NODE_H

template <class T>
class LinkNode {
public:
	LinkNode();
	LinkNode(LinkNode<T>& t_node);
	LinkNode(T t_data, LinkNode<T>* t_next);

	T get_item() const;
	T& __get_item();
	void set_item(const T& t_data);

	LinkNode* get_next() const;
	void set_next(LinkNode<T>* t_next);

private:
	T m_item;
	LinkNode* m_next;
};

template <class T>
LinkNode<T>::LinkNode() : m_next{ nullptr } {
}

template <class T>
LinkNode<T>::LinkNode(LinkNode<T>& t_node) : m_item{ t_node.m_item }, m_next{ t_node.m_next } {

}

template <class T>
LinkNode<T>::LinkNode(T t_data, LinkNode<T>* t_next) : m_item{ t_data }, m_next{ t_next } {

}

template <class T>
T LinkNode<T>::get_item() const {
	return m_item;
}
template <class T>
T& LinkNode<T>::__get_item() {
	return m_item;
}

template <class T>
void LinkNode<T>::set_item(const T& t_data) {
	m_item = t_data;
}

template <class T>
LinkNode<T>* LinkNode<T>::get_next() const {
	return m_next;
}

template <class T>
void LinkNode<T>::set_next(LinkNode<T>* t_next) {
	m_next = t_next;
}


#endif // NODE_H