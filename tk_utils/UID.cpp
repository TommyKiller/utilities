#include "UID.h"

tk_utils::UID::UID(const char* key)
{
    static int id = 0;
    _uid = key + id++;
}

tk_utils::UID::UID(const char* key, int id)
{
    _uid = key + id;
}

std::string tk_utils::UID::toString() const
{
    return _uid;
}

bool tk_utils::UID::operator==(const UID& other) const
{
    return _uid == other._uid;
}

bool tk_utils::UID::operator!=(const UID& other) const
{
    return !(*this == other);
}
