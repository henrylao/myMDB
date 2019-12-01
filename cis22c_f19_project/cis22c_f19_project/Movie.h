//#ifndef  _MOVIE_H
//#define _MOVIE_H
//#include <string>
//#include "Actor.h"
//#include "Person.h"
//#include "List.h"
//
//class Movie {
//private:
//	List<std::string>*		__actorIDs; 
//	int						__year;
//	double					__rating;
//	std::string				__genre;
//	std::string				__title;
//	std::string				__movieID;
//	/*toggle between various comparisons:
//	1 by movieID
//	2 by rating
//	3 by year */
//	int						__compareConfig;
//
//public:
//	Movie();
//	Movie(std::string title, std::string genre, int year, double rating);
//	//Movie(std::string title, std::string genre, int year, double rating, List<Actor*>* actors);
//	~Movie();
//	void clear();
//
//	bool addActor(const Actor& actor);
//	bool addActor(const std::string& actorID);
//
//	bool removeActor(const Actor& actor);
//	bool removeActor(std::string);
//
//	void readFullInfo() const;
//	void readActor(std::string name) const;
//	void setComparisonConfig(int config);
//	std::string getGenre() const;
//	std::string getTitle() const;
//	std::string getID() const;
//	//const List<Actor*>* getActors() const;
//	
//	double getRating() const;
//
//	friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
//	bool operator==(const Movie& movie) const;
//	bool operator<(const Movie& movie) const;
//	bool operator>(const Movie& movie) const;
//};
//#endif // ! _MOVIE_H
