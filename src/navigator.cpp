#include "navigator.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "queries.h"
using namespace std;
***REMOVED***
// Constructor
Navigator::Navigator(Input &Input, unordered_set<size_t> &Heads) : input(Input), heads(Heads)
{
	Clear();
	List();
***REMOVED***
	for (;;) {
		// Read user input
		cout << endl << "> ";
		string command;
		cin >> command;
		cout << endl;
***REMOVED***
		// One table up
		if (command == "up") {
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
				unordered_set<string> fields = Queries::Schema(input.names[path.back()]);
				for (auto i : fields)
					cout << i << " ";
				cout << endl;
			} else {
				cout << "Select a table first." << endl;
			}
		}
***REMOVED***
		// List whole list of children
		else if (command == "more") {
			Clear();
			//Read the limit from command line
			cout << "Limit?\n>";
			string limit; 
			cin >> limit;
			List( atoi(limit.c_str()) );
		}
***REMOVED***
		// List a diff of two tables
		else if (command == "diff"){
			cout << "Tables?\n>";
			string table_a, table_b;
			cin >> table_a >> table_b;
			Diff(table_a, table_b);
		}
***REMOVED***
		// Exit navigator
		else if (command == "exit" || command == "quit") {
			Clear();
			return;
		}
***REMOVED***
		// Show available commands
		else if (command == "help") {
			cout << "To navigate to a table, enter its name." << endl;
			cout << "up"     << "\t" << "Go back to the table you saw before." << endl;
			cout << "root"   << "\t" << "Go to the root level that lists all table heads." << endl;
			cout << "scheme" << "\t" << "List column scheme of the current table. Needs connection to database." << endl;
			cout << "more"   << "\t" << "List all children of the current table." << endl;
			cout << "diff"	 << "\t" << "Show changes between two tables";
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
	auto i = input.ids.find(Name);
	
	// Name doesn't match
	if (i == input.ids.end())
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
	string parent;
	vector<Child> children;
***REMOVED***
	// On root level list head tables
	if (!path.size()) {
		parent = "Head tables";
		for (auto i = heads.begin(); i != heads.end(); ++i) {
			Child child;
			child.Name = input.names[*i];
			child.Children = Children(*i);
			child.Ratio = -1;
			children.push_back(child);
		}
***REMOVED***
		// Sort by number of children
		if (Reverse)
			sort(children.begin(), children.end(), [](const Child &A, const Child &B) { return A.Children < B.Children; });
		else	
			sort(children.begin(), children.end(), [](const Child &A, const Child &B) { return A.Children > B.Children; });
	}
***REMOVED***
	// For tables list their children
	else {
		size_t id = path.back();
		parent = input.names[id];
		if (input.ratios.find(id) != input.ratios.end()) {
			for (auto i = input.ratios[id].begin(); i != input.ratios[id].end(); ++i) {
				Child child;
				child.Name = input.names[i->first];
				child.Children = Children(i->first);
				child.Ratio = Ratio(id, i->first);
				children.push_back(child);
			}
		}
***REMOVED***
		// Sort by ratio to parent
		if (Limit >= 0)
			sort(children.begin(), children.end(), [](const Child &A, const Child &B) { return A.Ratio > B.Ratio; });
		else
			sort(children.begin(), children.end(), [](const Child &A, const Child &B) { return A.Ratio < B.Ratio; });
	}
***REMOVED***
	// Print children
	Table(parent, children, Limit);
}
***REMOVED***
// Get ratio between to tables
float Navigator::Ratio(size_t From, size_t To)
{
	// Check for connection from parent table
	auto i = input.ratios.find(From);
	if (i == input.ratios.end())
		return -1;
***REMOVED***
	// Check for connection to child
	auto j = i->second.find(To);
	if (j == i->second.end())
		return -1;
***REMOVED***
	return j->second;
}
***REMOVED***
// Get number of children of a table
size_t Navigator::Children(size_t Id)
{
	// No children
	if (input.ratios.find(Id) == input.ratios.end())
		return 0;
***REMOVED***
	// Get number of children
	return input.ratios[Id].size();
}
***REMOVED***
// Print out the passed children as table
void Navigator::Table(string Parent, vector<Child> &Children, size_t Limit)
{
	// Store default formatting
	auto format = cout.flags();
***REMOVED***
	// Headline
	cout << Parent << endl;
	for (size_t i = 0; i < Parent.length(); ++i)
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
	cout << "Found " << Children.size() << (Children.size() > 1 ? " tables." : " table.") << endl << endl;
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
	for (int i = 0; i < width_ratio; ++i)
		cout << "-";
	cout << " ";
	for (int i = 0; i < width_children; ++i)
		cout << "-";
	cout << " ";
	for (int i = 0; i < width_name; ++i)
		cout << "-";
	cout << endl;
***REMOVED***
	// Loop up to table limit
	for (int i = 0; i < Limit || !Limit; ++i) {
		// Return if no more rows
		if (i > Children.size() - 1)
			return;
***REMOVED***
		// Print current row
		Child child = Children[i];
		if (child.Ratio > 0) {
			cout << setw(width_ratio) << right << setprecision(2) << fixed << child.Ratio << " ";
		} else {
			for (int j = 0; j < width_ratio - 1; ++j)
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
***REMOVED***
void Navigator::Diff(string TableA, string TableB){
	Clear();
***REMOVED***
	// Find nodes for diff to
	auto tableAId = input.ids.find(TableA);
	auto tableBId = input.ids.find(TableB);
***REMOVED***
	// If tables weren't found
	if (tableAId == input.ids.end() || tableBId == input.ids.end()) {
		cout << "Error:\tOne or both of the tables were not found" << endl;
		return;
	}
	// Get vector from first table as in missing
	unordered_set<string> parent_set = Queries::Schema(input.names[tableAId->second]); 
	
	// Get the new vector as new 
	unordered_set<string> child_set = Queries::Schema(input.names[tableBId->second]);
	if (parent_set.empty() || child_set.empty()) {
		cout << "Error:\tCould not retrieve elements from DD03L" << endl;
		return;
	}
	cout << "Changes from " << TableA << " to " << TableB <<  ":" << endl;
	
	vector<string> parent_vector;
	vector<string> child_vector;
	vector<string> common_vector;
	
	for each (auto field in parent_set)	{
		// If field is in both push it to common
		if (child_set.find(field) != child_set.end()){
			common_vector.push_back(field);
			child_set.erase(field);
		} else {
			parent_vector.push_back(field);
		}
	}
	// Now in child set are only the new fields left
	for each (auto field in child_set) {
		child_vector.push_back(field);
	}
***REMOVED***
	int width_common, width_parent, width_child;
	width_common = width_parent = width_child = 20;
***REMOVED***
	// Print the header
	cout << setw(width_common) << left << "Common" << " ";
	cout << setw(width_parent) << left << "Missing" << " ";
	cout << setw(width_child) << left << "New" << " " << endl;
***REMOVED***
	for (size_t i = 0; i < width_common; i++)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_parent; i++)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_child; i++)
		cout << "-";
	cout << " " << endl;
***REMOVED***
	for (size_t i = 0; i < common_vector.size() || i < child_vector.size() || i < parent_vector.size(); i++) {
		cout << setw(width_common) << right << ((i < common_vector.size()) ? common_vector[i] : " ") << " ";
		cout << setw(width_parent) << right << ((i < parent_vector.size()) ? parent_vector[i] : " ") << " ";
		cout << setw(width_child) << right << ((i < child_vector.size()) ? child_vector[i] : " ") << " " << endl;
	}
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
