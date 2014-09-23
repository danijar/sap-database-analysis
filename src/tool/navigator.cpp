#include "navigator.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <cstdlib>
#include "helper/queries.h"
#include "helper/charts.h"
#include "helper/jsonize.h"
using namespace std;
using namespace std::tr2::sys;


// Constructor
Navigator::Navigator(Hierarchy &Hierarchy, Structures &Structures) : hierarchy(Hierarchy), structures(Structures)
{
	Clear();
	List();

	for (;;) {
		// Read user hierarchy
		cout << endl << "> ";
		string command;
		cin >> command;
		cout << endl;

		// One table up
		if (command == "back") {
			if (Up()) {
				Clear();
				List();
			}
			else {
				cout << "No previous table to go to." << endl;
			}
		}

		// Root level
		else if (command == "root") {
			path.clear();
			Clear();
			List();
		}

		// List scheme
		else if (command == "scheme") {
			if (path.size()) {
				vector<Field> fields = Queries::Fields(*hierarchy.names[path.back()].begin());
				for (auto i : fields)
					cout << i.name << " ";
				cout << endl;
			}
			else {
				cout << "Select a table first." << endl;
			}
		}

		// List whole children
		else if (command == "more") {
			// Ask for parameters
			int limit;
			cout << "Limit: ";
			cin >> limit;

			Clear();
			List(abs(limit), limit < 0);
		}

		// List a difference between two table schemes
		else if (command == "diff") {
			// Ask for parameter
			cout << "Child: ";
			string table;
			cin >> table;
			cout << endl;

			Difference(table);
		}

		// Exit navigator
		else if (command == "exit" || command == "quit") {
			Clear();
			return;
		}

		// Draw histogram of children and their number of occurrence.
		else if (command == "histo") {
			// Ask for parameters
			size_t limit;
			cout << "Limit: ";
			cin >> limit;
			cout << endl;

			// Fetch and sort children
			size_t id = path.size() ? path.back() : 0;
			vector<size_t> data;
			data.reserve(hierarchy.children[id].size());
			for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i)
				data.push_back(hierarchy.amounts[*i]);
			sort(data.begin(), data.end(), greater<size_t>());

			// Apply limit and plot
			if (limit > data.size() - 1) {
				limit = 0;
				cout << "Adjusted limit to not exceed number of children." << endl << endl;
			}
			if (limit)
				data.resize(limit);
			Charts::Histogram(data);
		}

		// Write JSON files of names, children and differences for current tree
		else if (command == "json") {
			// Get current table id and name
			size_t id = path.size() ? path.back() : 0;

			// Implode all string names for one id
			string name = "";
			for (auto i = hierarchy.names[id].begin(); i != hierarchy.names[id].end(); i++)
				name += *i;

			name.erase(remove(name.begin(), name.end(), '<'), name.end());
			name.erase(remove(name.begin(), name.end(), '>'), name.end());
			name = "data/" + name;

			// Create dump
			if (Json(name, id))
				cout << "Successfully wrote JSON files to \"" << name << "\" folder." << endl;
			else
				cout << "Error writing the file" << endl;
		}

		// Write CSV file of current children and their number of children
		else if (command == "csv") {
			// Fetch and children and amounts
			size_t id = path.size() ? path.back() : 0;
			vector<pair<string, size_t>> data;
			data.reserve(hierarchy.children[id].size());
			for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i)
				data.push_back(make_pair(*hierarchy.names[*i].begin(), hierarchy.amounts[*i]));

			// Sort data
			sort(data.begin(), data.end(), [](pair<string, size_t> l, pair<string, size_t> r) { return l.second < r.second; });

			// Table without special chars as file name
			string name = *hierarchy.names[id].begin();
			name.erase(remove(name.begin(), name.end(), '<'), name.end());
			name.erase(remove(name.begin(), name.end(), '>'), name.end());
			name += ".csv";
			ofstream out("data/" + name);

			// Save to disk
			out << "sep=;" << endl;
			out << "Table;Amount" << endl;
			for (auto i = data.begin(); i != data.end(); ++i)
				out << i->first << ";" << i->second << endl;
			out.close();

			// Output
			cout << "Wrote table names and their amount of children to " << name << "." << endl;
		}

		// Write all informations of current table to database
		else if (command == "store") {
			// Get current table
			size_t id = path.size() ? path.back() : 0;
			
			// Reset tables
			Queries::Create();

			// Fill with all tables in cluster
			unordered_set<size_t> subchildren = hierarchy.Subchildren(id);
			subchildren.insert(id);
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

		// Show available commands
		else if (command == "help") {
			cout << "To navigate to a table, enter its name." << endl;
			cout << "back"   << "\t" << "Go back to the table you saw before." << endl;
			cout << "root"   << "\t" << "Go to the root level that lists all table heads." << endl;
			cout << "scheme" << "\t" << "List column scheme of the current table. Needs connection to database." << endl;
			cout << "more"   << "\t" << "List all children of the current table." << endl;
			cout << "diff"   << "\t" << "Show changes from current table to a child." << endl;
			cout << "histo"  << "\t" << "Draw histogram of children and their number of occurrence." << endl;
			cout << "json"   << "\t" << "Write JSON files of names, children and differences for current tree." << endl;
			cout << "csv"    << "\t" << "Write CSV file of current children and their number of children." << endl;
			cout << "store"  << "\t" << "Write all informations of current table to database." << endl;
			cout << "exit"   << "\t" << "Exit the navigator. Synonyms: quit." << endl;
		}

		// Navigate to table
		else {
			if (Go(command)) {
				Clear();
				List();
			} else {
				cout << "'" << command << "' is neither a table name nor a command. Enter 'help' to see a list of all available commands." << endl;
			}
		}
	}
}

// Go down one level in the hierarchie
bool Navigator::Go(string Name)
{
	// Find node navigating to
	auto i = hierarchy.ids.find(Name);

	// Name doesn't match
	if (i == hierarchy.ids.end())
		return false;

	// Add to path
	path.push_back(i->second);
	return true;
}

// Get one level up in the hierarchie
bool Navigator::Up()
{
	// If already on the highest level
	if (!path.size())
		return false;

	// Remove last from path
	size_t node = path.back();
	path.pop_back();
	return true;
}

// List children of current table
void Navigator::List(size_t Limit, bool Reverse)
{
	// Name and id of current table
	size_t id = path.size() ? path.back() : 0;

	// Prepare vector of children
	vector<Child> children;
	if (id < hierarchy.children.size()) {
		for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i) {
			Child child;
			child.Name = *hierarchy.names[*i].begin();
			if(hierarchy.names[*i].size() > 1) child.Name += " " + hierarchy.names[*i].size();
			child.Children = hierarchy.children[*i].size();
			child.Ratio = Ratio(id, *i);
			children.push_back(child);
		}
	}

	// Sort by ratio to parent, on root level by number of children
	if (path.size()) {
		auto comparator = [Reverse](const Child &A, const Child &B) { return A.Ratio > B.Ratio != Reverse; };
		sort(children.begin(), children.end(), comparator);
	}
	else {
		auto comparator = [Reverse](const Child &A, const Child &B) { return A.Children > B.Children != Reverse; };
		sort(children.begin(), children.end(), comparator);
	}

	// Print children
	Table(id, children, Limit);
}

// Get ratio between to tables
float Navigator::Ratio(size_t From, size_t To)
{
	// Check for table
	if (From > hierarchy.ratios.size() - 1)
		return -1;

	// Check for connection to child
	auto j = hierarchy.ratios[From].find(To);
	if (j == hierarchy.ratios[From].end())
		return -1;

	return j->second;
}

// Print out the passed children as table
void Navigator::Table(size_t Id, vector<Child> &Children, size_t Limit)
{
	// Store default formatting
	auto format = cout.flags();

	// Headline
	cout << *hierarchy.names[Id].begin() << (hierarchy.names[Id].size() > 1 ? " " + to_string(hierarchy.names[Id].size()) : " ")  << endl;
	for (size_t i = 0; i < hierarchy.names[Id].begin()->length() + 2; ++i)
		cout << "=";
	cout << endl;

	// Print message and return if no rows
	if (!Children.size()) {
		cout << "Found no tables." << endl;
		return;
	}

	// Show number of rows
	cout << "Found " << hierarchy.amounts[Id] << " overall and " << Children.size() << (Children.size() > 1 ? " direct children." : " child.") << endl << endl;

	// Find column widths
	size_t width_name = 0, width_children = 0, width_ratio = 4;
	for (auto i = Children.begin(); i != Children.end(); ++i) {
		// Name
		if (i->Name.length() > width_name)
			width_name = i->Name.length();

		// Number of Children
		size_t number = i->Children;
		size_t digits = 0;
		while (number) {
			number /= 10;
			digits++;
		}
		if (digits > width_children)
			width_children = digits;
	}

	// Table head
	if (width_name < 5)
		width_name = 5;
	if (width_children < 4)
		width_children = 4;
	if (width_ratio < 5)
		width_ratio = 5;
	cout << setw(width_ratio) << left << "Ratio" << " ";
	cout << setw(width_children) << left << "Sons" << " ";
	cout << setw(width_name) << left << "Table" << " ";
	cout << endl;
	for (size_t i = 0; i < width_ratio; ++i)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_children; ++i)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_name; ++i)
		cout << "-";
	cout << endl;

	// Loop up to table limit
	for (size_t i = 0; i < Limit || !Limit; ++i) {
		// Return if no more rows
		if (i > Children.size() - 1)
			return;

		// Print current row
		Child child = Children[i];
		if (child.Ratio > 0) {
			cout << setw(width_ratio) << right << setprecision(2) << fixed << child.Ratio << " ";
		}
		else {
			for (size_t j = 0; j < width_ratio - 1; ++j)
				cout << " ";
			cout << "- ";
		}
		cout << setw(width_children) << right << child.Children << " ";
		cout << setw(width_name) << left << child.Name << " ";
		cout << endl;
	}

	// Print continuation indicator
	cout << "..." << endl;

	// Reset formatting options
	cout.flags(format);
}

// Show a diff between two tables
void Navigator::Difference(string Table)
{
	// Validate hierarchy
	if (hierarchy.ids.find(Table) == hierarchy.ids.end()) {
		cout << "'" << Table << "' is no valid table name." << endl;
		return;
	}

	// Get differences
	size_t id = hierarchy.ids[Table];
	auto differences = structures.Difference(id);
	unordered_set<string> &added = differences.first;
	unordered_set<string> &removed = differences.second;

	// Find column widths
	size_t width_added = 5, width_removed = 7;
	for (auto i = added.begin(); i != added.end(); ++i)
	if (i->length() > width_added)
		width_added = i->length();
	for (auto i = removed.begin(); i != removed.end(); ++i)
	if (i->length() > width_removed)
		width_removed = i->length();

	// Store default formatting
	auto format = cout.flags();

	// Draw headline
	cout << "Changes to " << Table << endl;
	for (size_t i = 0; i < 11 + Table.length(); ++i)
		cout << "=";
	cout << endl << endl;

	// Draw table captions
	cout << left;
	cout << setw(width_added) << "Added ";
	cout << setw(width_removed) << "Removed" << endl;
	for (size_t i = 0; i < width_added; i++)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_removed; i++)
		cout << "-";
	cout << " " << endl;

	// Draw table rows
	auto a = added.begin();
	auto r = removed.begin();
	for (size_t i = 0; i < max(added.size(), removed.size()); ++i) {
		// Added column
		cout << setw(width_added);
		if (a != added.end()) {
			cout << *a << " ";
			a++;
		}
		else cout << " " << " ";

		// Removed column
		cout << setw(width_removed);
		if (r != removed.end()) {
			cout << *r << " ";
			r++;
		}
		else cout << " " << " ";

		cout << endl;
	}

	// Reset formatting options
	cout.flags(format);
}

bool Navigator::Json(string Folder, size_t Root)
{
	// Check for bounds
	if (Root > hierarchy.names.size() - 1)
		return false;

	// Create folder
	auto folder = initial_path<tr2::sys::path>() /= Folder;
	if (!exists(folder))
		create_directories(folder);

	// Create json streams
	Jsonize out_children(Folder + "/children.json");
	Jsonize out_added   (Folder + "/added.json"   );
	Jsonize out_removed (Folder + "/removed.json" );
	Jsonize out_amounts (Folder + "/amounts.json" );
	Jsonize out_names   (Folder + "/names.json"   );
	Jsonize out_changes (Folder + "/changes.json" );
	Jsonize out_removing(Folder + "/removing.json");

	// Get recursive children
	unordered_set<size_t> subchildren = hierarchy.Subchildren(Root);
	subchildren.insert(Root);

	// Output
	cout << "Exporting cluster of " << subchildren.size() << " tables." << endl;

	// Create containers for data limited to passed root
	unordered_map<size_t, unordered_set<string>> names;
	unordered_map<size_t, size_t> amounts;
	unordered_map<size_t, unordered_set<size_t>> children;
	unordered_map<size_t, unordered_set<string>> added, removed;
	unordered_map<size_t, float> changes;
	unordered_map<size_t, bool> removing;

	// Set sizes
	names.reserve(subchildren.size());
	children.reserve(subchildren.size());
	added.reserve(subchildren.size());
	removed.reserve(subchildren.size());
	amounts.reserve(subchildren.size());
	changes.reserve(subchildren.size());
	removing.reserve(subchildren.size());

	// Fill containers
	for (auto i = subchildren.begin(); i != subchildren.end(); ++i) {
		names[*i] = hierarchy.names[*i];
		amounts[*i] = hierarchy.amounts[*i];
		children[*i] = hierarchy.children[*i];
		added[*i] = structures.added[*i];
		removed[*i] = structures.removed[*i];
		changes[*i] = structures.changes[*i];
		removing[*i] = structures.removing[*i];
	}

	// Write to JSON streams
	out_children << children;
	out_added << added;
	out_removed << removed;
	out_amounts << amounts;
	out_names << names;
	out_changes << changes;
	out_removing << removing;

	// Flush files
	bool result = out_children.Flush() && out_added.Flush() && out_removed.Flush() && out_amounts.Flush() && out_names.Flush() && out_changes.Flush() && out_removing.Flush();
	return result;
}

// Clear console window on multiple platforms
void Navigator::Clear()
{
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}
