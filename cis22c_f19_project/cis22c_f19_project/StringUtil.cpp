#include "StringUtil.h"

std::string StringUtil::strip(const std::string& str) {
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

std::string StringUtil::uppercase(const std::string& str) {
	std::string formatted = "";
	std::locale loc;
	for (std::string::size_type i = 0; i < str.length(); ++i)
	{
		formatted += std::toupper(str[i], loc);
	}
	return formatted;
}

List<std::string>* StringUtil::split(const std::string & str, const std::string delim)
{
	if (str.empty())
		return nullptr;
	List<std::string>* tokens = new List<std::string>();
	std::string::size_type start = 0;
	while (true)
	{
		size_t idx = str.find(delim, start);
		if (idx == std::string::npos)
			break;
		tokens->append(str.substr(start, idx - start));
		start = idx + delim.size();
	}
	tokens->append(str.substr(start));

	return tokens;
}

std::string StringUtil::join(const List<std::string>& tokens)
{
	std::string joined;
	for (int i = 0; i < tokens.getLength(); i++)
	{
		joined += tokens.getEntry(i);
	}
	return joined;
}

std::string StringUtil::lowercase(const std::string& str) {
	std::string formatted = "";
	std::locale loc;
	for (std::string::size_type i = 0; i < str.length(); ++i)
	{
		formatted += std::tolower(str[i], loc);
	}
	return formatted;
}

std::string StringUtil::replace(const std::string& data,
	const std::string& to_search,
	const std::string& replace_str)
{
	std::string formatted = data;

	size_t pos = formatted.find(to_search);
	while (pos != std::string::npos)
	{
		formatted.replace(pos, to_search.size(), replace_str);
		pos = formatted.find(to_search, pos + replace_str.size());
	}
	return formatted;
}

bool StringUtil::containsAlpha(const std::string & data)
{
	for (int i = 0; i < data.length(); i++)
	{
		if (isalpha(data[i]))
			return true;
	}
	return false;
}



