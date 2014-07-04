#pragma once
#include <string>
#include "helper/serialize.h"
***REMOVED***
***REMOVED***
// Struct for the ratio rows
struct Ratio {
	std::string parent, child;
	float parentratio, childratio;
};
***REMOVED***
// Serialization support
Serialize &operator<<(Serialize &serialize, const Ratio &ratio);
Deserialize &operator>>(Deserialize &deserialize, Ratio &ratio);
