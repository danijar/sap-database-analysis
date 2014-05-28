#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "algorithm/ratios.h"
***REMOVED***
/*
* Responsible for querying field data from database and
* building a map of the tables and their fields and saving them
*/
class Structures
{
public:
	Structures(Ratios &Ratios, std::string Dsn, std::string User, std::string Password, std::string Path = "data/schemata.dump");
	void Fetch(std::string Dsn, std::string User, std::string Password, bool Output = false);
	std::unordered_set<Queries::Field> Common(size_t Parent_Id, size_t Child_Id);
	std::unordered_set<Queries::Field> Get(size_t Id);
***REMOVED***
	bool Load(std::string Path = "data/schemata.dump");
	bool Save(std::string Path = "data/schemata.dump");
	bool Saved(std::string Path = "data/schemata.dump");
	
private:
	size_t Size();
***REMOVED***
	std::vector<std::unordered_set<Queries::Field>> structures;
	std::unordered_map<std::string, size_t> &ids;
};
