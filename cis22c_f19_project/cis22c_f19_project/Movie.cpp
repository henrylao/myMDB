#include <iostream>
#include "Movie.h"


//----------------------------------//
//	 Constructors and Destructors	//
//----------------------------------//
Movie::Movie() : m_title(""),m_yearRelease(-1), m_ratings(-1),
	m_genre(nullptr), m_cast(nullptr) {};

Movie::Movie(std::string in_title, int in_year, double in_ratings,
	List<std::string>* in_genre, List<std::string>* in_cast) : m_title(in_title),
	m_yearRelease(in_year), m_ratings(in_ratings),
	m_genre(in_genre), m_cast(in_cast) {};

Movie::Movie(const Movie& m) :
	m_title(m.getTitle()), m_yearRelease(m.getYear()), m_ratings(m.getRatings),
	m_genre(m.getGenre), m_cast(m.getCast) {};

//----------------------------------//
//			   Mutators				//
//----------------------------------//
void Movie::setTitle(std::string in_title) { this->m_title = in_title; }

void Movie::setYear(int in_year) { this->m_yearRelease = in_year; }

void Movie::setRatings(double in_ratings) { this->m_ratings = in_ratings; }

void Movie::setGenre(List<std::string>* in_genre) { this->m_genre = in_genre; }

void Movie::setCast(List<std::string>* in_cast) { this->m_cast = in_cast; }

//----------------------------------//
//			   Getters				//
//----------------------------------//
std::string Movie::getTitle() const { return this->m_title; }

int Movie::getYear() const { return this->m_yearRelease; }

double Movie::getRatings() const { return this->m_ratings; }

List<std::string>* Movie::getGenre() const { return this->m_genre; }

List<std::string>* Movie::getCast() const { return this->m_cast; }

int Movie::getNumberofGenre() const {
	if (!m_genre->isEmpty()) {
		return m_genre->getLength();
	}
	else {
		return 0;
	}
}

int Movie::getNumberofCast() const {
	if (!m_cast->isEmpty()) {
		return m_cast->getLength();
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