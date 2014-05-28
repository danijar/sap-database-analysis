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
		size_t max = 0;
		for (auto i = Data.begin(); i != Data.end(); ++i)
			if (*i > max)
				max = *i;
***REMOVED***
		// Count occurences of all numbers
		vector<size_t> count;
		count.resize(max + 1);
		for (auto i = Data.begin(); i != Data.end(); ++i)
			count[*i]++;
***REMOVED***
		// Restrict dimensions to input data
		Width = min(Width, count.size());
		Height = min(Height, max);
***REMOVED***
		// Sample for width
		vector<size_t> samples;
		samples.reserve(Width);
		size_t step = count.size() / Width;
		for (size_t i = 0; i < Width; ++i) {
			// Average over samples
			size_t sum = 0;
			for (size_t j = 0; j < step; ++j)
				sum += count[i * step + j];
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
