#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include "algorithm/ratios.h"
#include "algorithm/hierarchy.h"
***REMOVED***
***REMOVED***
/*
* Responsible for querying field data from database and
* building a map of the tables and their fields and saving them
*/
class Structures
{
public:
	Structures(Ratios &Ratios, Hierarchy &Hierarchy, std::string Path = "data/structures.dump");
	void Fetch(bool Output = false);
	bool Load(std::string Path = "data/structures.dump");
	bool Save(std::string Path = "data/structures.dump");
	bool Saved(std::string Path = "data/structures.dump");
	std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>> Difference(size_t Parent, size_t Child);
	std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>> &Difference(size_t Child);
	
private:
	void Generate();
	size_t Size();
***REMOVED***
	std::vector<std::unordered_set <Queries::Field>> structures;
	std::vector<std::pair<std::unordered_set<std::string>, std::unordered_set<std::string>>> differences;
	std::unordered_map<std::string, size_t> &ids;
	Hierarchy &hierarchy;
};
