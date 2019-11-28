#ifndef _UTIL_FILEIO_H
#define _UTIL_FILEIO_H
#include "List.h"
#include "person.h"
#include <fstream>
#include "StringUtil.h"

namespace FileUtil
{
	/* Build a list of */
	List<Person>* buildListFromFile(std::string);
	List<std::string>* buildNameListFromFile(std::string path);
	List<std::string>* buildDateListFromFile(std::string path);
}
#endif // !_UTIL_FILEIO_H
