#include "helper/serialize.h"
using namespace std;


Serialize::Serialize(std::string Path) : stream(Path.c_str(), ios::out | ios::binary)
{

}

Serialize::~Serialize()
{
	stream.close();
}

bool Serialize::Good()
{
	return stream.is_open() && stream.good();
}

Serialize &Serialize::operator<<(const bool Value)
{
	// Convert and write
	char data[1] = { Value ? 1 : 0 };
	stream.write(data, 1);

	// Allow operator chaining
	return *this;
}

Serialize &Serialize::operator<<(const size_t Value)
{
	const size_t length = sizeof(size_t);

	// Convert and write
	char data[length];
	memcpy(data, &Value, length);
	stream.write(data, length);

	// Allow operator chaining
	return *this;
}

Serialize &Serialize::operator<<(const float Value)
{
	const size_t length = sizeof(float);

	// Convert and write
	char data[length];
	memcpy(data, &Value, length);
	stream.write(data, length);

	// Allow operator chaining
	return *this;
}

Serialize &Serialize::operator<<(const std::string Value)
{
	// First write string length
	*this << Value.length();

	// Then the the actual characters
	stream.write(Value.c_str(), Value.length());

	// Allow operator chaining
	return *this;
}


Deserialize::Deserialize(std::string Path) : stream(Path.c_str(), ios::in | ios::binary)
{

}

Deserialize::~Deserialize()
{
	stream.close();
}

bool Deserialize::Good()
{
	return stream.is_open() && stream.good();
}

Deserialize &Deserialize::operator>>(bool &Value)
{
	// Read from stream
	char data[1];
	stream.read(data, 1);

	// Convert type
	Value = (data[1] ? true : false);

	return *this;
}

Deserialize &Deserialize::operator>>(size_t &Value)
{
	const size_t length = sizeof(size_t);

	// Read from stream
	char data[length];
	stream.read(data, length);

	// Convert type
	memcpy(&Value, data, length);

	return *this;
}

Deserialize &Deserialize::operator>>(float &Value)
{
	const size_t length = sizeof(float);

	// Read from stream
	char data[length];
	stream.read(data, length);

	// Convert type
	memcpy(&Value, data, length);

	return *this;
}

Deserialize &Deserialize::operator>>(string &Value)
{
	// String length is stored before characters
	size_t length;
	*this >> length;

	// Read from stream
	char *data = new char[length + 1];
	stream.read(data, length);
	data[length] = '\0';

	// Convert type
	Value = string(data);
	delete[] data;

	return *this;
}
