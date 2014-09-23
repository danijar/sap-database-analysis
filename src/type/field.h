#pragma once
#include <string>
#include <functional>
#include "helper/serialize.h"


// Struct for the field values
struct Field {
	bool operator==(const Field &other) const;
	std::string name, roll, domain;
	size_t position;
};

// Serialization support
Serialize &operator<<(Serialize &serialize, const Field &field);
Deserialize &operator>>(Deserialize &deserialize, Field &field);

#include "field.tpl"
