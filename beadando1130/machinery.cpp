#include "machinery.hpp"

Machinery::Machinery(string man, string type, string licence,double usage, double consumption): Vehicle(man,type,licence,usage,consumption,'m') {};

double Machinery::getConsumption(int workDays){
    return consumption_m*getUsage(workDays);
}
double Machinery::getUsage(int workDays){
    return workDays*usage_m;
}
