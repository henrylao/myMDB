#ifndef _ACTOR_H
#define _ACTOR_H
#include "List.h"
#include <string>
#include "Movie.h"

class Actor
{
private:
	std::string				__actorID;	// nconst
	//  list of associated movieids ie keys however can also be the hashed ids as well
	// using the raw keys would require hashing to find from a table of movies
	std::string				__name;
	std::string				__birthYear;
	std::string				__deathYear;
	std::string				__roles;
	List<std::string>*		__movieIDs;
	List<Movie*>*			__movies;	// populate after adding to hashtable?
	/*toggle between various comparisons:
	1 by actorID (DEFAULT CTOR VALUE) 
	2 by name
	3 by birthYear */
	int						__compareConfig;

public:
	Actor();
	Actor(std::string tconstID, std::string name, std::string birthyear, std::string deathYear,
		std::string roles, const List<std::string>& movieIDs);
	~Actor() { clear;  }
	void clear() { 
		delete __movieIDs;  
		int SIZE = __movies->getLength();
		for (int i = 0; i < SIZE; i++)
		{
			// set the pointers in an actor to null 
			// movie deletion is handled when the database is closed
			// actors & movie relation is uni-directional 
			__movies->setEntry(i, nullptr);	
		}
		delete __movies;	// destroy list structure
	}
	// add movie 
	//bool addMovie(const Movie& movie);
	//bool removeMovie(const Movie& movie);
	std::string getID() const;
	std::string getName() const { return __name; }
		
	
	void readFullInfo() const;
	friend std::ostream& operator<<(std::ostream& out, const Actor& actor);
	bool operator==(const Actor& actor) const;
	bool operator<(const Actor& actor) const;
	bool operator>(const Actor& actor) const;
	bool operator<=(const Actor& actor) const;
	bool operator>=(const Actor& actor) const;
};

#endif

