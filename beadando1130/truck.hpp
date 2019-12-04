#include "vehicle.hpp"
#pragma once
class Truck:public Vehicle{
    public:
        Truck(string manuf,string type,string licence,double consumption, double usage);
        double getConsumption(int workDays);
        double getUsage(int workDays);
};


