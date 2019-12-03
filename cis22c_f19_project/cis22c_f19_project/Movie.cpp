#include "Movie.h"

Movie::Movie()
{
	__yearReleased = "";
	__rating = -1;
	__genres = "";
	__title = "";
	__movieID = "";
	__compareConfig = 1;
}

Movie::Movie(std::string tconstID, std::string title, std::string year, std::string runTime, std::string genres)
{
	__movieID = tconstID;
	__title = title;
	__genres = genres;
	__yearReleased = year;
	__runtimeMinutes = runTime;
	__rating = -1;
	__compareConfig = 1;

}

void Movie::clear()
{
}

bool Movie::operator==(const Movie & rightHandSide) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__movieID == rightHandSide.__movieID ? true : false);
		break;
	case 2:
		return (__rating == rightHandSide.__rating ? true : false);
		break;

	case 3:
		return (__yearReleased == rightHandSide.__yearReleased ? true : false);
		break;

	case 4:
		return (__title == rightHandSide.__title ? true : false);
		break;
	case 5: 
		return (__runtimeMinutes == rightHandSide.__runtimeMinutes ? true : false);
	}
		
	return false;
}

bool Movie::operator<(const Movie & rightHandSide) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__movieID == rightHandSide.__movieID ? true : false);
		break;
	case 2:
		return (__rating == rightHandSide.__rating ? true : false);
		break;

	case 3:
		return (__yearReleased == rightHandSide.__yearReleased ? true : false);
		break;

	case 4:
		return (__title == rightHandSide.__title ? true : false);
		break;
	case 5:
		return (__runtimeMinutes == rightHandSide.__runtimeMinutes ? true : false);
	}

	return false;
}

bool Movie::operator<=(const Movie & rightHandSide) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__movieID <= rightHandSide.__movieID ? true : false);
		break;
	case 2:
		return (__rating <= rightHandSide.__rating ? true : false);
		break;

	case 3:
		return (__yearReleased <= rightHandSide.__yearReleased ? true : false);
		break;

	case 4:
		return (__title == rightHandSide.__title ? true : false);
		break;
	case 5:
		return (__runtimeMinutes == rightHandSide.__runtimeMinutes ? true : false);
	}

	return false;
}

bool Movie::operator>(const Movie & rightHandSide) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__movieID == rightHandSide.__movieID ? true : false);
		break;
	case 2:
		return (__rating == rightHandSide.__rating ? true : false);
		break;

	case 3:
		return (__yearReleased == rightHandSide.__yearReleased ? true : false);
		break;

	case 4:
		return (__title == rightHandSide.__title ? true : false);
		break;
	case 5:
		return (__runtimeMinutes == rightHandSide.__runtimeMinutes ? true : false);
	}

	return false;
}

bool Movie::operator>=(const Movie & rightHandSide) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__movieID >= rightHandSide.__movieID ? true : false);
		break;
	case 2:
		return (__rating >= rightHandSide.__rating ? true : false);
		break;

	case 3:
		return (__yearReleased >= rightHandSide.__yearReleased ? true : false);
		break;

	case 4:
		return (__title >= rightHandSide.__title ? true : false);
		break;
	case 5:
		return (__runtimeMinutes >= rightHandSide.__runtimeMinutes ? true : false);
	}

	return false;
}

std::ostream & operator<<(std::ostream & out, const Movie & movie)
{
	out << "Title: " << movie.__title << std::endl;
	out << "Movie ID: " << movie.__movieID << std::endl;
	out << "Rating: " << movie.__rating << std::endl;
	out << "Year Released: " << movie.__yearReleased << std::endl;
	out << "Runtime: " << movie.__runtimeMinutes << " minutes" << std::endl;
	out << "Genre(s): " << (movie.__genres) << std::endl;
	return out;
	// TODO: insert return statement here
}
