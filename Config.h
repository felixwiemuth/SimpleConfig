/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "Config_templates.h"

#include <fstream>
#include <sstream>

class Config
{
    public:
        Config(const char* path="", bool binary=false, const char seperator='\n');
        ~Config();
    private:
        const char* path; //path to config file
        const char seperator; //character to seperate entries in formatted mode
        std::fstream file; //file stream that is used to load and save
        bool binary; //'false': content of variables (operator '>>' must be implemented by the type) are written formatted into the file -- 'true': memory fields are written to file directly -- Note: to load correctly, the mode has to be set the way it was when saving!
        enum Status {READY, LOAD, SAVE} status; // READY = waiting(file closed) LOAD = loading (file opened) SAVE = saving (file opened)
        struct Failure {enum Type {NONE, FILE_OPEN_FAIL, FILE_EOF} type;} failure;
    public:
        void set_binary(bool b=true); //set save/load mode to binary('true') or formatted('false')
        void change_file(const char* path, bool binary=false); //change current file to load/save to 'path'
        Failure::Type get_failure(); //return type of last failure

        template<typename T>
        bool load_save(T& data, bool save=false) //TODO specialize for 'binary==true'
        {
            if (save)
            {
                if (!set_status(SAVE))
                    return false;
                if (binary)
                {
                    file.write((char*)&data, sizeof(data));
                }
                else
                {
                    file << data << seperator;
                }
            }
            else //load
            {
                if (!set_status(LOAD))
                    return false;
                if (binary)
                {
                    file.read((char*)&data, sizeof(data));
                }
                else
                {
                    std::string in;
                    if (!std::getline(file, in, seperator))
                        return false;
                    if (!extract(in, data))
                        return false;
                }
            }
        }
    private:
        bool set_status(Status s); //set the status of the filestream or check if file stillt is 'good()' if the chosen status is already set
};

#endif // CONFIG_H_INCLUDED
