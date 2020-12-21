#include "UID.h"

utils::UID::UID(const char* key)
{
    static int id = 0;
    _id = key + id++;
}

bool utils::UID::operator==(const UID& other) const
{
    return _id == other._id;
}

bool utils::UID::operator!=(const UID& other) const
{
    return !(*this == other);
}

std::string utils::UID::get() const
{
    return _id;
}
