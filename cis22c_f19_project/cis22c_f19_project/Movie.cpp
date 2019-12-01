//#include "Movie.h"
//
//Movie::Movie()
//{
//	__actorIDs = new List<std::string>();
//	__year = -1;
//	__rating = -1;
//	__genre = "";
//	__title = "";
//	__movieID = "";
//}
//
//Movie::Movie(std::string title, std::string genre, int year, double rating)
//{
//	__title = title;
//	__genre = genre;
//	__year = year;
//	__rating = rating;
//	__actorIDs = new List<std::string>();
//}
//
//bool Movie::addActor(const Actor & actor)
//{
//	if (actor.getID() == "")
//		return false;
//	else
//	{
//		__actorIDs->sortedInsert(actor.getID());
//		return true;
//	}
//	return false;
//}
//
//bool Movie::addActor(const std::string& actorID)
//{
//	if (actorID.length() == 0)
//		return false;
//	else
//	{
//		__actorIDs->sortedInsert(actorID);
//		return true;
//	}
//	return false;
//}
//
//bool Movie::removeActor(std::string)
//{
//	return false;
//}
//
//bool Movie::operator==(const Movie & rightHandSide) const
//{
//	switch(__compareConfig)
//		case 1:
//		case 2:
//		case 3:
//
//	return false;
//}
//
//bool Movie::operator<(const Movie & rightHandSide) const
//{
//	return false;
//}
//
//bool Movie::operator>(const Movie & rightHandSide) const
//{
//	return false;
//}
//
//void Movie::setComparisonConfig(int config)
//{
//	if (!(config > 0 && config < 4))
//	{
//		throw CustomException("Invalid Comparison Operator Configuration");
//	}
//	else
//		__compareConfig = config;
//
//}
