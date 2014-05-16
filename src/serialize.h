#pragma once
***REMOVED***
#include <string>
#include <fstream>
***REMOVED***
***REMOVED***
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
class Deserialize {
public:
	Deserialize(std::string Path);
	~Deserialize();
	size_t GetSizeT();
	float GetFloat();
	std::string GetString();
private:
	std::ifstream stream;
};
