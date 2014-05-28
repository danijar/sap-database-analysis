#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
***REMOVED***
***REMOVED***
/*
 * Stream to serialize values to disk.
 */
class Serialize {
public:
	Serialize(std::string Path);
	~Serialize();
	bool Good();
	Serialize &operator<<(const size_t Value);
	Serialize &operator<<(const float Value);
	Serialize &operator<<(const std::string Value);
	template <typename TLeft, typename TRight> Serialize &operator<<(const std::pair<TLeft, TRight> Value);
	template <typename T> Serialize &operator<<(const std::vector<T> Value);
	template <typename T> Serialize &operator<<(const std::unordered_set<T> Value);
	template <typename TKey, typename TVal> Serialize &operator<<(const std::unordered_map<TKey, TVal> Value);
private:
	std::ofstream stream;
};
***REMOVED***
***REMOVED***
/*
 * Stream to deserialize values from disk.
 */
class Deserialize {
public:
	Deserialize(std::string Path);
	~Deserialize();
	bool Good();
	Deserialize &operator>>(size_t &Value);
	Deserialize &operator>>(float &Value);
	Deserialize &operator>>(std::string &Value);
	template <typename TLeft, typename TRight> Deserialize &operator>>(std::pair<TLeft, TRight> &Value);
	template <typename T> Deserialize &operator>>(std::vector<T> &Value);
	template <typename T> Deserialize &operator>>(std::unordered_set<T> &Value);
	template <typename TKey, typename TVal> Deserialize &operator>>(std::unordered_map<TKey, TVal> &Value);
private:
	std::ifstream stream;
};
***REMOVED***
// Templates
#include "serialize.tpl"
