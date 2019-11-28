#ifndef _CUSTOM_EXCEPTION_H
#define _CUSTOM_EXCEPTION_H
#include <string>

class CustomException
{
	std::string m_msg;
public:
	CustomException(const std::string& t_msg) : m_msg(t_msg) {}
	CustomException() : m_msg("") {}
	std::string getMessage() const { return this->m_msg; }
};


#endif // !1
