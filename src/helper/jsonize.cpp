#include "helper/jsonize.h"
using namespace std;


Jsonize::Jsonize(std::string Path) : path(Path)
{

}

Jsonize::~Jsonize()
{
	// Write to file
	if (!flushed) {
		Flush();
		stream.flush();
	}
}

Jsonize &Jsonize::operator << (const bool &Value)
{
	stream << (Value ? "true" : "false");
	return *this;
}

Jsonize &Jsonize::operator<<(const std::string &Value)
{
	stream << "\"" << Value << "\"";
	return *this;
}

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

	return true;
}

string Jsonize::Dissolve()
{
	// Prevent destructor from saving as file
	flushed = true;

	// Get string and empty stream
	string content = stream.str();
	stream.clear();
	
	// Return placeholder since this is currently not working
	return "{}";

	return content;
}
