#include "navigator.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <functional>
#include <cstdlib>
#include "queries.h"
#include "charts.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor
Navigator::Navigator(Hierarchy &Hierarchy) : hierarchy(Hierarchy)
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
				unordered_set<string> fields = Queries::Schema(hierarchy.names[path.back()]);
				for (auto i : fields)
					cout << i << " ";
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
			// Ask for parameters
			cout << "Tables: ";
			string left, right;
			cin >> left >> right;
***REMOVED***
			Clear();
			Difference(left, right);
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
				data.push_back(hierarchy.children[*i].size());
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
		// Show available commands
		else if (command == "help") {
			cout << "To navigate to a table, enter its name." << endl;
			cout << "back"   << "\t" << "Go back to the table you saw before." << endl;
			cout << "root"   << "\t" << "Go to the root level that lists all table heads." << endl;
			cout << "scheme" << "\t" << "List column scheme of the current table. Needs connection to database." << endl;
			cout << "more"   << "\t" << "List all children of the current table." << endl;
			cout << "diff"	 << "\t" << "Show changes between two tables." << endl;
			cout << "histo"  << "\t" << "Draw histogram of children and their number of occurrence." << endl;
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
	string headline = path.size() ? hierarchy.names[id] : "Root";
***REMOVED***
	// Prepare vector of children
	vector<Child> children;
	if (hierarchy.children.find(id) != hierarchy.children.end()) {
		for (auto i = hierarchy.children[id].begin(); i != hierarchy.children[id].end(); ++i) {
			Child child;
			child.Name = hierarchy.names[*i];
			child.Children = Children(*i);
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
	Table(headline, children, Limit);
}
***REMOVED***
// Get ratio between to tables
float Navigator::Ratio(size_t From, size_t To)
{
	// Check for connection from parent table
	auto i = hierarchy.ratios.find(From);
	if (i == hierarchy.ratios.end())
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
	// Find node of interest
	auto i = hierarchy.children.find(Id);
***REMOVED***
	// No children
	if (i == hierarchy.children.end())
		return 0;
***REMOVED***
	// Get number of children
	return i->second.size();
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
	cout << "Found " << Children.size() << (Children.size() > 1 ? " children." : " child.") << endl << endl;
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
***REMOVED***
void Navigator::Difference(string Left, string Right)
{
	// Validate hierarchy
	auto i = hierarchy.ids.find(Left);
	auto j = hierarchy.ids.find(Right);
	if (i == hierarchy.ids.end()) {
		cout << "'" << Left << "' is no valid table name." << endl;
		return;
	}
	if (j == hierarchy.ids.end()) {
		cout << "'" << Right << "' is no valid table name." << endl;
		return;
	}
***REMOVED***
	// Get table shemes
	auto parent = Queries::Schema(Left);
	auto child = Queries::Schema(Right);
	if (parent.empty() || child.empty()) {
		cout << "Could not retrieve table schemes." << endl;
		return;
	}
	
	// Find distinct and common fields
	vector<string> commons, missings, news;
	for (auto i = parent.begin(); i != parent.end(); ++i)
		if (child.find(*i) == child.end())
			missings.push_back(*i);
		else
			commons.push_back(*i);
	for (auto i = child.begin(); i != child.end(); ++i)
		if (parent.find(*i) == parent.end())
			news.push_back(*i);
***REMOVED***
	// Find column widths
	size_t width_commons = 6, width_missings = 7, width_news = 3;
	for (auto i = commons.begin(); i != commons.end(); ++i)
		if (i->length() > width_commons)
			width_commons = i->length();
	for (auto i = missings.begin(); i != missings.end(); ++i)
		if (i->length() > width_missings)
			width_missings = i->length();
	for (auto i = news.begin(); i != news.end(); ++i)
		if (i->length() > width_news)
			width_news = i->length();
***REMOVED***
	// Store default formatting
	auto format = cout.flags();
***REMOVED***
***REMOVED***
	// Draw headline
	cout << "Changes between " << Left << " to " << Right << endl;
	for (size_t i = 0; i < 19 + Left.length() + Right.length(); ++i)
		cout << "=";
	cout << endl << endl;
***REMOVED***
	// Draw table captions
	cout << setw(width_commons) << "Common ";
	cout << setw(width_missings) << "Missing ";
	cout << setw(width_news) << "New " << endl;
	for (size_t i = 0; i < width_commons; i++)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_missings; i++)
		cout << "-";
	cout << " ";
	for (size_t i = 0; i < width_news; i++)
		cout << "-";
	cout << " " << endl;
***REMOVED***
	// Draw table rows
	for (size_t i = 0; i < commons.size() || i < news.size() || i < missings.size(); i++) {
		cout << setw(width_commons) << ((i < commons.size()) ? commons[i] : " ") << " ";
		cout << setw(width_missings) << ((i < missings.size()) ? missings[i] : " ") << " ";
		cout << setw(width_news)  << ((i < news.size()) ? news[i] : " ") << " ";
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
