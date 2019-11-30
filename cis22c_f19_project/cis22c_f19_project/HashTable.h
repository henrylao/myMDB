#ifndef  _HASH_TABLE_H
#define _HASH_TABLE_H

#include "HashUtil.h"
#include "MathUtil.h"
#include <string>
#include "List.h"
#include "HashTableNode.h"
#include <fstream>
#include <iostream>
template <typename T>
class HashTable
{
	
private:
	List<std::string>*			__keys;
	HashTableNode<T>**			__table;
	size_t						__collisionCount;
	size_t						__capacity; 
	size_t						__occupancy;
	size_t						__resizeCount;
	std::ofstream				__log;
	bool						__hitLimit;
	
	// ------------------------------------------
	// Internal	Table Management Section
	// ------------------------------------------

	/* This function utilizes the MathUtil package
	in finding and generating a prime table size selecting the first
	prime number element of a read row greater than the input
	table size.
	@return unsigned integer signifying the hashtable size
	@param quantityToAdd is the number of key-value pairs to be added */
	size_t					__findNextPrime(size_t quantityToAdd);
	/* This is an internal function for clearing allocated memory for the TableNodes 
	containing a key-value pair
	@pre hashTable stores key-value pairs
	@post hashTable is emptied */
	void					__clear();
	/* This is an internal function for dynamically resizing the hashtable
	during insertion of values. The function finds the next prime value greater
	than twice the current capacity size. 
	@pre hashtable size is either to small for insertion of elements or is too small for
	efficient quadratic searching of hashed key-value pairs
	@post hashtable size is a prime value 2 times greater than the former */
	void					__resize();
	/* This functions finds the hashID (index) on the array quadratically probing
	for the value associated with the key
	@pre key follows the format YYYY-MM-DD 
	@return -1 if not found else a positive integer less than the table's capacity */
	int						__find(std::string key) const;
	
public:
	// -------------------------------------
	// Constructors and Destructors Section
	// -------------------------------------

	/* Dynamically generates a table expected to be at 
	a max of 50% load factor after all data objects of the
	quantity to add have been inserted into the table */
	HashTable(size_t quantityToAdd);
	HashTable();
	virtual ~HashTable();

	// -------------------------------------
	// Mutator Section
	// -------------------------------------

	/* The add function utilizes quadratic probing 
	for generating a hashID when adding a string key and generic value
	pair into the table. The function first checks the load factor
	to be less than 50% from which it resizes if greater than 50% 
	before insertion.
	@post key is hashed and the generic value is added into the table 
	@param key is a string of the date format: YYYY-MM-DD
	@param value any generic value */
	bool				add(std::string key, const T& value);
	/* The remove function utilizes the internal find function
	to verify the keys existence throwing an exception when the
	key is not found. If the key exists, the value associated with the key
	is deleted from the table.
	@post memory allocated for the key-value pair is deleted
	@param key is a string of the date format: YYYY-MM-DD 	*/
	bool				remove(std::string key);
	/* The get function utilizes the internal find function
	to verify the keys existence throwing an exception when the
	key is not found. If the key exists, the value associated with the key
	is returned from the table.
	@param key is a string of the date format: YYYY-MM-DD 	*/
	T					get(std::string key) const;

	// -------------------------------------
	// Getter Section
	// -------------------------------------
	List<std::string>	keys() const;
	bool				isEmpty() const;
	size_t				size() const;
	size_t				capacity() const;
	size_t				collisions() const;
	size_t				resizeQuantity() const;
	double				loadFactor()  const;
	void				display();
	void				empty();

	// -------------------------------------
	// Operator Overload Section
	// -------------------------------------
	T operator[](std::string key) const;	
	T& operator[](std::string key);	
	template<typename U>
	friend std::ostream& operator<<(std::ostream& out,  HashTable<U>& table);

};

// -------------------------------------
// Constructors and Destructors Section
// -------------------------------------
template<typename T>
HashTable<T>::HashTable()
{
	__log.open("log.txt", std::ios::out);	// DEBUG

	__keys = new List<std::string>();
	__resizeCount = 0;
	__capacity = 3;
	__table = new HashTableNode<T>*[__capacity];
	__occupancy = 0;
	for (size_t i = 0; i < __capacity; i++)
		__table[i] = nullptr;
}

template<typename T>
HashTable<T>::HashTable(size_t quantityToAdd)
{
	__keys = new List<std::string>();
	__log.open("log.txt", std::ios::out);	// DEBUG
	__resizeCount = 0;

	if (MathUtil::isPrimeMillerRabin(quantityToAdd, 4))
		__capacity = quantityToAdd;
	else
		__capacity = __findNextPrime(quantityToAdd);

	__table = new HashTableNode<T>*[__capacity];
	__occupancy = 0;
	for (size_t i = 0; i < __capacity; i++)
		__table[i] = nullptr;
}
template<typename T>
HashTable<T>::~HashTable() {

	// DEBUG
	__log << "Rehashes: " << __resizeCount << std::endl;
	__log << "Collisions: " << __collisionCount << std::endl;
	__log << "Load Factor: " << this->loadFactor() << std::endl;
	__log << "Occupancy: " << __occupancy << std::endl;
	__log << "Capacity: " << __capacity << std::endl;
	__log.close();
	// end DEBUG
	__keys->clear();
	this->__clear();
}
// ------------------------------------------
// Internal	Table Management Section
// ------------------------------------------
template<typename T>
void HashTable<T>::__resize()
{
	if (__hitLimit)
		return;

	if (__capacity * 2 > MathUtil::MAX_PRIME)
	{
		__hitLimit = true;
		return;
	}
	// reset unordered key list t
	__keys->clear();
	__resizeCount++;
	// hold onto old table and old size
	HashTableNode<T>**	pOldTable = __table;
	size_t oldCapacity = __capacity;
	// double old capacity to a new prime
	__capacity = __findNextPrime(__capacity * 2);
	// recreate the table with the new capacity and reset to all nullptr
	__table = new HashTableNode<T>*[__capacity];
	for (size_t i = 0; i < __capacity; i++)
		__table[i] = nullptr;
	// reset occupancy and collision counter
	__occupancy = 0;
	__collisionCount = 0;
	// add via rehashing the old entry keys and values to the expanded table
	for (size_t i = 0; i < oldCapacity; i++)
		if (pOldTable[i] != nullptr)
			this->add(pOldTable[i]->getKey(), pOldTable[i]->getValue());
	// deallocate memory of old table
	for (size_t i = 0; i < oldCapacity; i++)
	{
		if (pOldTable[i] != nullptr)
			delete pOldTable[i];
	}
	delete[] pOldTable;
	pOldTable = nullptr;
}

template<typename T>
void HashTable<T>::__clear()
{
	for (size_t i = 0; i < __capacity; i++)
		delete __table[i];
	delete[] __table;
}

template<typename T>
int HashTable<T>::__find(std::string key) const
{
	bool collide = false;
	size_t hashID;
	int pos = -1;

	// init hashID
	hashID = HashUtil::hashBirthday(key);
	//std::cout << __table[hashID]->getKey() << std::endl;	// DEBUG
	for (size_t i = 0; i < __capacity; i++)
	{
		// quadratically generate the hashID
		//hashID = (hashID + __C1 * i + __C2 * i * i) % __capacity;
		//hashID = (hashID + i * i) % __capacity;
		hashID = (hashID + i + i * i) % __capacity;

		if (__table[hashID] != nullptr && __table[hashID]->getKey() == key)
		{
			return hashID;
		}
	}
	return pos;
}
template<typename T>
size_t HashTable<T>::__findNextPrime(size_t quantityToAdd)
{
	std::ifstream infile;
	if (quantityToAdd < MathUtil::MAX_PRIME)
	{
		return MathUtil::findPrime(quantityToAdd);
	}
	else
	{
		throw CustomException("Quantity Out of Bounds of Stored Prime Numbers");
		//// generate a sorted array of primes with a slightly larger bound than needed 
		//size_t* pPrimes;
		//unsigned long newTableSize = 0;
		//// generate primes with a slightly 
		//pPrimes = MathUtil::generatePrimesAtkins(quantityToAdd*1.5);
		//// start at  point and look for the next prime greater than the input arg 
		////std::cout << pPrimes[MathUtil::ATKINS_ARRAY_SIZE / 2] << std::endl;	// DEBUG
		//for (size_t i = (MathUtil::ATKINS_ARRAY_SIZE / 2); i < MathUtil::ATKINS_ARRAY_SIZE; i++)
		//{
		//	//std::cout << i << std::endl;	// DEBUG
		//	if (pPrimes[i] > quantityToAdd)
		//	{
		//		newTableSize = pPrimes[i];
		//		std::cout << newTableSize << std::endl;
		//		break;
		//	}
		//}
		//delete[] pPrimes;
		//std::cout << newTableSize << std::endl;
		//return newTableSize;
	}
}
// -------------------------------------
// Mutator Section
// -------------------------------------

template<typename T>
bool HashTable<T>::add(std::string key, const T& value)
{
	bool collide = false;
	size_t hashID;

	// check current state of table before adding
	if ((double)__occupancy / (double)__capacity > .5)
		this->__resize();

	// quadratically generate the hashID 
	hashID = HashUtil::hashBirthday(key);	
	for (size_t i = 0; i < __capacity; i++)
	{
		//hashID = (hashID + __C1 * i + __C2 * i * i) % __capacity;	 
		hashID = (hashID + i + i * i) % __capacity;
		if (__table[hashID] == nullptr)
		{
			// collision case
			if (i > 0)
			{
				__collisionCount++;
				// map table node to generated hashID and add to unsorted list
				__table[hashID] = new HashTableNode<T>(key, hashID, value, true);
				//__pairs->append(__table[hashID]);
				__keys->append(key);
				__occupancy++;
				//__keys.insert(__keys.getLength(), key);
				//__values.insert(__values.getLength(), value);
				__log << value << "\t\t\t" << i << " hashes" << std::endl;
				return true;
			}
			// no collision case
			else {
				// map table node to generated hashID and add to unsorted list
				__table[hashID] = new HashTableNode<T>(key, hashID, value, false);
				__keys->append(key);
				__occupancy++;
				__log << value << "\t\t\t" << i << " hashes" << std::endl;

				return true;
			}
		}
	}
	return false;
}

template<typename T>
bool HashTable<T>::remove(std::string key)
{
	int hashID = this->__find(key);
	if (hashID == -1)
		return false;
	if (__table[hashID]!= nullptr)
	{
		if (__table[hashID]->hasCollision())
			__collisionCount--;
		for (int i = 0; i < __keys->getLength(); i++)
		{
			if (__keys->getEntry(i) == key)
			{
				__keys->remove(i);
			}
		}
		delete __table[hashID];
		return true;
	}
	return false;
}
// -------------------------------------
// Getter Section
// -------------------------------------

template<typename T>
void HashTable<T>::empty()
{
	if (__occupancy == 0)
		return;
	this->__clear();
}
template<typename T>
double HashTable<T>::loadFactor() const
{
	return	((double)__occupancy / (double)__capacity);

}
template<typename T>
size_t HashTable<T>::capacity() const
{
	return __capacity;
}
template<typename T>
size_t HashTable<T>::size() const
{
	return __occupancy;
}

template<typename T>
size_t HashTable<T>::collisions() const
{
	return __collisionCount;
}
template<typename T>

size_t HashTable<T>::resizeQuantity() const
{
	return size_t();
}
template<typename T>
void HashTable<T>::display()
{
	std::cout << "Index\t|\tValue\t\t\t|\tCollision\n";
	std::cout << "------------------------------------------------------------------\n";
	// iterate using internally stored keys
	for (int i = 0; i < __keys->getLength(); i++)
	{
		std::cout << "Key: " << __keys->getEntry(i) << " | Value: " << __table[__find(__keys->getEntry(i))]->getValue() << std::endl;
	}
	std::cout << "Occupancy: " << __occupancy << std::endl;
	std::cout << "Capacity: " << __capacity << std::endl;
	std::cout << "Load Factor: " << std::to_string(loadFactor() * 100) << "%" << std::endl;
	std::cout << "Number of Collisions: " << __collisionCount << std::endl;
}
template<typename T>
List<std::string> HashTable<T>::keys() const
{
	return *(__keys);
}
template<typename T>
bool HashTable<T>::isEmpty() const
{
	return (__occupancy == 0 ? true : false);
}
template<typename T>
T HashTable<T>::get(std::string key) const
{
	int hashID = __find(key);
	if (hashID == -1)
		throw CustomException("Key Error: " + key);
	else
		return __table[hashID]->getValue();
}
// -------------------------------------
// Operator Overload Section
// -------------------------------------
template<typename T>
std::ostream & operator<<(std::ostream & out, HashTable<T>& table)
{
	// TODO: insert return statement here
	if (table.__occupancy == 0)
	{
		out << "{ }";
		return out;
	}
	const int SIZE = table.__keys->getLength();
	out << "{ ";
	for (int i = 0; i < SIZE - 1; i++)
	{
		out << "'"  << table.__keys->getEntry(i) << "': " << table.__table[table.__find(table.__keys->getEntry(i))]->getValue() << ", ";
	}
	out  << table.__keys->getEntry(SIZE - 1) << "': " << table.__table[table.__find(table.__keys->getEntry(SIZE - 1))]->getValue() << "}";
	return out;
}
template<typename T>
T HashTable<T>::operator[](std::string key) const
{
	int hashID = __find(key);
	if (hashID == -1)
		throw CustomException("Key Error: " + key);
	else
		return __table[hashID]->getValue();
}
template<typename T>
T& HashTable<T>::operator[](std::string key)
{
	int hashID = __find(key);
	if (hashID == -1)
		throw CustomException("Key Error: " + key);
	else
		return __table[hashID]->getValue();
}
#endif // ! _HASH_TABLE_H

