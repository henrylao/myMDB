#ifndef SORT_UTIL_H
#define SORT_UTIL_H
#include "Movie.h"
#include "pair.h"

namespace SortUtil
{
	/* This function takes last element as pivot, places
	the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
	to left of pivot and all greater elements to right
	of pivot */
	int partition(Pair<Movie*,int>** arr , int low, int high);
	/* This function sorts the pair values in descending order
	in accordance to the configuration of the pair comparison 
	operators 
	arr** --> Array to be sorted,
	low --> Starting index,
	high --> Ending index == size of the array - 1 */
	void quickSort(Pair<Movie*, int>** arr, int low, int high);
	// A utility function to swap two elements
	void swap(Pair<Movie*, int>* a, Pair<Movie*, int>* b);
}

#endif // ! SORT_UTIL_H
