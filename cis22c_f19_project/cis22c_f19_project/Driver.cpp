#include <iostream>
//#include "Movie.h"
#include "FileIO.h"
#include "MathUtil.h"

using namespace std;

int main()
{
	List<int> list;
	for (int i = 0; i < 7; i++)
		list.append(i);
	cout << list[0] << endl;
	return 0;
}