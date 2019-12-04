#include "truck.hpp"

Truck::Truck(string man, string type, string licence,double usage, double consumption): Vehicle(man,type,licence,usage,consumption,'t') {};
double Truck::getConsumption(int workDays){
    return consumption_m*getUsage(workDays)/100;
}
double Truck::getUsage(int workDays){
    return workDays*usage_m;
}
