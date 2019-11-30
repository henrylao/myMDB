#ifndef _HASH_TABLE_NODE_H
#define _HASH_TABLE_NODE_H

#include <string>

template <typename T>
class HashTableNode
{
private:
	std::string		__key;
	T				__value;	
	size_t			__hashID;		// bucket position with respect to table position
	bool			__collide;

public:
	HashTableNode(std::string key, size_t hashID, const T& value, bool collide);
	T&				getValue();
	std::string&	getKey();
	size_t			getHashID() const;
	bool			hasCollision() const;
	template <class U>
	friend std::ostream& operator<< (std::ostream &out, const HashTableNode<U>& node);
};

template <typename T>
std::ostream& operator< (std::ostream &out, const HashTableNode<T>& node)
{
	out << node;
	return out;
}
template <typename T>
HashTableNode<T>::HashTableNode(std::string key, size_t hashID, const T& value, bool collide)
{
	__key = key;
	__hashID = hashID;
	__value = value;
	__collide = collide;
}
template <typename T>
T& HashTableNode<T>::getValue() { return this->__value; }

template <typename T>
std::string& HashTableNode<T>::getKey() { return this->__key; }

template <typename T>
size_t HashTableNode<T>::getHashID() const { return this->__hashID; }

template <typename T>
bool HashTableNode<T>::hasCollision() const { return this->__collide; }

#endif // _HASH_TABLE_NODE_H
