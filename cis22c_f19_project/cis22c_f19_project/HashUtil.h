#ifndef  _HASH_UTIL_H
#define _HASH_UTIL_H

#include <string>
#include "StringUtil.h"

namespace HashUtil
{
	/* Hash a date by summing up the individual integer
	values in a date string
	@pre input string parameter is assumed to follow the format: YYYY-MM-DD
	@post string is hashed to a value less than or equal to 9 
	@return computed size_t hash value */
	size_t hashBirthday(const std::string& str);
	size_t hashStringFold(const std::string & str, size_t byteSize);
	size_t hash_UNIX_ELF(std::string name);
	size_t hashStringFold(const std::string & str, int byteSize);
	//uint64_t 
	unsigned int RSHash(const std::string & str);

	unsigned int JSHash(const std::string & str);

	unsigned int SDBMHash(const char * str, unsigned int length);

	unsigned int DJBHash(const char * str, unsigned int length);

	unsigned int DEKHash(const char * str, unsigned int length);
	
};

#endif // ! _HASH_UTIL_H
