#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include "countCars.h"
#include "revenueCars.h"
#include "distribution.h"

using namespace std;

int main() {
    fstream file;
    file.open("../world_car_sales_1m.csv");
    if(!file.is_open()){
        cout<<"Error while opening the file\n";
        return 1;
    }

    vector<vector<string> >data;
    map<string, int> header_map;
    string line;

    int idx = 0;
    if(getline(file, line)){
        stringstream ss(line);
        string header;
        while(getline(ss, header, ',')){
            header_map[header] = idx;
            idx++;
        }
    }

    while(getline(file, line)){
        stringstream ss(line);
        string cell;
        vector<string> row;
        while(getline(ss, cell, ',')){
            row.push_back(cell);
        }
        data.push_back(row);
    }

    GenerateCarsCount generateCarsCount(data, header_map);
    revenueCars revenueCars(data, header_map);
    Distribution distribution(data, header_map);

    int revenueBMW2025 = revenueCars.calculate_revenue_cars(2025, "BMW");
    int countAudi = generateCarsCount.calculate_car_count(2025, "Audi", "China");
    vector<pair<string, int>> distributionEurope = distribution.calculate_distribution("Europe");
    

    cout<<"Count of Audi in 2025 in China: "<<countAudi<<"\n";
    cout<<"Revenue of BMW in 2025: "<<revenueBMW2025<<"\n";
    cout<<"Distribution of Revenue in Europe: \n";


    for(auto country : distributionEurope){
        cout<<country.first<<" "<<country.second<<"\n";
    }   
    // for(auto data_row : data){
    //     for(auto cell : data_row){
    //         cout<<cell<<" ";
    //     }
    //     cout<<"\n";
    // }
    file.close();
    return 0;
}