#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>
***REMOVED***
***REMOVED***
/*
 * Stream to serialize values to disk.
 */
class Jsonize {
public:
	Jsonize(std::string Path);
	~Jsonize();
	Jsonize &operator<<(const std::string &Value);
	template <typename T> Jsonize &operator<<(const T &Value);
	template <typename TLeft, typename TRight> Jsonize &operator<<(const std::pair<TLeft, TRight> Value);
	template <typename T> Jsonize &operator<<(const std::vector<T> &Value);
	template <typename T> Jsonize &operator<<(const std::unordered_set<T> &Value);
	template <typename TKey, typename TVal> Jsonize &operator<<(const std::unordered_map<TKey, TVal> &Value);
	bool Flush();
private:
	std::stringstream stream;
	std::string path;
	bool flushed = false;
};
***REMOVED***
// Templates
#include "jsonize.tpl"
