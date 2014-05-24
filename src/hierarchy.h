#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "input.h"
***REMOVED***
***REMOVED***
class Hierarchy {
public:
	Hierarchy(Input &Input);
	std::unordered_map<std::string, size_t> &ids;
	std::unordered_map<size_t, std::string> &names;
	std::unordered_map<size_t, std::unordered_map<size_t, float>> &ratios;
	std::unordered_map<size_t, std::unordered_set<size_t>> children;
private:
	std::unordered_set<size_t> processed;
	std::unordered_set<size_t> Heads(Input &Input);
	void Children(size_t Id);
};
