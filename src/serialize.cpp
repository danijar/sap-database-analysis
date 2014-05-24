#include "serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
Serialize::Serialize(std::string Path) : stream(Path.c_str(), ios::out | ios::binary)
{
	if (!stream.is_open() || !stream.good())
		throw exception("Could not open file for writing.");
}
***REMOVED***
Serialize::~Serialize()
{
	stream.close();
}
***REMOVED***
Serialize &Serialize::operator<<(size_t Value)
{
	const size_t length = sizeof(size_t);
***REMOVED***
	// Convert and write
	char data[length];
	memcpy(data, &Value, length);
	stream.write(data, length);
***REMOVED***
	// Allow operator chaining
	return *this;
}
***REMOVED***
Serialize &Serialize::operator<<(float Value)
{
	const size_t length = sizeof(float);
***REMOVED***
	// Convert and write
	char data[length];
	memcpy(data, &Value, length);
	stream.write(data, length);
***REMOVED***
	// Allow operator chaining
	return *this;
}
***REMOVED***
Serialize &Serialize::operator<<(std::string Value)
{
	// First write string length
	*this << Value.length();
***REMOVED***
	// Then the the actual characters
	stream.write(Value.c_str(), Value.length());
***REMOVED***
	// Allow operator chaining
	return *this;
}
***REMOVED***
***REMOVED***
Deserialize::Deserialize(std::string Path) : stream(Path.c_str(), ios::in | ios::binary)
{
	if (!stream.is_open() || !stream.good())
		throw exception("Could not open file for reading.");
}
***REMOVED***
Deserialize::~Deserialize()
{
	stream.close();
}
***REMOVED***
***REMOVED***
Deserialize &Deserialize::operator>>(size_t &Value)
{
	const size_t length = sizeof(size_t);
***REMOVED***
	// Read from stream
	char data[length];
	stream.read(data, length);
***REMOVED***
	// Convert type
	memcpy(&Value, data, length);
***REMOVED***
	return *this;
}
***REMOVED***
Deserialize &Deserialize::operator>>(float &Value)
{
	const size_t length = sizeof(float);
***REMOVED***
	// Read from stream
	char data[length];
	stream.read(data, length);
***REMOVED***
	// Convert type
	memcpy(&Value, data, length);
***REMOVED***
	return *this;
}
***REMOVED***
Deserialize &Deserialize::operator>>(string &Value)
{
	// String length is stored before characters
	size_t length;
	*this >> length;
***REMOVED***
	// Read from stream
	char *data = new char[length + 1];
	stream.read(data, length);
	data[length] = '\0';
***REMOVED***
	// Convert type
	Value = string(data);
	delete[] data;
***REMOVED***
	return *this;
}
