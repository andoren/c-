#include "vehicle.hpp"

Vehicle::Vehicle(string manuf,string type,string licence, double usage,double consumption,char relation):manuf_m(manuf),type_m(type),licence_m(licence),consumption_m(consumption),usage_m(usage),relation_m(relation){};

bool Vehicle::operator == (Vehicle v){
    return getLicence() == v.getLicence();
}
