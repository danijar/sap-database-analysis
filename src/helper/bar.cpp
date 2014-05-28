#include "helper/bar.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace std::chrono;
***REMOVED***
***REMOVED***
// Constructor
Bar::Bar(string Label, size_t Max, size_t Width) : label(Label), max(Max), width(Width), current(0), redrawed(0), active(true)
{
	// Validate parameters
	if (Max < 1)
		throw exception("Maximum must be greater or equal to one.");
***REMOVED***
	// Measure execution time
	start = high_resolution_clock::now();
***REMOVED***
	// Draw initial state
	Draw();
}
***REMOVED***
// Increment progress state
bool Bar::Increment(int Step)
{
	// If in progress increment state
	if (current < max && active) {
		current += Step;
		if (current > max)
			current = max;
***REMOVED***
		// Draw if necessary
		if (current - redrawed > max / width - 1) {
			redrawed = current;
			Draw();
		}
	}
	// Else finish up
	else {
		Finish();
	}
***REMOVED***
	// Return state
	return active;
}
***REMOVED***
// Get current state
size_t Bar::Current()
{
	return current;
}
***REMOVED***
// Change maximum and adjust current position
void Bar::Resize(size_t Remaining)
{
	// Find current progress
	double progress = (double)current / (double)max;
***REMOVED***
	// Update maximum
	max = current + Remaining;
***REMOVED***
	// Adjust current to keep progress
	current = size_t(max * progress + 0.5);
}
***REMOVED***
// Redraw and add final line break
void Bar::Finish(bool Success)
{
	// Calculate execution time
	double elapsed = 0.1 * (duration_cast<chrono::milliseconds>(high_resolution_clock::now() - start).count() / 100);
***REMOVED***
	// Only finish once
	if (!active)
		return;
***REMOVED***
	// Fill up progress
	if (Success)
		current = max;
***REMOVED***
	// Redraw and add final line break
	Draw();
	auto format = cout.flags();
	cout << " ";
	cout << setw(7) << setprecision(1) << fixed << elapsed << "s" << endl;
	cout.flags(format);
***REMOVED***
	// Disable bar
	active = false;
}
***REMOVED***
// Print current state of progress bar to console
void Bar::Draw()
{
	// Only draw when line is still active
	if (!active)
		return;
***REMOVED***
	// Calculate progress
	size_t percent = 100 * current / max;
***REMOVED***
	// Reset cursor
	cout << "\r";
***REMOVED***
	// Draw label and padd if neccessary
	if (label.length())
		cout << label << " ";
	size_t padding = 62 - width;
	if (padding > label.length())
		for (size_t i = 0; i < padding - label.length(); ++i)
			cout << " ";
***REMOVED***
	// Draw progress bar
	cout << (percent < 100 ? percent < 10 ? "  " : " " : "") << percent << "% ";
	cout << "[";
	for (int i = 0; i < width; ++i)
		cout << (i < width * percent / 100 ? "=" : " ");
	cout << "]";
	cout.flush();
}
