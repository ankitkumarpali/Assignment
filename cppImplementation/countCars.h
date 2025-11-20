#ifndef COUNT_AUDI_H
#define COUNT_AUDI_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "CarData.h"
using namespace std;
class GenerateCarsCount{
    private:
        vector<CarData> data;
        map<string, int> header_map;
    public:
        GenerateCarsCount(vector<CarData> data, map<string, int> header_map);
        int calculate_car_count(int year, string carBrand, string country);
};
#endif