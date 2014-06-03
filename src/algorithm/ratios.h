#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "helper/queries.h"
***REMOVED***
/*
 * Responsible for querying input data from database and
 * generating a graph of tables and their ratios from it.
 */
class Ratios {
public:
	Ratios(std::string Path = "data/ratios.dump");
	void Fetch(bool Output = false);
	bool Load(std::string Path = "data/ratios.dump");
	bool Save(std::string Path = "data/ratios.dump");
	bool Saved(std::string Path = "data/ratios.dump");
	
	//std::unordered_map<std::string, size_t> ids;
	std::unordered_set<std::string> names;
	std::unordered_map<std::string, std::unordered_map<std::string, float>> ratios;
***REMOVED***
private:
	void Graph(std::vector<Queries::Ratio > &Rows);
	size_t Size();
	size_t Id(std::string name);
};
