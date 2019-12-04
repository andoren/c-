#pragma once
#include <list>
#include "menu_item.hpp"
#include "vehicle.hpp"
#include "truck.hpp"
#include "machinery.hpp"
#include <string>
#include "forsearch.hpp"
#include <vector>
using namespace std;

class Menu {
    public:
        static bool Exec();
        static void Clean();
        static bool ReadDataFromTextFile();
    private:
        static MenuItem menus[];
        static int selection;
        static bool newMachinery();
        static bool newTruck();
        static bool getMonthlyFullConsumption();
        static bool getMonthlyConsumptionByLicence();
        static bool getMonthlyConsumptionByManfAndType();
        static bool exitApp();
        static list<Vehicle*> vehicles;
        static list<string>getManufactures();
        static list<ForSearch*>getManufAndTypes(list<string> manufactures);
        static void printForSearch(list<ForSearch*>searchlist);
        static bool saveToTextFile();
        static vector<string> splitData(const string& s, char delimiter);
};

