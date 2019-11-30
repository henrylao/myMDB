#ifndef _MOVIE_H
#define _MOVIE_H

#include <iostream>
#include "List.h"

class Movie {
private:
	std::string m_title;
	int m_yearRelease;
	double m_ratings;
	List<std::string>* m_genre;	//List of strings for multiple genres
	List<std::string>* m_cast;	//List of strings for multiple casts
public:
	//----------------------------------//
	//	 Constructors and Destructors	//
	//----------------------------------//
	Movie();
	Movie(std::string in_title, int in_year, double in_ratings,
		List<std::string>* in_genre, List<std::string>* in_cast);
	//Copy constructor
	Movie(Movie& m);
	~Movie() {};

	//----------------------------------//
	//			   Mutators				//
	//----------------------------------//
	void setTitle(std::string in_title);
	void setYear(int in_year);
	void setRatings(double in_ratings);
	void setGenre(List<std::string>* in_genre);
	void setCast(List<std::string>* in_cast);

	//----------------------------------//
	//			   Getters				//
	//----------------------------------//
	std::string getTitle() const;
	int getYear() const;
	double getRatings() const;
	List<std::string>* getGenre() const;
	List<std::string>* getCast() const;
	int getNumberofGenre() const;
	int getNumberofCast() const;
	// Check if in_name is in the m_cast
	bool checkCast(std::string in_name) const;
	// Check if in_genre is in the m_genre
	bool checkGenre(std::string in_genre) const;

	//----------------------------------//
	//		  Operator Overload			//
	//----------------------------------//
	friend std::ostream& operator<< (std::ostream &out, const Movie& movie);
};

Movie::Movie() : m_title(""), m_yearRelease(-1), m_ratings(-1),
m_genre(nullptr), m_cast(nullptr) {};

Movie::Movie(std::string in_title, int in_year, double in_ratings,
	List<std::string>* in_genre, List<std::string>* in_cast) : m_title(in_title),
	m_yearRelease(in_year), m_ratings(in_ratings), m_genre(in_genre), m_cast(in_cast) {}


Movie::Movie(Movie& m) :
	m_title(m.getTitle()), m_yearRelease(m.getYear()), m_ratings(m.getRatings()),
	m_genre(m.getGenre()), m_cast(m.getCast()) {};

void Movie::setTitle(std::string in_title) { this->m_title = in_title; }

void Movie::setYear(int in_year) { this->m_yearRelease = in_year; }

void Movie::setRatings(double in_ratings) { this->m_ratings = in_ratings; }

void Movie::setGenre(List<std::string>* in_genre) { this->m_genre = in_genre; }

void Movie::setCast(List<std::string>* in_cast) { this->m_cast = in_cast; }

std::string Movie::getTitle() const { return this->m_title; }

int Movie::getYear() const { return this->m_yearRelease; }

double Movie::getRatings() const { return this->m_ratings; }

List<std::string>* Movie::getGenre() const { return this->m_genre; }

List<std::string>* Movie::getCast() const { return this->m_cast; }

int Movie::getNumberofGenre() const {
	if (!m_genre->isEmpty()) {
		return m_genre->size();
	}
	else {
		return 0;
	}
}

int Movie::getNumberofCast() const {
	if (!m_cast->isEmpty()) {
		return m_cast->size();
	}
	else {
		return 0;
	}
}

bool Movie::checkGenre(std::string in_name) const {
	if (!m_genre->isEmpty()) {
		return m_genre->contains(in_name);
	}
	else {
		return false;
	}
}

bool Movie::checkCast(std::string in_genre) const {
	if (!m_cast->isEmpty()) {
		return m_cast->contains(in_genre);
	}
	else {
		return false;
	}
}

std::ostream& operator<< (std::ostream &out, const Movie& movie)
{
	out << movie.m_title;
	out << "(" << movie.m_yearRelease << ")";
	out << "\t ¡¹" << movie.m_ratings << "/10" << std::endl;
	out << "Genres:" << &(movie.m_genre) << std::endl;
	out << "Casts:" << &(movie.m_cast) << std::endl;
	return out;
}
#endif