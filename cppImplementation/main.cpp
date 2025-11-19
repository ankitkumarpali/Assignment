#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include "countAudi.h"
#include "revenueBMW.h"
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

    GenerateAudiCount generateAudiCount(data, header_map);
    revenueBMW revenueBMW(data, header_map);
    Distribution distribution(data, header_map);

    int revenueBMW2025 = revenueBMW.calculate_revenue_bmw(2025, "BMW");
    int countAudi = generateAudiCount.calculate_revenue_audi(2025, "Audi", "Germany");
    vector<pair<string, int>> distributionEurope = distribution.calculate_distribution("Europe");
    

    cout<<"Count of Audi in 2025 in Germany: "<<countAudi<<"\n";
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