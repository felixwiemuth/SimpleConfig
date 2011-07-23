#ifndef TEMPLATES_H_INCLUDED
#define TEMPLATES_H_INCLUDED

#include "Config.h"

#include <sstream>
#include <fstream>

template <typename T> std::ostream& operator<<(Config& c, T& data)
{
    if (!c.file.is_open())
        return false;
    c.file << data << c.seperator;
    c.file.close();
}

#endif // TEMPLATES_H_INCLUDED
