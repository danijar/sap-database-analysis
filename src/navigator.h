#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "input.h"
***REMOVED***
***REMOVED***
class Navigator {
public:
	Navigator(Input &Input, std::unordered_set<size_t> &Heads);
	bool Go(std::string Name);
	bool Up();
	void List();
private:
	Input &input;
	std::unordered_set<size_t> &heads;
	std::vector<size_t> path;
	size_t Children(size_t Id);
};
