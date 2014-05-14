#include <string>
#include <chrono>
***REMOVED***
/*
 * Text based progress bar for the console.
 */
class Bar
{
public:
	Bar(std::string Label, size_t Max = 100, size_t Width = 48);
	bool Increment(int Step = 1);
	size_t Current();
	void Finish(bool Success = true);
private:
	void Draw();
	std::string label;
	const size_t max, width;
	size_t current;
	bool active;
	std::chrono::high_resolution_clock::time_point start;
};
