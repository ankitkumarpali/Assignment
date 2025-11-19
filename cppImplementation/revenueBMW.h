#ifndef REVENUE_BMW_H
#define REVENUE_BMW_H
#include <vector>
#include <string>
#include <map>

using namespace std;

class revenueBMW{
    private:
        vector<vector<string> > data;
        map<string, int> header_map;
    public:
        revenueBMW(vector<vector<string> > data, map<string, int> header_map);
        int calculate_revenue_bmw(int year, string country);
};
#endif