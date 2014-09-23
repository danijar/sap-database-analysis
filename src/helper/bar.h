#pragma once
#include <string>
#include <chrono>


/*
 * Text based progress bar for the console.
 */
class Bar
{
public:
	Bar(std::string Label, size_t Max = 100, size_t Width = 40);
	~Bar();
	void operator+=(int Steps);
	void operator++(int);
	operator size_t() const;
	void Resize(size_t Remaining);
	void Finish(bool Success = true);

	static bool Output;

private:
	void Draw();

	std::string label;
	size_t max;
	const size_t width;
	size_t current, redrawed;
	bool active;
	std::chrono::high_resolution_clock::time_point start;
};
