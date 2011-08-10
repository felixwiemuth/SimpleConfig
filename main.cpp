/* Copyright (C) 2011 by Felix Wiemuth
   This code is licensed under the GNU GENERAL PUBLIC LICENSE http://www.gnu.org/licenses/gpl.txt */

/*
    This is a demonstration on how to use SimpleConfig.
    Note the "(!)" signs to test different things.

    ATTENTION: Be careful when using the binary save mode.
    In binary mode, the memory fields are written to the file as they are
    and the variables are loaded with that much data from the file as their size allows.
    So watch out that you do not load/save data that is or includes actually pointers etc.
    (For example, you cannot simply load/save the type "std::string"
     because it is a complex type that includes pointers, so you would actually save
     adresses instead of data!).

    GENERAL ADVISE: Always load the same variables in the same order as they were saved.
    Otherwise you can quickly mess up all your data. To avoid making errors SimpleConfig
    is designed in a way that it is enough to define one function to load AND save your data.
    See the example class below to understand how this is meant.

    The main point of this test routine is first to create a class object in the main() function
    (what as a result loads data from the file), then change the loaded variables and destroy the object again
    (what as a result saves data to the file). Afterwards a new object is created to load the previously
    saved data again.
*/


#include <iostream>

#include "Config.h"
#include "templates.h"

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
            config.set_binary(); // (!) comment out to test formatted mode
            load_save(); // (!) comment out on first run to create a file!
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
            //config.load_save(mySval, save); // (!) uncomment to test formatted mode
        }
        void set_vars()
        {
            myIval = 266;
            myBval = true;
            myFval = 0.987;
            mySval = "Binary test is this. ok. SECOND CHANGED ;)";
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
    myClass* test = new myClass();
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

    //Another test
    Config config("test.save");
    int i = 25;
    config.load_save(i, true);
    i = 36;
    config.load_save(i);
    cout << "i: " << i << endl;

    config.change_file("test2.bin", true);
    i++;
    config.load_save(i, true);

    config.change_file("void.txt");

    config.change_file("test2.bin", true);
    int loaded;
    config.load_save(loaded);
    cout << "loaded: " << loaded << endl;

    //Test exceptions
    Config c;
    int a, b;
    c.load_save(a);
    if (!c)
        cout << "Error Code: " << c.get_failure() << endl;
    else
        cout << "No error accured!" << endl;
    c.clear();
    if (!c)
        cout << "Error Code: " << c.get_failure() << endl;
    else
        cout << "No error accured!" << endl;

    //Test load/save with shift operators
    Config myconf("test.save");
    int x;
    myconf >> x;
    cout << "x: " << x << endl;
    myconf.change_file("test_modified.save");
    x *= 2;
    myconf << x;

    return 0;
}
