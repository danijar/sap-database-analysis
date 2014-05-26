#include "helper/charts.h"
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
***REMOVED***
***REMOVED***
namespace Charts {
	// ...
	void Histogram(vector<size_t> &Data, size_t Height, size_t Width)
	{
		// Sort data and store maximum
		sort(Data.begin(), Data.end(), greater<size_t>());
		size_t max = Data.front();
***REMOVED***
		// Restrict dimensions to input data
		Width = min(Width, Data.size());
		Height = min(Height, max);
***REMOVED***
		// Sample for width
		vector<size_t> samples;
		samples.reserve(Width);
		size_t step = Data.size() / Width;
		for (size_t i = 0; i < Width; ++i) {
			// Average over samples
			size_t sum = 0;
			for (size_t j = 0; j < step; ++j)
				sum += Data[i * step + j];
			sum /= step;
***REMOVED***
			// Write to vector
			samples.push_back(sum);
		}
***REMOVED***
		// Top border
		cout << "+";
		for (size_t i = 0; i < Width; ++i)
			cout << "-";
		cout << "+" << endl;
***REMOVED***
		// Draw line by line
		for (size_t y = Height; y > 0; --y) {
			// Left border
			cout << "|";
***REMOVED***
			// Chart bars
			for (size_t x = 0; x < min(samples.size(), size_t(79)); ++x) {
				if (samples[x] * Height / max > y - 1)
					cout << "#";
				else
					cout << " ";
			}
***REMOVED***
			// Right border
			cout << "|" << endl;
		}
***REMOVED***
		// Bottom border
		cout << "+";
		for (size_t i = 0; i < Width; ++i)
			cout << "-";
		cout << "+" << endl;
	}
}
