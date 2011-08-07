/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef CONFIG_TEMPLATES_H_INCLUDED
#define CONFIG_TEMPLATES_H_INCLUDED

#include <string>
#include <sstream>

template <typename T>
bool extract(std::string& in, T& dest)
{
    std::stringstream sstr(in);
    if (! (sstr >> dest))
        return false;
    return true;
}

template <>
inline bool extract(std::string& in, std::string& dest)
{
    dest = in;
    return true;
}

#endif // CONFIG_TEMPLATES_H_INCLUDED
