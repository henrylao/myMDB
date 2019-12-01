
#ifndef  _MOVIE_H
#define _MOVIE_H

#include <string>
#include "Actor.h"
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
	static const char				MOVIE_DELIM = '|';
	// default comparison is by movie id
	Movie();
	Movie(std::string tconstID, std::string title, 
		std::string year, std::string runTime, const List<std::string>& genres);

	void clear();
	void readFullInfo() const;
	void setCompareByID() { __compareConfig = 1; }
	void setCompareByRating() { __compareConfig = 2; }
	void setCompareByYear() { __compareConfig = 3;  }
	void setCompareByTitle() { __compareConfig = 4; }
	void setCompareByRuntime() { __compareConfig = 5;  }

	List<std::string> getGenres() const { return *__genres; }
	std::string getTitle() const;
	std::string getID() const;
	//const List<Actor*>* getActors() const;
	
	double getRating() const;

	friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
	bool operator==(const Movie& movie) const;
	bool operator<(const Movie& movie) const;
	bool operator<=(const Movie& movie) const;
	bool operator>(const Movie& movie) const;
	bool operator>=(const Movie& movie) const;
};
#endif // ! _MOVIE_H
