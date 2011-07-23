#include <iostream>

#include "Config.h"

using namespace std;

//Example of load AND save function (as class method)
class myClass
{
    private:
        //Config object
        Config config;
        //myData
        int myIval;
        bool myBval;
        std::string mySval;

    public:
        myClass() : config("settings.conf")
        {
            load_save();
        }
        ~myClass()
        {
            load_save(true);
        }
        void load_save(bool save=false)
        {
            config.load_save(myIval, save);
            config.load_save(myBval, save);
            config.load_save(mySval, save);
        }
        void print()
        {
            cout << "myIval: " << myIval << "\nmySval: " << mySval << endl << "myBval: ";
            if (myBval)
                cout << "TRUE";
            else
                cout << "FALSE";
            cout << std::endl;
        }
};


int main()
{
    //Creat object of type 'myClass' to demonstrate saving
    myClass test; //save at destruction
    test.print();

    return 0;
}
