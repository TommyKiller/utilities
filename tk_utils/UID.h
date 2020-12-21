#ifndef UID_H
#define UID_H
#pragma once

// Standard Headers
#include <string>

// Define Namespace
namespace tk_utils
{
	class UID
	{
	public:
		UID(const char* key);
		UID(const char* key, int id);

		std::string toString() const;

		bool operator==(const UID& other) const;
		bool operator!=(const UID& other) const;

	private:
		std::string _uid;
	};
} // namespace tk_utils

#endif // !UID_H
