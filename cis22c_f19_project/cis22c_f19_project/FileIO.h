#ifndef _UTIL_FILEIO_H
#define _UTIL_FILEIO_H
#include "List.h"
#include "person.h"
#include <fstream>
#include "StringUtil.h"
#include "HashTable.h"

namespace FileIO
{
	/* Builds a list of people from a .txt file. White spaces are 
	accounted for an do not affect list creation. Order
	of names and dates must follow the following format:
	person1_name
	YYYY-MM-DD
	person2_name
	YYYY-MM-DD
	person3_name
	YYYY-MM-DD
	@return pointer to a list of people constructed */
	List<Person>* buildPersonListFromFile(std::string);
	/* Builds a list of people from a .txt file of names. 
	@return pointer to a list of names 
	@param path is the full path to the target file */
	List<std::string>* buildNameListFromFile(std::string path);
	/* Builds a list of dates from a .txt file of dates of
	the following format:
	YYYY-MM-DD
	@return pointer to a list of names
	@param path is the full path to the target file */
	List<std::string>* buildDateListFromFile(std::string path);
	void writeTableToFile(std::string path,
		const List<std::string>& keys,   HashTable<Person>& table);
	
}
#endif // !_UTIL_FILEIO_H
