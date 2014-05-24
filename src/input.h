#pragma once
#include <string>
#include <vector>
#include <unordered_map>
***REMOVED***
***REMOVED***
/*
 * Responsible for querying input data from database and
 * generating a graph of tables and their ratios from it.
 */
class Input {
public:
	void Fetch(std::string Dsn, std::string User, std::string Password, bool Output = false);
	bool Load(std::string Path = "input.dump");
	bool Save(std::string Path = "input.dump");
	bool Saved(std::string Path = "input.dump");
	std::unordered_map<std::string, size_t> ids;
	std::unordered_map<size_t, std::string> names;
	std::unordered_map<size_t, std::unordered_map<size_t, float>> ratios;
private:
	struct row { std::string parent, child; float parentratio, childratio; };
	size_t Id(std::string name);
	std::vector<row> Query(std::string Dsn, std::string User, std::string Password);
	void Graph(std::vector<row> &Rows);
	size_t Size();
};
