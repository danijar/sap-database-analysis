#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "queries.h"
***REMOVED***
/*
 * Responsible for querying input data from database and
 * generating a graph of tables and their ratios from it.
 */
class Input {
public:
	Input(std::string Dsn, std::string User, std::string Password, std::string Path = "input.dump");
	bool Save(std::string Path = "input.dump");
	bool Saved(std::string Path = "input.dump");
	void Fetch(std::string Dsn, std::string User, std::string Password, bool Output = false);
	bool Load(std::string Path = "input.dump");
***REMOVED***
	std::unordered_map<std::string, size_t> ids;
	std::unordered_map<size_t, std::string> names;
	std::unordered_map<size_t, std::unordered_map<size_t, float>> ratios;
***REMOVED***
private:
	
	void Graph(std::vector<Queries::ratio_row > &Rows);
	size_t Size();
	size_t Id(std::string name);
};
