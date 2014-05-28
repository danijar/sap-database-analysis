#include "navigator.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <functional>
#include <cstdlib>
#include "helper/queries.h"
#include "helper/charts.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor
Navigator::Navigator(Hierarchy &Hierarchy, Structures &Structures) : hierarchy(Hierarchy), structures(Structures)
{
	Clear();
	List();
***REMOVED***
	for (;;) {
		// Read user hierarchy
		cout << endl << "> ";
		string command;
		cin >> command;
		cout << endl;
***REMOVED***
		// One table up
		if (command == "back") {
			if (Up()) {
				Clear();
				List();
			} else {
				cout << "No previous table to go to." << endl;
			}
		}
***REMOVED***
		// Root level
		else if (command == "root") {
			path.clear();
			Clear();
			List();
		}
***REMOVED***
		// List scheme
		else if (command == "scheme") {
			if (path.size()) {
				vector<Queries::Field> fields = Queries::Fields(hierarchy.names[path.back()]);
				for (auto i : fields)
					cout << i.name << " ";
				cout << endl;
			} else {
				cout << "Select a table first." << endl;
			}
		}
***REMOVED***
		// List whole children
		else if (command == "more") {
			// Ask for parameters
			int limit;
			cout << "Limit: ";
			cin >> limit;
***REMOVED***
			Clear();
			List(abs(limit), limit < 0);
		}
***REMOVED***
		// List a difference between two table schemes
		else if (command == "diff") {
			// Ask for parameter
			cout << "Child: ";
			string table;
			cin >> table;
			cout << endl;
***REMOVED***
			Difference(table);
		}
***REMOVED***
		// Exit navigator
		else if (command == "exit" || command == "quit") {
			Clear();
			return;
		}
***REMOVED***
		// Draw histogram of children and their number of occurrence.
		else if (command == "histo") {
			// Ask for parameters
			size_t limit;
			cout << "Limit: ";
			cin >> limit;
			cout << endl;
***REMOVED***
			// Fetch and sort children
			size_t id = path.size() ? path.back() : 0;
			vector<size_t> data;
			data.reserve(hierarchy.children[id].size());
			for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i)
				data.push_back(hierarchy.amounts[*i]);
			sort(data.begin(), data.end(), greater<size_t>());
***REMOVED***
			// Apply limit and plot
			if (limit > data.size() - 1) {
				limit = 0;
				cout << "Adjusted limit to not exceed number of children." << endl << endl;
			}
			if (limit)
				data.resize(limit);
			Charts::Histogram(data);
		}
***REMOVED***
		else if (command == "csv") {
			// Fetch and children and amounts
			size_t id = path.size() ? path.back() : 0;
			vector<pair<string, size_t>> data;
			data.reserve(hierarchy.children[id].size());
			for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i)
				data.push_back(make_pair(hierarchy.names[*i], hierarchy.amounts[*i]));
***REMOVED***
			// Sort data
			sort(data.begin(), data.end(), [](pair<string, size_t> l, pair<string, size_t> r) { return l.second < r.second; });
***REMOVED***
			// Table without special chars as file name
			string name = hierarchy.names[id];
			name.erase(remove(name.begin(), name.end(), '<'), name.end());
			name.erase(remove(name.begin(), name.end(), '>'), name.end());
			name += ".csv";
			ofstream out("data/" + name);
***REMOVED***
			// Save to disk
			out << "sep=;" << endl;
			out << "Table;Amount" << endl;
			for (auto i = data.begin(); i != data.end(); ++i)
				out << i->first << ";" << i->second << endl;
			out.close();
***REMOVED***
			// Output
			cout << "Wrote table names and their amount of children to " << name << "." << endl;
		}
***REMOVED***
		// Show available commands
		else if (command == "help") {
			cout << "To navigate to a table, enter its name." << endl;
			cout << "back"   << "\t" << "Go back to the table you saw before." << endl;
			cout << "root"   << "\t" << "Go to the root level that lists all table heads." << endl;
			cout << "scheme" << "\t" << "List column scheme of the current table. Needs connection to database." << endl;
			cout << "more"   << "\t" << "List all children of the current table." << endl;
			cout << "diff"	 << "\t" << "Show changes from current table to a child." << endl;
			cout << "histo"  << "\t" << "Draw histogram of children and their number of occurrence." << endl;
			cout << "csv"    << "\t" << "Write CSV file of current children and their number of children." << endl;
			cout << "exit"   << "\t" << "Exit the navigator. Synonyms: quit." << endl;
		}
***REMOVED***
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
***REMOVED***
// Go down one level in the hierarchie
bool Navigator::Go(string Name)
{
	// Find node navigating to
	auto i = hierarchy.ids.find(Name);
	
	// Name doesn't match
	if (i == hierarchy.ids.end())
		return false;
***REMOVED***
	// Add to path
	path.push_back(i->second);
	return true;
}
***REMOVED***
// Get one level up in the hierarchie
bool Navigator::Up()
{
	// If already on the highest level
	if (!path.size())
		return false;
***REMOVED***
	// Remove last from path
	size_t node = path.back();
	path.pop_back();
	return true;
}
***REMOVED***
// List children of current table
void Navigator::List(size_t Limit, bool Reverse)
{
	// Name and id of current table
	size_t id = path.size() ? path.back() : 0;
***REMOVED***
	// Prepare vector of children
	vector<Child> children;
	if (id < hierarchy.children.size()) {
		for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i) {
			Child child;
			child.Name = hierarchy.names[*i];
			child.Children = hierarchy.children[*i].size();
			child.Ratio = Ratio(id, *i);
			children.push_back(child);
		}
	}
***REMOVED***
	// Sort by ratio to parent, on root level by number of children
	if (path.size()) {
		auto comparator = [Reverse](const Child &A, const Child &B) { return A.Ratio > B.Ratio != Reverse; };
		sort(children.begin(), children.end(), comparator);
	} else {
		auto comparator = [Reverse](const Child &A, const Child &B) { return A.Children > B.Children != Reverse; };
		sort(children.begin(), children.end(), comparator);
	}
	
	// Print children
	Table(id, children, Limit);
}
***REMOVED***
// Get ratio between to tables
float Navigator::Ratio(size_t From, size_t To)
{
	// Check for table
	if (From > hierarchy.ratios.size() - 1)
		return -1;
***REMOVED***
	// Check for connection to child
	auto j = hierarchy.ratios[From].find(To);
	if (j == hierarchy.ratios[From].end())
		return -1;
***REMOVED***
	return j->second;
}
***REMOVED***
// Print out the passed children as table
void Navigator::Table(size_t Id, vector<Child> &Children, size_t Limit)
{
	// Store default formatting
	auto format = cout.flags();
***REMOVED***
	// Headline
	cout << hierarchy.names[Id] << endl;
	for (size_t i = 0; i < hierarchy.names[Id].length(); ++i)
		cout << "=";
	cout << endl;
***REMOVED***
	// Print message and return if no rows
	if (!Children.size()) {
		cout << "Found no tables." << endl;
		return;
	}
***REMOVED***
	// Show number of rows
	cout << "Found and " << hierarchy.amounts[Id] << " overall and " << Children.size() << (Children.size() > 1 ? " direct children." : " child.") << endl << endl;
***REMOVED***
	// Find column widths
	size_t width_name = 0, width_children = 0, width_ratio = 4;
	for (auto i = Children.begin(); i != Children.end(); ++i) {
		// Name
		if (i->Name.length() > width_name)
			width_name = i->Name.length();
***REMOVED***
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
***REMOVED***
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
***REMOVED***
	// Loop up to table limit
	for (size_t i = 0; i < Limit || !Limit; ++i) {
		// Return if no more rows
		if (i > Children.size() - 1)
			return;
***REMOVED***
		// Print current row
		Child child = Children[i];
		if (child.Ratio > 0) {
			cout << setw(width_ratio) << right << setprecision(2) << fixed << child.Ratio << " ";
		} else {
			for (size_t j = 0; j < width_ratio - 1; ++j)
				cout << " ";
			cout << "- ";
		}
		cout << setw(width_children) << right << child.Children << " ";
		cout << setw(width_name) << left << child.Name << " ";
		cout << endl;
	}
***REMOVED***
	// Print continuation indicator
	cout << "..." << endl;
***REMOVED***
	// Reset formatting options
	cout.flags(format);
}
***REMOVED***
// Show a diff between two tables
void Navigator::Difference(string Table)
{
	// Validate hierarchy
	if (hierarchy.ids.find(Table) == hierarchy.ids.end()) {
		cout << "'" << Table << "' is no valid table name." << endl;
		return;
	}
***REMOVED***
	// Get differences
	size_t id = hierarchy.ids[Table];
	auto differences = structures.Difference(id);
	unordered_set<string> &added = differences.first;
	unordered_set<string> &removed = differences.second;
***REMOVED***
	// Find column widths
	size_t width_added = 5, width_removed = 7;
	for (auto i = added.begin(); i != added.end(); ++i)
		if (i->length() > width_added)
			width_added = i->length();
	for (auto i = removed.begin(); i != removed.end(); ++i)
		if (i->length() > width_removed)
			width_removed = i->length();
***REMOVED***
	// Store default formatting
	auto format = cout.flags();
***REMOVED***
	// Draw headline
	cout << "Changes to " << Table << endl;
	for (size_t i = 0; i < 11 + Table.length(); ++i)
		cout << "=";
	cout << endl << endl;
***REMOVED***
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
***REMOVED***
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
***REMOVED***
	// Reset formatting options
	cout.flags(format);
}
***REMOVED***
// Clear console window on multiple platforms
void Navigator::Clear()
{
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}
