#include "menu.hpp"
#include <iostream>
#include "vehicle.hpp"
#include "truck.hpp"
#include "machinery.hpp"
#include <list>
#include <string>
#include <algorithm>
#include "forsearch.hpp"
#include <fstream>
#include <istream>
#include<vector>
#include<sstream>
using namespace std;

MenuItem Menu::menus[]=
{
    {"Add new truck",newTruck},
    {"Add new machinery",newMachinery},
    {"Sum of monthly consumption",getMonthlyFullConsumption},
    {"Monthly consumption by manufacterer and type",getMonthlyConsumptionByManfAndType},
    {"Monthly consumption by licence number",getMonthlyConsumptionByLicence},
    {"Save data",saveToTextFile},
    {"Exit",exitApp}

};
int Menu::selection;
list<Vehicle*> Menu::vehicles;
void Menu::Clean(){
    for (Vehicle* v: vehicles) {delete(v);}
}
bool Menu::exitApp(){
    if(saveToTextFile())cout <<"Data has been saved...";

    return false;
}
bool Menu::ReadDataFromTextFile(){
    char buffer[250];
    ifstream dataFile("data.txt");
    if( dataFile.is_open()) {
        while( dataFile.getline(buffer, 250)) {
            vector<string>lineData = splitData(buffer,';');
            if(lineData[0]=="t"){
                Truck* t = new Truck(lineData[1],lineData[2],lineData[3],stod(lineData[4]),stod(lineData[5]));
                vehicles.push_back(t);
            }
            else{
                Machinery* m = new Machinery(lineData[1],lineData[2],lineData[3],stod(lineData[4]),stod(lineData[5]));
                vehicles.push_back(m);
            }
        }
        dataFile.close();
        return true;
    }
    else
    {
        cout << "Cannot find or empty data.txt." << endl;
        return false;
    }
}
vector<string> Menu::splitData(const string& s, char delimiter){
   vector<std::string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
bool Menu::Exec(){

   int i = 1;
   for (MenuItem m: menus) {
      cout << i++ << ": " << m.getText() << endl;
   }
   cout << endl << "Select operation: ";
   cin >> selection;
   return menus[selection - 1].invokeFunction();
}
bool Menu::saveToTextFile(){
    ofstream myOutFile("data.txt");
    if( myOutFile.is_open()) {
        list<Vehicle*>::iterator it;
        for(it = vehicles.begin();it != vehicles.end();++it){
            Vehicle* v = *it;
            myOutFile <<v->relation_m<<";"<< v->getManuf()<<";"<<v->getType()<<";"<<v->getLicence()<<";"<<v->consumption_m<<";"<<v->usage_m << endl;
        }
        myOutFile.close();
    }
    return true;
}
bool Menu::getMonthlyConsumptionByLicence(){
   cout << "Licence number(abc-123): ";
   string licence;
   cin >> licence;
   list<Vehicle*>::iterator it;
   for(it = vehicles.begin(); it != vehicles.end(); ++it) {
      Vehicle* v = *it;
      if ((*v).getLicence() == licence) {
         cout << v->getManuf() << "-" << v->getType()<< "-"<<v->getLicence() << " monthly consumption is " << v->getConsumption(20) << endl;
      }
   }
   return true;
}
bool Menu::getMonthlyConsumptionByManfAndType(){
    list<string>manufactures = getManufactures();
    list<ForSearch*> searchlist = getManufAndTypes(manufactures);
    printForSearch(searchlist);
    return true;
}
bool Menu::getMonthlyFullConsumption(){

    int fullcon = 0;
    list<Vehicle*>::iterator it;
   for(it = vehicles.begin(); it != vehicles.end(); ++it) {
      Vehicle* v = *it;
      fullcon += v->getConsumption(20);
   }
    cout<<"The sum of the vehicles monthly consumption is "<<fullcon <<endl;
    return true;
}
bool Menu::newMachinery(){
   cout << "Enter new Machinary Manufacterer: ";
   string man;
   cin >> man;

   cout << "Enter new Machinary Type: ";
   string type;
   cin >> type;

   cout << "Enter new Machinary Licence number: ";
   string licence;
   cin >> licence;
   cout << "Enter new Machinary daily usage in hours: ";
   int usage;
   cin >> usage;
   cout << "Enter new Machinary consumption in hours: ";
   int con;
   cin >> con;
   Machinery* machinery = new Machinery(man,type,licence,usage,con);
   vehicles.push_back(machinery);
   return true;
}
bool Menu::newTruck(){
   cout << "Enter new Truck Manufacterer: ";
   string man;
   cin >> man;

   cout << "Enter new Truck Type: ";
   string type;
   cin >> type;

   cout << "Enter new Truck Licence number: ";
   string licence;
   cin >> licence;
   cout << "Enter new Truck daily usage in km: ";
   int usage;
   cin >> usage;
   cout << "Enter new Truck consumption(100km): ";
   int con;
   cin >> con;
   Truck* truck = new Truck(man,type,licence,usage,con);
   vehicles.push_back(truck);
   return true;
}
list<string>Menu::getManufactures(){
    list<string>manufactures;
    list<Vehicle*>::iterator it;
   for(it = vehicles.begin(); it != vehicles.end(); ++it) {
        Vehicle* v = *it;
        std::list<string>::iterator itf;
        itf = std::find(manufactures.begin(), manufactures.end(), v->getManuf());
        if(itf == manufactures.end())
            manufactures.push_back(v->getManuf());
   }
   list<string>::iterator itf;
   return manufactures;
}
list<ForSearch*>Menu::getManufAndTypes(list<string> manufactures){
    list<ForSearch*> returnElement;
    list<ForSearch*>::iterator itf;
    list<Vehicle*>::iterator itv;
    list<string>::iterator itm;
    for(itm = manufactures.begin(); itm != manufactures.end(); ++itm) {
      returnElement.push_back(new ForSearch(*itm));
    }
    for(itf=returnElement.begin();itf != returnElement.end();++itf){
        ForSearch* f = *itf;
        for(itv = vehicles.begin();itv!=vehicles.end();++itv){
            Vehicle* v = *itv;
            if(f->manufacture == v->getManuf() && (std::find(f->types.begin(), f->types.end(), v->getType()) == f->types.end())){
                f->types.push_back(v->getType());
            }
        }
    }

    return returnElement;

}
void Menu::printForSearch(list<ForSearch*>searchlist){
    list<ForSearch*>::iterator it;
    for(it= searchlist.begin();it!=searchlist.end();++it){
        ForSearch* f = *it;
        cout<<f->manufacture<<":"<<endl;
        list<string>::iterator its;
        for(its = f->types.begin();its != f->types.end();++its){
            int cons = 0;
            string type = *its;
            list<Vehicle*>::iterator itv;
            for(itv = vehicles.begin();itv != vehicles.end();++itv){
                Vehicle* v = *itv;
                if(v->getManuf() == f->manufacture && v->getType() == type){
                    cons += v->getConsumption(20);
                }
            }
            cout <<"\t"<<type<<" consumptions is: "<<cons<<endl;
        }
        cout<<endl;
    }
}
