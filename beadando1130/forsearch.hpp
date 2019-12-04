#pragma once
#include <string>
#include <list>
using namespace std;
class ForSearch{
public:
    ForSearch(string man):manufacture(man){};
    string manufacture;
    list<string> types;
};
