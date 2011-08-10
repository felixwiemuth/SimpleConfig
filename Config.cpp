/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#include "Config.h"

using namespace std;

Config::Config(const char* path, bool binary, const char seperator) : seperator(seperator)
{
    failure.type = Failure::NONE;
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

bool Config::check_file()
{
    if (file)
        return true;
    if (file.eof())
        failure.type = Failure::FILE_EOF;
    if (file.fail())
        failure.type = Failure::FILE_FAIL;
    if (file.bad())
        failure.type = Failure::FILE_BAD;
    return false;
}

Config::Failure::Type Config::get_failure()
{
    return failure.type;
}

void Config::clear()
{
    failure.type = Failure::NONE;
}

bool Config::operator()()
{
    if (failure.type == Failure::NONE)
        return true;
    return false;
}

bool Config::operator!()
{
    return !(*this)();
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
            if (!file.is_open())
            {
                status = READY;
                failure.type = Failure::FILE_OPEN_FAIL;
                return false;
            }
            if (!check_file())
                return false;
        }
        status = s; //update status flag
        file.clear(); //reset status flags
    }
    else
    {
        if (status == READY)
            return true;
        if (check_file()) //status is still LOAD or SAVE and file is good
            return true;
        //file not ok => close
        set_status(READY);
        return false;
    }
    return true;
}
