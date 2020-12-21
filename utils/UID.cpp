#include "UID.h"

utils::UID::UID(const char* key)
{
    static int id = 0;
    _id = key + id++;
}

bool utils::UID::operator==(const UID& other)
{
    return _id == other._id;
}

bool utils::UID::operator!=(const UID& other)
{
    return !(*this == other);
}
