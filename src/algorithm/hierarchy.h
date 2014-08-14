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
	Hierarchy(Ratios &Ratios, std::string Path = "data/hierarchy.dump", bool ForceFetch = false);
	bool Load(std::string Path = "data/hierarchy.dump");
	bool Save(std::string Path = "data/hierarchy.dump");
	bool Saved(std::string Path = "data/hierarchy.dump");
	void Generate();
	std::unordered_set<size_t> Subchildren(size_t Root);
***REMOVED***
	std::unordered_map<std::string, size_t> &ids;
	std::vector<std::unordered_set<std::string>> &names;
	std::vector<std::unordered_map<size_t, float>> &ratios;
	std::vector<std::unordered_set<size_t>> children;
	std::vector<size_t> amounts;
***REMOVED***
private:
	void Children(size_t Id);
	std::unordered_set<size_t> Heads();
	size_t Amount(size_t Id, Bar *Bar);
***REMOVED***
	std::unordered_set<size_t> processed;
};
