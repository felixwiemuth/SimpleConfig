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
            myIval = 11;
            myBval = true;
            mySval = "Hello World!";
            //load_save();
        }
        ~myClass()
        {
            load_save(true);
        }
        void load_save(bool save=false)
        {
            cout << "Saving" << endl;
//          TEMPLATE: config.load_save(/* myData */, save);
            config.load_save(myIval, save);
            config.load_save(myBval, save);
            config.load_save(mySval, save);
        }
};


int main()
{
    //Creat object of type 'myClass' to demonstrate saving
    myClass test; //save at destruction

    return 0;
}
