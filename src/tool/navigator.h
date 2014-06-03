#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "algorithm/hierarchy.h"
#include "algorithm/structures.h"
***REMOVED***
***REMOVED***
/*
 * Console based navigation through our result set. Currently,
 * it operated just on the input data rather than the hierarchy.
 */
class Navigator {
public:
	Navigator(Hierarchy &Hierarchy, Structures &Structures);
	bool Go(std::string Name);
	bool Up();
	void List(size_t Limit = 16, bool Reverse = false);
private:
	struct Child{ std::string Name; float Ratio; size_t Children; };
***REMOVED***
	float Ratio(std::string From, std::string To);
	void Table(std::string Id, std::vector<Child> &Children, size_t Limit = 16);
	void Difference(std::string Table);
	void Clear();
***REMOVED***
	Hierarchy &hierarchy;
	Structures &structures;
	std::vector<std::string> path;
};
