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
	void List(size_t Limit = 16);
private:
	Input &input;
	std::unordered_set<size_t> &heads;
	std::vector<size_t> path;
	float Ratio(size_t From, size_t To);
	size_t Children(size_t Id);
	struct Child{ std::string Name; float Ratio; size_t Children; };
	void Table(std::string Parent, std::vector<Child> &Children, size_t Limit = 16);
	void Clear();
};
