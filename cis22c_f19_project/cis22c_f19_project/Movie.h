
#ifndef  _MOVIE_H
#define _MOVIE_H

#include <string>
#include "List.h"


class Movie {
private:
	std::string				__yearReleased;	// startYear in data set
	std::string				__rating;
	List<std::string>*		__genres;
	std::string				__title;
	std::string				__movieID;
	std::string				__runtimeMinutes;
	/*toggle between various comparisons:
	1 by movieID
	2 by rating
	3 by year 
	4 by title 
	5 by runtime */
	int						__compareConfig;

public:
	//----------------------------------------------------
	// Constructor and Destructor Section
	//----------------------------------------------------
	// default comparison is by movie id
	Movie();
	Movie(std::string tconstID, std::string title, 
		std::string year, std::string runTime, 
		const List<std::string>& genres);
	//----------------------------------------------------
	// Mutators Section
	//----------------------------------------------------
	void		clear();
	void		setCompareByID() { __compareConfig = 1; }
	void		setCompareByRating() { __compareConfig = 2; }
	void		setCompareByYear() { __compareConfig = 3; }
	void		setCompareByTitle() { __compareConfig = 4; }
	void		setCompareByRuntime() { __compareConfig = 5; }

	//----------------------------------------------------
	// Getters Section
	//----------------------------------------------------
	void						readFullInfo() const { std::cout << *this << std::endl; }
	List<std::string>			getGenres() const { return *__genres; }
	std::string					getTitle() const { return __title;  }
	std::string					getID() const { return __movieID; }
	std::string					getRating() const { return __rating; }

	//--------------------------------
	// Operator Overload Section
	//------------------------------
	friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
	bool operator==(const Movie& movie) const;
	bool operator<(const Movie& movie) const;
	bool operator<=(const Movie& movie) const;
	bool operator>(const Movie& movie) const;
	bool operator>=(const Movie& movie) const;
};
#endif // ! _MOVIE_H
