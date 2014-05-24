#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "hierarchy.h"
***REMOVED***
***REMOVED***
/*
 * Console based navigation through our result set. Currently,
 * it operated just on the input data rather than the hierarchy.
 */
class Navigator {
public:
	Navigator(Hierarchy &Hierarchy);
	bool Go(std::string Name);
	bool Up();
	void List(size_t Limit = 16, bool Reverse = false);
private:
	Hierarchy &hierarchy;
	std::vector<size_t> path;
	float Ratio(size_t From, size_t To);
	size_t Children(size_t Id);
	struct Child{ std::string Name; float Ratio; size_t Children; };
	void Table(std::string Parent, std::vector<Child> &Children, size_t Limit = 16);
	void Difference(std::string Left, std::string Right);
	void Clear();
};
