#include "serialize.h"
***REMOVED***
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
size_t Deserialize::GetSizeT()
{
	const size_t length = sizeof(size_t);
***REMOVED***
	// Read from stream
	char data[length];
	stream.read(data, length);
***REMOVED***
	// Convert type
	size_t result;
	memcpy(&result, data, length);
	return result;
}
***REMOVED***
float Deserialize::GetFloat()
{
	const size_t length = sizeof(float);
***REMOVED***
	// Read from stream
	char data[length];
	stream.read(data, length);
***REMOVED***
	// Convert type
	float result;
	memcpy(&result, data, length);
	return result;
}
***REMOVED***
std::string Deserialize::GetString()
{
	// String length is stored before characters
	size_t length = GetSizeT();
***REMOVED***
	// Read from stream
	char *value = new char[length + 1];
	stream.read(value, length);
	value[length] = '\0';
***REMOVED***
	// Convert type
	string result(value);
	delete[] value;
	return result;
}
