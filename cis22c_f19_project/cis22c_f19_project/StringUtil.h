#ifndef _STR_UTIL_H
#define _STR_UTIL_H
#include "List.h"
#include <string>
#include <locale>
namespace StringUtil
{
	std::string				strip(const std::string& str);
	std::string				uppercase(const std::string&);
	List<std::string>*		split(const std::string& str, const std::string delim);
	std::string				join(const List<std::string>& tokens);
	std::string				lowercase(const std::string& str);
	std::string				lstrip(const std::string& str);
	std::string				rstrip(const std::string& str);
	bool					contains(std::string mainStr, std::string substrToVerify);
	/* Replace all the substrings found (to_search) in the data str
	returning a modified string without mutating original input string
	@param data is the string format
	@param to_search is the substring to find in the data string and replace
	@param replace_str is the string to replace the found(to_search) substrings 
	in the data string
	@pre none
	@post none
	@return a string is formatted and reflects the changes from the input args */
	std::string				replace(const std::string& data, const std::string& to_search, const std::string& replace_str);
	/* Returns true if the string contains any characters of the alphabet 
	@param data is the string to search
	@pre none
	@post none
	@return true if the string contains a character of the alphabet else false */
	bool					containsAlpha(const std::string& data);
};
#endif // ! _STRING_UTIL

