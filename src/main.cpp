#include "input.h"
***REMOVED***
#include <iostream>
***REMOVED***
using namespace std;
***REMOVED***
int main()
{
	// Load and cache input data
	Input input;
	if (input.Saved())
		input.Load();
	else {
		input.Fetch("HANA", "***REMOVED***", "***REMOVED***", true);
		if (input.ids.size())
			input.Save();
	}
***REMOVED***
	// Show small set of input data
	size_t tables = input.ids.size();
	for (size_t i = 1000; i < min(tables, 1010); ++i) {
		for (size_t j = 0; j < min(tables, 10); ++j) {
			cout << input.names[i] << " " << input.names[j];
			if (input.ratios[i].find(j) != input.ratios[i].end())
				cout << " " << input.ratios[i][j];
			if (input.ratios[j].find(i) != input.ratios[j].end())
				cout << " " << input.ratios[i][j];
			cout << endl;
		}
		cout << endl;
	}
***REMOVED***
	// Find superparents
	// ...
***REMOVED***
	// Hold console open
	cin.get();
}
