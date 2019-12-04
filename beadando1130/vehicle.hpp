#pragma once
#include <string>

using namespace std;
class Vehicle{
public:
    Vehicle(string manuf,string type,string licence, double usage,double consumption, char relation);
    void setManuf(string man){manuf_m = man;}
    void setType(string type){type_m = type;}
    void setLicence(string licence){licence_m = licence;}
    void setConsmption(double consumption){consumption_m = consumption;}
    void setUsage(double usage){usage_m = usage;}
    string getType(){return type_m;}
    string getManuf(){return manuf_m;}
    string getLicence(){return licence_m;}
    double getConsumption(){return consumption_m;}
    double getUsage(){return usage_m;}
    virtual double getConsumption(int workDays){};
    virtual double getUsage(int workDays){};
    virtual ~Vehicle(){};
    bool operator == (Vehicle v);
    string type_m;
    string manuf_m;
    string licence_m;
    double consumption_m;
    double usage_m;
    char relation_m;
};
