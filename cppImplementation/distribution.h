#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <vector>
#include <string>
#include <map>
#include <set>
#include "CarData.h"
using namespace std;

class Distribution{
    private:
        vector<CarData> data;
        map<string, int> header_map;
    public:
        Distribution(vector<CarData> data, map<string, int> header_map);
        set<string> get_country_list(string region);
        vector<pair<string, int>> calculate_distribution(string region);

};
#endif
