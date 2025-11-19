#ifndef COUNT_AUDI_H
#define COUNT_AUDI_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;
class GenerateCarsCount{
    private:
        vector<vector<string> > data;
        map<string, int> header_map;
    public:
        GenerateCarsCount(vector<vector<string> > data, map<string, int> header_map);
        int calculate_car_count(int year, string carBrand, string country);
};
#endif