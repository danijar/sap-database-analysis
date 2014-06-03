#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "algorithm/ratios.h"
#include "helper/bar.h"
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
	std::unordered_set<std::string> &names;
	//std::unordered_map<std::string, size_t> &ids;
	// We have to build this for ourself
	std::unordered_map<std::string, std::unordered_map<std::string, float>> &ratios;
	std::unordered_map<std::string, std::unordered_set< std::string >> children;
	std::unordered_map<std::string, size_t> amounts;
***REMOVED***
private:
	void Generate();
	void Children(std::string Id);
	std::unordered_set<std::string> Heads();
	size_t Amount(std::string Id, Bar *Bar);
***REMOVED***
	std::unordered_set<std::string> processed;
};
