#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
Serialize::Serialize(std::string Path) : stream(Path.c_str(), ios::out | ios::binary)
{
***REMOVED***
}
***REMOVED***
Serialize::~Serialize()
{
	stream.close();
}
***REMOVED***
bool Serialize::Good()
{
	return stream.is_open() && stream.good();
}
***REMOVED***
Serialize &Serialize::operator<<(const bool Value)
{
	// Convert and write
	char data[1] = { Value ? 1 : 0 };
	stream.write(data, 1);
***REMOVED***
	// Allow operator chaining
	return *this;
}
***REMOVED***
Serialize &Serialize::operator<<(const size_t Value)
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
Serialize &Serialize::operator<<(const float Value)
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
Serialize &Serialize::operator<<(const std::string Value)
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
***REMOVED***
}
***REMOVED***
Deserialize::~Deserialize()
{
	stream.close();
}
***REMOVED***
bool Deserialize::Good()
{
	return stream.is_open() && stream.good();
}
***REMOVED***
Deserialize &Deserialize::operator>>(bool &Value)
{
	// Read from stream
	char data[1];
	stream.read(data, 1);
***REMOVED***
	// Convert type
	Value = (data[1] ? true : false);
***REMOVED***
	return *this;
}
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
