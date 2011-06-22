#include "Config.h"

using namespace std;

Config::Config(const char* path, const char seperator) : path(path), seperator(seperator), status(READY)
{
}

Config::~Config()
{
    set_status(READY); //close file if necessary
}

bool Config::set_status(Status s)
{
    if (s != status) //check if 's' is not already set
    {
        if (s == READY)
            file.close();
        else
        {
            if (s == LOAD)
                file.open(path, ios::in);
            else // s == SAVE
                file.open(path, ios::out | ios::trunc);
            //check if valid
            if (!file.is_open())
                return false;
            file.clear(); //reset status flags
        }
    }
    else
    {
        if (!file.good())
            return false;
    }
    return true;
}
