#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "input.h"
#include "serialize.h"
***REMOVED***
/*
* Responsible for querying field data from database and
* building a map of the tables and their fields and saving them
*/
class Schemata
{
public:
	Schemata(Input &Input, std::string Dsn, std::string User, std::string Password, std::string Path = "schema.dump");
***REMOVED***
	void Fetch(std::string Dsn, std::string User, std::string Password, bool Output = false);
	bool Load(std::string Path = "schema.dump");
	bool Save(std::string Path = "schema.dump");
	bool Saved(std::string Path = "schema.dump");
	
private:
	size_t Size();
***REMOVED***
	std::unordered_map<size_t, std::unordered_set<Queries::Field>> schemata;
	std::unordered_map<std::string, size_t> &ids;
};
