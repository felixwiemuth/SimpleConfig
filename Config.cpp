#include "Config.h"

using namespace std;

Config::Config(const char* path, const char seperator) : path(path), seperator(seperator), status(READY)
{
}

Config::~Config()
{
    set_status(READY); //close file if necessary
}

void Config::set_save_mode_formatted()
{
    binary = false;
}

void Config::set_save_mode_binary()
{
    binary = true;
}

bool Config::set_status(Status s)
{
    if (s != status) //check if 's' is not already set
    {
        file.close(); //if the status changed the file has to be either closed or closed and reopened
        if (s != READY) //'s == LOAD || SAVE' so reopen
        {
            if (s == LOAD)
                file.open(path, ios::in);
            else // s == SAVE
                file.open(path, ios::out | ios::trunc);
            //check if valid
            if (!file || !file.is_open())
            {
                status = READY;
                return false;
            }
            file.clear(); //reset status flags
        }
        status = s; //update status flag
    }
    else
    {
        if (!file)
        {
            status = READY;
            return false;
        }
    }
    return true;
}
