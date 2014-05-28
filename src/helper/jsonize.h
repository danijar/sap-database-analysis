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
	void write_to_file();
***REMOVED***
	Jsonize &operator<<(const std::string &Value);
	template <typename T> Jsonize &operator<<(const T &Value);
	template <typename T> Jsonize &operator<<(const std::vector<T> &Value);
	template <typename T> Jsonize &operator<<(const std::unordered_set<T> &Value);
	template <typename TKey, typename TVal> Jsonize &operator<<(const std::unordered_map<TKey, TVal> &Value);
private:
	std::stringstream stream;
	std::string path;
};
***REMOVED***
// Templates
#include "jsonize.tpl"
