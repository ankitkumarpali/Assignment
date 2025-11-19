#include "countAudi.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
using namespace std;

GenerateAudiCount::GenerateAudiCount(vector<vector<string> > data, map<string, int> header_map){
    this->data = data;
    this->header_map = header_map;
}

int GenerateAudiCount::calculate_revenue_audi(int year, string carBrand, string country){
    int total_count = 0;
    int manufacturer_idx = this->header_map["manufacturer"];
    int country_idx = this->header_map["country"];
    int sale_date_idx = this->header_map["sale_date"];


    vector<thread> workers;
    int thread_count = thread::hardware_concurrency();

    int chunk_size = data.size() / thread_count;

    cout<<"Thread count: "<<thread_count<<"\n";

    vector<int> local_count(thread_count);

    auto worker = [&](int thread_id, int start, int end){
        for(int i = start; i < end; i++){
            auto data_row = data[i];
            string sale_date = data_row[sale_date_idx];
            string sale_year_str = sale_date.substr(0, 4);
            int sale_year = stoi(sale_year_str);
            if(data_row[manufacturer_idx] == carBrand && sale_year == year && data_row[country_idx] == country){
                local_count[thread_id] += 1;
            }
        }
    };  

    

    for(int i = 0; i < thread_count; i++){
        int start = i * chunk_size;
        int end = (i == thread_count - 1) ? data.size() : start + chunk_size;
        workers.emplace_back(worker, i, start, end);
    }

    for(auto& worker : workers){
        worker.join();
    }

    for(auto local : local_count){
        cout<<"Local count: "<<local<<"\n";
        total_count += local;
    }

    // for(auto data_row : data){
    //     // Parse year from sale_date (format: YYYY-MM-DD)
    //     string sale_date = data_row[sale_date_idx];
    //     string sale_year_str = sale_date.substr(0, 4);
    //     int sale_year = stoi(sale_year_str);
    //     // cout<<data_row[manufacturer_idx]<<" "<<sale_year<<" "<<data_row[country_idx]<<"\n";
        
    //     if(data_row[manufacturer_idx] == carBrand && sale_year == year && data_row[country_idx] == country){
    //         total_count += 1;
    //     }
    // }
    return total_count;
}