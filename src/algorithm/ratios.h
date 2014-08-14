#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "type/ratio.h"
***REMOVED***
/*
 * Responsible for querying input data from database and
 * generating a graph of tables and their ratios from it.
 */
class Ratios {
public:
	Ratios(std::string Path = "data/ratios.dump", bool ForceFetch = false);
	void Fetch(bool Output = false);
	bool Load(std::string Path = "data/ratios.dump");
	bool Save(std::string Path = "data/ratios.dump");
	bool Saved(std::string Path = "data/ratios.dump");
	void Generate();
***REMOVED***
	std::vector<Ratio> rows;
	std::unordered_map<std::string, size_t> ids;
	std::vector<std::unordered_set<std::string>> names;
	std::vector<std::unordered_map<size_t, float>> ratios;
***REMOVED***
private:
	size_t Size();
	size_t Id(std::string name);
};
