#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "Config_templates.h"

#include <fstream>
#include <sstream>

class Config
{
    public:
        Config(const char* path, const char seperator='\n');
        ~Config();
    private:
        const char* path;
        const char seperator;
        std::fstream file;
        enum Status {READY, LOAD, SAVE} status; // READY = waiting(file closed) LOAD = loading (file opened) SAVE = saving (file opened)
    public:
        template<typename T>
        bool load_save(T& data, bool save=false)
        {
            if (save)
            {
                if (!set_status(SAVE))
                    return false;
                file << data << seperator;
            }
            else //load
            {
                if (!set_status(LOAD))
                    return false;
                std::string in;
                if (!std::getline(file, in, seperator))
                    return false;
                if (!extract(in, data))
                    return false;
            }
        }
    private:
        bool set_status(Status s); //set the status of the filestream or check if file stillt is 'good()' if the chosen status is already set
};

#endif // CONFIG_H_INCLUDED
