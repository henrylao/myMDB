#include "HashUtil.h"

size_t HashUtil::hashBirthday(const std::string& str) {
	// clean string to include only integers
	std::string cleaned = StringUtil::replace(str, "-", "");
	int SIZE = cleaned.size();
	int sum = 0;
	// find sum of all integers in the cleaned string
	for (int i = 0; i < SIZE; i++)
	{
		sum += std::stoi(std::string(1, cleaned[i]));
	}
	// convert sum to string and calculate second sum
	std::string sumStr = std::to_string(sum);
	SIZE = sumStr.size();
	sum = 0;
	for (int i = 0; i < SIZE; i++)
		sum += std::stoi(std::string(1, sumStr[i]));
	return sum;
}
//
//size_t HashUtil::hashStringFold(const std::string & str, size_t byteSize)
//{
//	size_t intLength = str.length() / 4;
//	size_t sum = 0;
//	for (size_t j = 0; j < intLength; j++) {
//		std::string c = str.substr(j * 4, (j * 4) + 4).c_str();
//		size_t mult = 1;
//		for (int k = 0; k < c.length; k++) {
//			sum += size_t(c[k]) * mult;
//			mult *= 256;
//		}
//	}
//	std::string c = str.substr(intLength * 4).c_str();
//	size_t mult = 1;
//	for (int k = 0; k < c.length; k++) {
//		sum += c[k] * mult;
//		mult *= 256;
//	}
//	return(sum % byteSize);
//}

size_t HashUtil::hash_UNIX_ELF(std::string name)
{
	// UNIX ELF hash
	// Published hash algorithm used in the UNIX ELF format for object files
	unsigned long h = 0, g;
	size_t value;
	std::string::iterator   sp;

	for (sp = name.begin(); sp != name.end(); sp++) {
		h = (h << 4) + *sp;
		if (g = h & 0xF0000000) {
			h ^= g >> 24;
			h &= ~g;
		}
	}
	value = h;
	return value;
}

unsigned int HashUtil::RSHash(const std::string& str)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash = hash * a + str[i];
		a = a * b;
	}

	return (hash & 0x7FFFFFFF);
}

unsigned int HashUtil::JSHash(const std::string& str)
{
	unsigned int hash = 1315423911;

	for (std::size_t i = 0; i < str.length(); i++)
	{
		hash ^= ((hash << 5) + str[i] + (hash >> 2));
	}

	return (hash & 0x7FFFFFFF);
}

unsigned int HashUtil::SDBMHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}
unsigned int HashUtil::DJBHash(const char* str, unsigned int length)
{
	unsigned int hash = 5381;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) + hash) + (*str);
	}

	return hash;
}
unsigned int HashUtil::DEKHash(const char* str, unsigned int length)
{
	unsigned int hash = length;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
	}

	return hash;
}