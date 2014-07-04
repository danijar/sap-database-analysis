#pragma once
#include <functional>
#include "field.h"
***REMOVED***
***REMOVED***
// Type traits
namespace std {
	template <>
	struct hash<Field>
	{
		size_t operator()(const Field &f) const {
			using std::hash;
			return (hash<string>()(f.name)
				^ ((hash<string>()(f.roll) << 1) >> 1)
				^ ((hash<string>()(f.domain) << 1) >> 1)
				^ ((hash<size_t>()(f.position) << 1) >> 1));
		}
	};
}
