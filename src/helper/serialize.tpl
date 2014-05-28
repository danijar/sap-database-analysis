#pragma once
#include "serialize.h"
***REMOVED***
***REMOVED***
template <typename TLeft, typename TRight> Serialize &Serialize::operator<<(const std::pair<TLeft, TRight> Value)
{
	*this << Value.first << Value.second;
	return *this;
}
***REMOVED***
template <typename T> Serialize &Serialize::operator<<(const std::vector<T> Value)
{
	*this << Value.size();
	for (auto i = Value.begin(); i != Value.end(); ++i)
		*this << *i;
	return *this;
}
***REMOVED***
template <typename T> Serialize &Serialize::operator<<(const std::unordered_set<T> Value)
{
	*this << Value.size();
	for (auto i = Value.begin(); i != Value.end(); ++i)
		*this << *i;
	return *this;
}
***REMOVED***
template <typename TKey, typename TVal> Serialize &Serialize::operator<<(const std::unordered_map<TKey, TVal> Value)
{
	*this << Value.size();
	for (auto i = Value.begin(); i != Value.end(); ++i)
		*this << i->first << i->second;
	return *this;
}
***REMOVED***
template <typename TLeft, typename TRight> Deserialize &Deserialize::operator>>(std::pair<TLeft, TRight> &Value)
{
	*this >> Value.first >> Value.second;
	return *this;
}
***REMOVED***
template <typename T> Deserialize &Deserialize::operator>>(std::vector<T> &Value)
{
	size_t size;
	*this >> size;
	for (size_t i = 0; i < size; ++i) {
		T value;
		*this >> value;
		Value.push_back(value);
	}
	return *this;
}
***REMOVED***
template <typename T> Deserialize &Deserialize::operator>>(std::unordered_set<T> &Value)
{
	size_t size;
	*this >> size;
	for (size_t i = 0; i < size; ++i) {
		T value;
		*this >> value;
		Value.insert(value);
	}
	return *this;
}
***REMOVED***
template <typename TKey, typename TVal> Deserialize &Deserialize::operator>>(std::unordered_map<TKey, TVal> &Value)
{
	size_t size;
	*this >> size;
	for (size_t i = 0; i < size; ++i) {
		TKey key;
		TVal val;
		*this >> key >> val;
		Value.insert(make_pair(key, val));
	}
	return *this;
}
