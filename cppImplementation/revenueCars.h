#ifndef REVENUE_CARS_H
#define REVENUE_CARS_H
#include <vector>
#include <string>
#include <map>

using namespace std;

class revenueCars{
    private:
        vector<vector<string> > data;
        map<string, int> header_map;
    public:
        revenueCars(vector<vector<string> > data, map<string, int> header_map);
        int calculate_revenue_cars(int year, string carBrand);
};
#endif