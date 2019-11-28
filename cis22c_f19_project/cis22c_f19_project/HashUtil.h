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
	//uint64_t 
};

#endif // ! _HASH_UTIL_H

