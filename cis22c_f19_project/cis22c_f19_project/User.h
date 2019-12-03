#ifndef  _USER_H
#define	 _USER_H

#include "List.h"
#include <string>
#include "StringUtil.h"
#include <fstream>
class User
{
	List<std::string>			__searchHistory;
	std::string					__name;
public:
	User();
	bool loadUserHistory(std::string path);
	void writeUserHistory(std::string path);



}
#endif // ! _USER_H
