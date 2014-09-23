#include "ratio.h"


// Serializer for ratio type
Serialize &operator<<(Serialize &serialize, const Ratio &ratio)
{
	serialize << ratio.parent << ratio.child << ratio.parentratio << ratio.childratio;
	return serialize;
}

// Deserializer for ratio type
Deserialize &operator>>(Deserialize &deserialize, Ratio &ratio)
{
	deserialize >> ratio.parent >> ratio.child >> ratio.parentratio >> ratio.childratio;
	return deserialize;
}
