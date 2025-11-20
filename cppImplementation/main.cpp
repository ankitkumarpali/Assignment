#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <thread>
#include "countCars.h"
#include "revenueCars.h"
#include "distribution.h"
#include <future>
#include <chrono>
#include "loadCsv.h"

using namespace std;

int main() {

    auto start = chrono::high_resolution_clock::now();

    vector<vector<string> >data;
    map<string, int> header_map;
    // string line;

    // int idx = 0;
    // if(getline(file, line)){
    //     stringstream ss(line);
    //     string header;
    //     while(getline(ss, header, ',')){
    //         header_map[header] = idx;
    //         idx++;
    //     }
    // }

    // while(getline(file, line)){
    //     stringstream ss(line);
    //     string cell;
    //     vector<string> row;
    //     while(getline(ss, cell, ',')){
    //         row.push_back(cell);
    //     }
    //     data.push_back(row);
    // }

    int thread_count = thread::hardware_concurrency();

    LoadCsv loadCsv;
    vector<CarData> data1 = loadCsv.load_csv("../world_car_sales_1m.csv");

    GenerateCarsCount generateCarsCount(data1, header_map);
    revenueCars revenueCars(data1, header_map);
    Distribution distribution(data1, header_map);

    
    auto revenueBMW = async(launch::async, [&](){
        return revenueCars.calculate_revenue_cars(2025, "BMW");
    });
    auto countAudi = async(launch::async, [&](){    
        return generateCarsCount.calculate_car_count(2025, "Audi", "China");
    });
    auto distributionEurope = async(launch::async, [&](){
        return distribution.calculate_distribution("Europe");
    });

    int revenueBMW2025 = revenueBMW.get();
    int countAudi2025 = countAudi.get();
    vector<pair<string, int>> distributionEuropeanCountries = distributionEurope.get();    
    

    cout<<"Count of Audi in 2025 in China: "<<countAudi2025<<"\n";
    cout<<"Revenue of BMW in 2025: "<<revenueBMW2025<<"\n";
    cout<<"Distribution of Revenue in Europe: \n";


    for(auto country : distributionEuropeanCountries){
        cout<<country.first<<" "<<country.second<<"\n";
    }   
    // for(auto data_row : data){
    //     for(auto cell : data_row){
    //         cout<<cell<<" ";
    //     }
    //     cout<<"\n";
    // }
    // file.close();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout<<"Time taken: "<<duration.count()<<" milliseconds\n";
    return 0;
}