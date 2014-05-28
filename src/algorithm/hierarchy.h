#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "algorithm/ratios.h"
***REMOVED***
***REMOVED***
/*
 * Finds a best matching tree hierarchy from input data.
 */
class Hierarchy {
public:
	Hierarchy(Ratios &Ratios, std::string Path = "data/hierarchy.dump");
	bool Load(std::string Path = "data/hierarchy.dump");
	bool Save(std::string Path = "data/hierarchy.dump");
	bool Saved(std::string Path = "data/hierarchy.dump");
***REMOVED***
	std::unordered_map<std::string, size_t> &ids;
	std::vector<std::string> &names;
	std::vector<std::unordered_map<size_t, float>> &ratios;
	std::vector<std::unordered_set<size_t>> children;
***REMOVED***
private:
	void Generate();
	void Children(size_t Id);
***REMOVED***
	std::unordered_set<size_t> processed;
	std::unordered_set<size_t> Heads();
};
