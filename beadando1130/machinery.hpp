#pragma once
#include "vehicle.hpp"

class Machinery: public Vehicle{
    public:
        Machinery(string manuf,string type,string licence,double consumption, double usage);
        double getConsumption(int workDays);
        double getUsage(int workDays);
};
