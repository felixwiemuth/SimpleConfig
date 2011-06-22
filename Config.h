#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <fstream>
#include <sstream>

class Config
{
    public:
        Config(const char* path, const char seperator='\n');
        ~Config();
    public:
        const char* path;
        const char seperator;
        std::fstream file;
        enum Status {READY, LOAD, SAVE} status; // READY = waiting(file closed) LOAD = loading (file opened) SAVE = saving (file opened)
    public:
        bool set_status(Status s);

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
                std::stringbuf in;
                std::stringstream in2;
                while (file.good())
                {
                    file.get(in, seperator);
                    try
                    {
                        std::stringstream in2(in.str());
                        in2 >> data;
                    }
                    catch(std::ios_base::failure&) //error
                    {
                        continue;
                    }
                }
            }
        }
};

#endif // CONFIG_H_INCLUDED
