#ifndef _ACTOR_H
#define _ACTOR_H

#include "List.h"
#include "Movie.h"

class Actor
{

private:
	std::string				__actorID;
	//  list of associated movieIDs ie keys however can also be the hashed ids as well
	// using the raw keys would require hashing to find from a table of movies
	List<std::string>*		__movieIDs;	
	List<std::string>*		__roles;
	std::string				__name;
	std::string				__deathYear;
	std::string				__birthYear;

public:
	Actor() {}
	Actor(std::string name, std::string birthDate, List<std::string>* movieIDs, List<std::string>* roles);
	~Actor();
	void clear();
	// add movie 
	bool addMovie(const Movie& movie);
	bool removeMovie(const Movie& movie);
	std::string getID() const;
	
	bool findMovie(std::string movieName) const;
	bool findMovie(const Movie& movie) const;

	void readFullInfo() const;

	bool operator==(const Actor& actor) const;
	bool operator<(const Actor& actor) const;
	bool operator>(const Actor& actor) const;
};
#endif // !_ACTOR_H


#include "Movie.h"