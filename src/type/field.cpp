#include "field.h"


// Equality operator
bool Field::operator==(const Field &other) const {
	return name == other.name;
}

// Serializer for query field type
Serialize &operator<<(Serialize &serialize, const Field &field)
{
	serialize << field.name << field.roll << field.domain << field.position;
	return serialize;
}

// Deserializer for query field type
Deserialize &operator>>(Deserialize &deserialize, Field &field)
{
	deserialize >> field.name >> field.roll >> field.domain >> field.position;
	return deserialize;
}
