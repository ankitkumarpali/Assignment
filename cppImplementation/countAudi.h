#ifndef COUNT_AUDI_H
#define COUNT_AUDI_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;
class GenerateAudiCount{
    private:
        vector<vector<string> > data;
        map<string, int> header_map;
    public:
        GenerateAudiCount(vector<vector<string> > data, map<string, int> header_map);
        int calculate_revenue_audi(int year, string carBrand, string country);
};
#endif