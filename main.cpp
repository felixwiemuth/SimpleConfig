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
        float myFval;
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
            config.load_save(myFval, save);
            config.load_save(mySval, save);
        }
        void set_vars()
        {
            myIval = 16;
            myBval = true;
            myFval = 0.999;
            mySval = "New String";
        }
        void print()
        {
            cout << "myIval: " << myIval
                 << "\nmySval: " << mySval
                 << "\nmyFval: " << myFval
                 << endl << "myBval: ";
            if (myBval)
                cout << "TRUE";
            else
                cout << "FALSE";
            cout << "\n" << std::endl;
        }
};


int main()
{
    //Creat objects of type 'myClass' to demonstrate loading/saving
    myClass* test = new myClass(); //save at destruction
    cout << "--- LOADED ---" << endl;
    test->print();
    test->set_vars();
    cout << "--- CHANGED ---" << endl;
    test->print();
    delete test;
    test = new myClass();
    cout << "--- NEW OBJECT ---" << endl;
    test->print();
    delete test;

    return 0;
}
