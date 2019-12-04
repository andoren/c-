#include <iostream>
#include "menu.hpp"
#include "truck.hpp"
#include "machinery.hpp"
using namespace std;

int main()
{
    Menu::ReadDataFromTextFile();
    while (Menu::Exec());
    Menu::Clean();
    return 0;
}
