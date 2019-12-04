#pragma once
#include <string>
using namespace std;
typedef bool (*MenuFunc)();
class MenuItem{
public:
    MenuItem(string myText, MenuFunc myFunc):myFunc_m(myFunc),myText_m(myText){};
    bool invokeFunction(){return myFunc_m();}
    string getText(){return myText_m;}
private:
    MenuFunc myFunc_m;
    string myText_m;
};
