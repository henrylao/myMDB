#ifndef _STR_UTIL_H
#define _STR_UTIL_H
#include "List.h"
#include <string>
#include <locale>

namespace StringUtil
{
	std::string strip(const std::string& str);
	std::string uppercase(const std::string&);
	List<std::string>* split(const std::string& str, const std::string delim);
	//std::string join(const List<std::string>& target, std::string delim);
	std::string lowercase(const std::string& str);
	std::string lstrip(const std::string& str);
	std::string rstrip(const std::string& str);
	std::string replace(const std::string& data, const std::string& to_search, const std::string& replace_str);
};
#endif // ! _STRING_UTIL

