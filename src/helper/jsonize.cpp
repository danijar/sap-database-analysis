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
Jsonize &Jsonize::operator << (const bool &Value)
{
	stream << (Value ? "true" : "false");
	return *this;
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
	// Write to file
	ofstream file(path, ios_base::out);
	if (file.bad() || !file.is_open()) {
		cout << "Could not open file \"" << path << "\" to write." << endl;
		return false;
	}
	file << stream.rdbuf();
	file.close();
	
	// Prevent destructor from saving as file
	flushed = true;
***REMOVED***
	return true;
}
***REMOVED***
string Jsonize::Dissolve()
{
	// Prevent destructor from saving as file
	flushed = true;
***REMOVED***
	// Get string and empty stream
	string content = stream.str();
	stream.clear();
	
	// Return placeholder since this is currently not working
	return "{}";
***REMOVED***
	return content;
}
