#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "input.h"
***REMOVED***
***REMOVED***
/*
 * Finds a best matching tree hierarchy from input data.
 */
class Hierarchy {
public:
	Hierarchy(Input &Input, std::string Path = "hierarchy.dump");
	void Generate();
	bool Load(std::string Path = "hierarchy.dump");
	bool Save(std::string Path = "hierarchy.dump");
	bool Saved(std::string Path = "hierarchy.dump");
***REMOVED***
	std::unordered_map<std::string, size_t> &ids;
	std::unordered_map<size_t, std::string> &names;
	std::unordered_map<size_t, std::unordered_map<size_t, float>> &ratios;
	std::unordered_map<size_t, std::unordered_set<size_t>> children;
private:
	void Children(size_t Id);
***REMOVED***
	std::unordered_set<size_t> processed;
	std::unordered_set<size_t> Heads();
};
