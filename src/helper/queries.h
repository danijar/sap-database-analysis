#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "helper/bar.h"
#include "helper/serialize.h"
***REMOVED***
***REMOVED***
/*
 * This namespace holds all code that connects to the database.
 */
namespace Queries {
	// Struct for the ratio rows
	struct ratio_row {
		std::string parent, child;
		float parentratio, childratio;
	};
***REMOVED***
	// Struct for the field values
	struct Field {
		std::string name, roll, domain;
		size_t position;
		bool operator==(const Field &other) const
		{
			return name == other.name;
		}
	};
	Serialize &operator<<(Serialize &serialize, const Field &field);
	Deserialize &operator>>(Deserialize &deserialize, Field &field);
***REMOVED***
	std::unordered_set<std::string> Schema(std::string Table);
	std::vector<ratio_row> Ratios(std::string Dsn, std::string User, std::string Password);
	std::vector<Field> Fields(std::string Table, std::string Dsn, std::string User, std::string Password);
	std::unordered_map<size_t, std::unordered_set<Field>> Schemata(std::unordered_map<std::string, size_t> &Ids,
		std::string Dsn, std::string User, std::string Password);
}
***REMOVED***
namespace std {
	template <>
	struct hash<Queries::Field>
	{
		size_t operator()(const Queries::Field &f) const {
			using std::hash;
			return (hash<string>()(f.name)
				^ ((hash<string>()(f.roll)     << 1) >> 1)
				^ ((hash<string>()(f.domain)   << 1) >> 1)
				^ ((hash<size_t>()(f.position) << 1) >> 1));
		}
	};
}
