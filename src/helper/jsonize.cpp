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
	write_to_file();
	stream.flush();
}
***REMOVED***
***REMOVED***
void Jsonize::write_to_file()
{
	ofstream out_file(path, ios_base::out);
	if (out_file.bad()) {
		cout << "Could not open file" << path << endl;
		return;
	}
	
	out_file << stream.rdbuf();
	out_file.close();
}
***REMOVED***
Jsonize &Jsonize::operator<<(const std::string &Value)
{
	stream << "\"" << Value << "\"";
	return *this;
}
***REMOVED***
***REMOVED***
