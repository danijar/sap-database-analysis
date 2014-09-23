#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <chrono>
#include "helper/queries.h"
#include "algorithm/ratios.h"
#include "algorithm/hierarchy.h"
#include "algorithm/structures.h"
#include "tool/benchmark.h"
#include "tool/navigator.h"
#include "helper/benchmark.h"
#include "helper/bar.h"
using namespace std;

void storeInDB(size_t tabID, Hierarchy hierarchy, Structures structures) {
	// Reset tables
	Queries::Create();

	// Fill with all tables in cluster
	unordered_set<size_t> subchildren = hierarchy.Subchildren(tabID);
	subchildren.insert(tabID);
	Bar bar("Store", subchildren.size());
	for (auto i = subchildren.begin(); i != subchildren.end(); i++, bar++) {
		// Compute ratio to parent
		float ratio = 0.0f;
		for (size_t j = 0; j < hierarchy.children.size(); ++j) {
			if (hierarchy.children[j].find(*i) != hierarchy.children[j].end()) {
				ratio = hierarchy.ratios[j][*i];
				break;
			}
		}

		// Insert into database
		bool result = Queries::Store(*i,
			hierarchy.names[*i],
			hierarchy.children[*i],
			structures.added[*i],
			structures.removed[*i],
			hierarchy.amounts[*i],
			ratio,
			structures.changes[*i],
			structures.removing[*i]
			);
	}
	bar.Finish();
}


void loadConfig() {
	ifstream dbConnectionFile("Settings.cfg");
	if (!dbConnectionFile.good() || dbConnectionFile.eof())
		return;
	
	char keyBuffer[200];
	char valueBuffer[200];
	while (!dbConnectionFile.eof()) {
		// Read identifier
		dbConnectionFile.getline(keyBuffer, 200);
		if (!dbConnectionFile.good() || dbConnectionFile.eof())
			return;
		// Now the next value and assing
		dbConnectionFile.getline(valueBuffer, 200);

		if (strcmp(keyBuffer, "Dsn:") == 0)
			Queries::Dsn = string(valueBuffer);
		if (strcmp(keyBuffer, "User:") == 0)
			Queries::User = string(valueBuffer);
		if (strcmp(keyBuffer, "Password:") == 0)
			Queries::Password = string(valueBuffer);
		if (strcmp(keyBuffer, "DBSchema:") == 0)
			Queries::DBSchema = string(valueBuffer);
		if (strcmp(keyBuffer, "InputTable:") == 0)
			Queries::InputTable = string(valueBuffer);
		if (strcmp(keyBuffer, "FieldsTable:") == 0)
			Queries::FieldsTable = string(valueBuffer);
		if (strcmp(keyBuffer, "OutputPrefix:") == 0)
			Queries::OutputPrefix = string(valueBuffer);
	}

}

int main(int argc, char *argv[])
{
	// Load from files if possible
	loadConfig();

	// Compute ratio graph, hierarchy and differences
	bool force_fetch = false;

	if (argc > 1 && strcmp(argv[1], "clean") == 0)
		force_fetch = true;

	Ratios ratios("data/ratios.dump", force_fetch);
	Hierarchy hierarchy(ratios, "data/hierarchy.dump", force_fetch);
	Structures structures(ratios, hierarchy, "data/structures.dump", force_fetch);

	/*
	// Benchmark structure generation
	Benchmark::Output = true;
	Bar::Output = false;
	cout << "Start benchmark." << endl;
	Benchmark benchmark("Overall");
	for (size_t i = 0; i < 100; ++i) {
		benchmark.Round();
		ratios.Generate();
		hierarchy.Generate();
	}
	benchmark.Finish();
	*/

	/*
	// Wait for user input
	cout << "Press enter to start hierarchy navigator..." << endl;
	cout.flush();
	cin.get();
	*/
	
	// Check if only need to export
	if (argc > 1 && strcmp(argv[argc-1], "export") == 0) {
		storeInDB(0, hierarchy, structures);
		return 0;
	}

	// Navigate through hierarchie
	Navigator navigator(hierarchy, structures);
}
