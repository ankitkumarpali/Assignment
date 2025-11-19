#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "revenueBMW.h"

using namespace std;

revenueBMW::revenueBMW(vector<vector<string> > data, map<string, int> header_map){
    this->data = data;
    this->header_map = header_map;
}

int revenueBMW::calculate_revenue_bmw(int year, string carBrand){
    int total_revenue = 0;

    for(auto data_row : data){
        int manufacturer_idx = this->header_map["manufacturer"];
        int year_idx = this->header_map["year"];
        int sale_price_idx = this->header_map["sale_price_usd"];
        string year_str = data_row[year_idx].substr(0, 4);
        int year = stoi(year_str);
        if(data_row[manufacturer_idx] == carBrand && data_row[year_idx] == year){
            total_revenue += stoi(data_row[sale_price_idx]);
        }
    }
    return total_revenue;
    
}