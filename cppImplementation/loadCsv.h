#ifndef LOAD_CSV_H
#define LOAD_CSV_H
#include <vector>
#include <string>
#include <map>
#include "CarData.h"
using namespace std;

class LoadCsv{
    private:
        vector<CarData> data;
        map<string, int> header_map;
    public:
    vector<CarData> load_csv(string filename);
};

#endif