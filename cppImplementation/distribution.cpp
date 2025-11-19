#include "distribution.h"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <thread>

using namespace std;

Distribution::Distribution(vector<vector<string> > data, map<string, int> header_map){
    this->data = data;
    this->header_map = header_map;
}

set<string> Distribution::get_country_list(string region){
    set<string> country_set;
    for(auto data_row : data){
        if(data_row[header_map["region"]] == region){
            country_set.insert(data_row[header_map["country"]]);
        }
    }
    return country_set;
}

vector<pair<string, int>> Distribution::calculate_distribution(string region){
    vector<pair<string, int>> distribution;   
    map<string, int> final_distribution;
    vector<thread> workers;
    int thread_count = thread::hardware_concurrency();

    vector<map<string, int>> local_distribution(thread_count);

    int chunk_size = data.size() / thread_count;

    auto worker = [&](int thread_id, int start, int end){
        for(int i = start; i < end; i++){
            auto data_row = data[i];
            if(data_row[header_map["region"]] == region){
                local_distribution[thread_id][data_row[header_map["country"]]] += stoi(data_row[header_map["sale_price_usd"]]);
            }
        }
    };

    // for(auto data_row : data){
    //     if(data_row[header_map["region"]] == region){
    //         distribution[data_row[header_map["country"]]] += stoi(data_row[header_map["sale_price_usd"]]);
    //     }
    // }

    for(int i = 0; i < thread_count; i++){
        int start = i * chunk_size;
        int end = (i == thread_count - 1) ? data.size() : start + chunk_size;
        workers.emplace_back(worker, i, start, end);
    }

    for(auto& worker : workers){
        worker.join();
    }

    for(auto local : local_distribution){
        for(auto item : local){
            final_distribution[item.first] += item.second;
        }
    }

    distribution.assign(final_distribution.begin(), final_distribution.end());
    sort(distribution.begin(), distribution.end(), [](const pair<string, int>& p1, const pair<string, int>& p2){
        return p1.second > p2.second;
    });

    return distribution;
}