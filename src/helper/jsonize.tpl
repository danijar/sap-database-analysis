#pragma once
#include "jsonize.h"
***REMOVED***
template <typename T> Jsonize &Jsonize::operator<<(const T &Value)
{
	this->stream << Value;
	return *this;
}
***REMOVED***
template <typename TLeft, typename TRight> Jsonize &Jsonize::operator<<(const std::pair<TLeft, TRight> Value)
{
	stream << "[";
	*this << Value.first << "," << Value.second;
	stream << "]";
	return *this;
}
***REMOVED***
template <typename T> Jsonize &Jsonize::operator<<(const std::vector<T> &Value)
{
	stream << "[";
	if (Value.begin() != Value.end()) {
		*this << *Value.begin();
		for (auto i = (++Value.begin()); i != Value.end(); ++i)
			*this << "," << *i; // TOOD: Can we stream the colon into *this instead of stream?
	}
	stream << "]";
	return *this;
}
***REMOVED***
template <typename T> Jsonize &Jsonize::operator<<(const std::unordered_set<T> &Value)
{
	stream << "[";
	if (Value.begin() != Value.end()) {
		*this << *Value.begin();
		for (auto i = (++Value.begin()); i != Value.end(); ++i)
			*this << "," << *i;
	}
	stream << "]";
	return *this;
}
***REMOVED***
template <typename TKey, typename TVal> Jsonize &Jsonize::operator<<(const std::unordered_map<TKey, TVal> &Value)
{
	stream << "{";
	if (Value.begin() != Value.end()) {
		*this << to_string(Value.begin()->first) << ":" << Value.begin()->second;
		for (auto i = (++Value.begin()); i != Value.end(); ++i)
			*this << "," << to_string(i->first) << ":" << i->second;
	}
	stream << "}";
	return *this;
}
