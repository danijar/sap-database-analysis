#include "helper/jsonize.h"
using namespace std;
***REMOVED***
***REMOVED***
Jsonize::Jsonize(std::string Path) : path(Path)
{
***REMOVED***
}
***REMOVED***
Jsonize::~Jsonize()
{
	// Write to file
	if (!flushed) {
		Flush();
		stream.flush();
	}
}
***REMOVED***
Jsonize &Jsonize::operator<<(const std::string &Value)
{
	stream << "\"" << Value << "\"";
	return *this;
}
***REMOVED***
bool Jsonize::Flush()
{
	ofstream file(path, ios_base::out);
	if (file.bad() || !file.is_open()) {
		cout << "Could not open file \"" << path << "\" to write." << endl;
		return false;
	}
***REMOVED***
	file << stream.rdbuf();
	file.close();
	flushed = true;
	return true;
}
