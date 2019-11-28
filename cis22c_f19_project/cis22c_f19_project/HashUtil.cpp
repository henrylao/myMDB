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