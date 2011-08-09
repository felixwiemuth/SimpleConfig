/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Config.h"

using namespace std;

Config::Config(const char* path, bool binary, const char seperator) : seperator(seperator)
{
    change_file(path, binary);
}

Config::~Config()
{
    set_status(READY); //close file if necessary
}

void Config::set_binary(bool b)
{
    if (binary != b)
    {
        binary = b;
        set_status(READY); //file must be reopened in the other mode if it was opened before
    }
}

void Config::change_file(const char* path, bool binary)
{
    set_status(READY); //make sure current file is closed
    this->path = path;
    set_binary(binary);
}

bool Config::set_status(Status s)
{
    if (s != status) //check if 's' is not already set
    {
        file.close(); //if the status changed the file has to be either closed or closed and reopened
        if (s != READY) //'s == LOAD || SAVE' so reopen
        {
            if (s == LOAD)
            {
                if (binary)
                    file.open(path, ios::in | ios::binary);
                else
                    file.open(path, ios::in);
            }
            else // s == SAVE
            {
                if (binary)
                    file.open(path, ios::out | ios::trunc | ios::binary);
                else
                    file.open(path, ios::out | ios::trunc);
            }
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
        if (status == READY)
            return true;
        if (!file)
        {
            set_status(READY);
            return false;
        }
    }
    return true;
}
