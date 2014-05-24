#pragma once
***REMOVED***
#include <string>
#include <fstream>
***REMOVED***
***REMOVED***
/*
 * Stream to serialize values to disk.
 */
class Serialize {
public:
	Serialize(std::string Path);
	~Serialize();
	Serialize &operator<<(size_t Value);
	Serialize &operator<<(float Value);
	Serialize &operator<<(std::string Value);
private:
	std::ofstream stream;
};
***REMOVED***
***REMOVED***
/*
 * Stream to deserialize values from disk.
 */
class Deserialize {
public:
	Deserialize(std::string Path);
	~Deserialize();
	Deserialize &operator>>(size_t &Value);
	Deserialize &operator>>(float &Value);
	Deserialize &operator>>(std::string &Value);
private:
	std::ifstream stream;
};
