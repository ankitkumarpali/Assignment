#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "revenueCars.h"
#include <thread>

using namespace std;

revenueCars::revenueCars(vector<vector<string> > data, map<string, int> header_map){
    this->data = data;
    this->header_map = header_map;
}

int revenueCars::calculate_revenue_cars(int year, string carBrand){
    int total_revenue = 0;
    int manufacturer_idx = this->header_map["manufacturer"];
    int sale_date_idx = this->header_map["sale_date"];
    int sale_price_idx = this->header_map["sale_price_usd"];


    vector<thread> workers;
    int thread_count = thread::hardware_concurrency();

    vector<int> local_revenue(thread_count);

    int chunk_size = data.size() / thread_count;

    auto worker = [&](int thread_id, int start, int end){
        for(int i = start; i < end; i++){
            auto data_row = data[i];
            string sale_date = data_row[sale_date_idx];
            string sale_year_str = sale_date.substr(0, 4);
            int sale_year = stoi(sale_year_str);
            if(data_row[manufacturer_idx] == carBrand && sale_year == year){
                local_revenue[thread_id] += stoi(data_row[sale_price_idx]);
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

    for(auto local : local_revenue){
        total_revenue += local;
    }

    // for(auto data_row : data){
    //     // Parse year from sale_date (format: YYYY-MM-DD)
    //     string sale_date = data_row[sale_date_idx];
    //     string sale_year_str = sale_date.substr(0, 4);
    //     int sale_year = stoi(sale_year_str);
        
    //     if(data_row[manufacturer_idx] == carBrand && sale_year == year){
    //         total_revenue += stoi(data_row[sale_price_idx]);
    //     }
    // }

    return total_revenue;
}

