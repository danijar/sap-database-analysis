#include <string>
#include <vector>
#include <unordered_map>
***REMOVED***
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
***REMOVED***
***REMOVED***
/*
 * Responsible for querying input data from database and
 * generating a graph of tables and their ratios from it.
 */
class Input {
public:
	Input(std::string Dsn, std::string User, std::string Password, bool Output = false);
	std::unordered_map<std::string, size_t> ids;
	std::unordered_map<size_t, std::unordered_map<size_t, float>> ratios;
private:
	struct row { std::string parent, child; float parentratio, childratio; };
	size_t Id(std::string name);
	void Ratio(size_t From, size_t To, float Weight);
	std::vector<row> Query(std::string Dsn, std::string User, std::string Password, bool Output = false);
	size_t Size();
};
