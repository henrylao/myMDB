#include <iostream>
#include "GUI.h"
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"
#include <chrono>
#include "NotIMDB_Database.h"
using namespace std;

int main() {
	string path = "data//full//movie_titles_sorted_by_id_full.tsv";
	List<std::string>* movieTitles = new List<std::string>();
	// benchmarking 
	auto start = std::chrono::high_resolution_clock::now();
	FileIO::buildMovieTitles_sortedByID(path, movieTitles);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	int SIZE = movieTitles->getLength();
	/*for (int i = 0; i < SIZE; i++)
	{
		cout << movieTitles->getEntry(i) << endl;
	}*/
	NotIMDB_Database var;
	int index;

	start = std::chrono::high_resolution_clock::now();
	index = var.__binarySearch_byMovieName(movieTitles, 0, SIZE, "tt0001116");
	finish = std::chrono::high_resolution_clock::now();

	elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	cout << index << endl;
	cout << SIZE << endl;
	return 0;

}