#ifndef UID_H
#define UID_H
#pragma once

// Standard Headers
#include <string>

// Define Namespace
namespace utils
{
	class UID
	{
	public:
		UID(const char* key);

		bool operator==(const UID& other) const;
		bool operator!=(const UID& other) const;
		std::string get() const;

	private:
		std::string _id;
	};
} // namespace utils

#endif // !UID_H
