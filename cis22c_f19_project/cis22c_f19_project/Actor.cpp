#include "Actor.h"

Actor::Actor()
{
	__name = "";
	__actorID = "";
	__birthYear = "";
	__deathYear = "";
	__roles = "";
	__movieIDs = new List<std::string>();
	__movies = new List<Movie*>();
}

Actor::Actor(std::string tconstID, std::string name, std::string birthYear, std::string deathYear,
	std::string roles, const List<std::string>& movieIDs)
{
	__name = name;
	__actorID = tconstID;
	__birthYear = birthYear;
	__deathYear = deathYear;
	__roles = roles;
	__movieIDs = new List<std::string>(movieIDs);
	__movies = new List<Movie*>();
}


std::string Actor::getID() const
{
	return std::string();
}

void Actor::readFullInfo() const
{
}

bool Actor::operator==(const Actor & rhs) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__actorID == rhs.__actorID ? true : false);
		break;
	case 2:
		return (__name == rhs.__name ? true : false);
		break;

	case 3:
		return (__birthYear == rhs.__birthYear ? true : false);
		break;
	}

	return false;
}

bool Actor::operator<(const Actor & rhs) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__actorID < rhs.__actorID ? true : false);
		break;
	case 2:
		return (__name < rhs.__name ? true : false);
		break;

	case 3:
		return (__birthYear < rhs.__birthYear ? true : false);
		break;
	}
	return false;
}

bool Actor::operator>(const Actor & rhs) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__actorID > rhs.__actorID ? true : false);
		break;
	case 2:
		return (__name > rhs.__name ? true : false);
		break;
	case 3:
		return (__birthYear > rhs.__birthYear ? true : false);
		break;
	}
	return false;
}

bool Actor::operator<=(const Actor & rhs) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__actorID <= rhs.__actorID ? true : false);
		break;
	case 2:
		return (__name <= rhs.__name ? true : false);
		break;

	case 3:
		return (__birthYear <= rhs.__birthYear ? true : false);
		break;
	}
	return false;
}

bool Actor::operator>=(const Actor & rhs) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__actorID >= rhs.__actorID ? true : false);
		break;
	case 2:
		return (__name >= rhs.__name ? true : false);
		break;

	case 3:
		return (__birthYear >= rhs.__birthYear ? true : false);
		break;
	}
	return false;
}

std::ostream & operator<<(std::ostream & out, const Actor & actor)
{
	out << "Name: " << actor.__name << std::endl;
	out << "Actor ID: " << actor.__actorID << std::endl;
	out << "Birth Year: " << actor.__birthYear << std::endl;
	out << "Death Year: " << actor.__deathYear << std::endl;
	out << "Associated Roles: " << actor.__roles << std::endl;
	out << "Associated Movies: ";
	int SIZE = actor.__movies->getLength();  
	for (int i = 0; i < SIZE; i++)
	{
		out << "\t* " << actor.__movies->getEntry(i)->getTitle() << std::endl;
	}
	return out;
}
