#include <iostream>
#include "Movie.h"
#include "List.h"

using namespace std;

int main() {
	string str1 = "ThanksGiving";
	List<string> g1;
	g1.append("Horror");
	g1.append("Comedey");
	List<string> c1;
	g1.append("Jon Doe");
	g1.append("Herry Styles");
	cout << c1;
	Movie m(str1, 2019, 8.0, &g1, &c1);
	//cout << m.getGenre() << endl;
	//cout << m << endl;
	return 0;
}