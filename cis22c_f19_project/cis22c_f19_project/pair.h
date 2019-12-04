#ifndef PAIR_H
#define PAIR_H
template <typename K, typename V>
class Pair {
private:

	K		__key;
	V		__value;
	/* 1: compare by key
	2: compare by value */
	int		__compareConfig;

public:
	Pair(): __compareConfig(2) {}
	Pair(const K& key, const V& value) : __compareConfig(0) {}
	V getValue() const { return __value; }
	K getKey() const { return __key; }

	bool operator==(const Pair& pair) const;
	bool operator<(const Pair& pair) const;
	bool operator<=(const Pair& pair) const;
	bool operator>(const Pair& pair) const;
	bool operator>=(const Pair& pair) const;
	void setValue(const V& value) { __value = value; }
	void setKey(const K& key) {	__key = key; }
	/* 1: compare by key
	2: compare by value */
	void setCompareByKey() { __compareConfig = 1; }
	void setCompareByValue() { __compareConfig = 2; }
};


template<typename K, typename V>
bool Pair<K, V>::operator==(const Pair & pair) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__key == pair.__key ? true : false);
		break;

	case 2:
		return (__value == pair.__value ? true : false);
		break;

	}
	return false;
}

template<typename K, typename V>
bool Pair<K, V>::operator<(const Pair & pair) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__key < pair.__key ? true : false);
		break;
	case 2:
		return (__value < pair.__value ? true : false);
		break;

	}
	return false;
}

template<typename K, typename V>
bool Pair<K, V>::operator<=(const Pair & pair) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__key <= pair.__key ? true : false);
		break;

	case 2:
		return (__value <= pair.__value ? true : false);
		break;

	}
	return false;
}

template<typename K, typename V>
bool Pair<K, V>::operator>(const Pair & pair) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__key > pair.__key ? true : false);
	case 2:
		return (__value > pair.__value ? true : false);

	}
	return false;
}

template<typename K, typename V>
bool Pair<K, V>::operator>=(const Pair & pair) const
{
	switch (__compareConfig)
	{
	case 1:
		return (__key >= pair.__key ? true : false);
		break;

	case 2:
		return (__value >= pair.__value ? true : false);
		break;

	}
	return false;
}

#endif // !PAIR_H
