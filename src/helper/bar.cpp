#include "helper/bar.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace std::chrono;
***REMOVED***
***REMOVED***
// Static member
bool Bar::Output = true;
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
// Finish on destruction
Bar::~Bar()
{
	Finish();
}
***REMOVED***
// Increment progress state
void Bar::operator+=(int Steps)
{
	// If in progress, increment state
	if (current < max && active) {
		current += Steps;
		if (current > max)
			current = max;
***REMOVED***
		// Draw if something changed
		bool percentage = 100 * redrawed / max > 100 * current / max;
		bool bars = current - redrawed > max / width - 1;
		if (percentage || bars) {
			redrawed = current;
			Draw();
		}
	} else {
		Finish();
	}
}
***REMOVED***
// Increment progress state by one
void Bar::operator++(int)
{
	*this += 1;
}
***REMOVED***
// Return current state
Bar::operator size_t() const {
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
	// Only finish once
	if (!active)
		return;
	
	// Fill up progress
	if (Success)
		current = max;
***REMOVED***
	if (Output) {
		// Calculate execution time
		double elapsed = 0.1 * (duration_cast<chrono::milliseconds>(high_resolution_clock::now() - start).count() / 100);
***REMOVED***
		// Redraw and add final line break
		Draw();
		auto format = cout.flags();
		cout << " ";
		cout << setw(7) << setprecision(1) << fixed << elapsed << "s" << endl;
		cout.flags(format);
	}
***REMOVED***
	// Disable bar
	active = false;
}
***REMOVED***
// Print current state of progress bar to console
void Bar::Draw()
{
	// Only draw when still active and output enabled
	if (!active || !Output)
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
