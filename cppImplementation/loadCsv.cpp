#include "loadCsv.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <iterator>
#include "CarData.h"
#include <iostream>

using namespace std;

LoadCsv loadCsv;

vector<CarData> LoadCsv::load_csv(string filename){
    vector<CarData> data;
    map<string, int> header_map;
    fstream file;
    int idx = 0;
    file.open(filename);

    if(!file.is_open()){
        cout<<"Error while opening the file\n";
        return data;
    }

    string contentCSV((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    vector<string>lines;

    size_t pos = 0, prev = 0;
    while((pos = contentCSV.find('\n', prev)) != string::npos){
        lines.push_back(contentCSV.substr(prev, pos - prev));
        prev = pos + 1;
    }

    if(prev < contentCSV.size()){
        lines.push_back(contentCSV.substr(prev));
    }

    stringstream ss(lines[0]);
    lines.erase(lines.begin());
    string header;

    while(getline(ss, header, ',')){
        header_map[header] = idx++;
    }

    int thread_count = thread::hardware_concurrency();
    int chunk_size = lines.size() / thread_count;
    vector<thread> workers;
    vector<vector<CarData>> partial_data(thread_count);

    auto worker = [&](int thread_id, int start, int end){
        
        for(int i = start; i < end; i++){
            vector<string> local_data;
            size_t s = 0, e = 0;
            string line = lines[i];
            while((e = line.find(',', s)) != string::npos){
                local_data.push_back(line.substr(s, e - s));
                s = e + 1;
            }
            local_data.push_back(line.substr(s));
            CarData carData;
            carData.manufacturer = local_data[header_map["manufacturer"]];
            carData.country = local_data[header_map["country"]];
            carData.sale_date = local_data[header_map["sale_date"]];
            carData.sale_price_usd = local_data[header_map["sale_price_usd"]];
            carData.region = local_data[header_map["region"]];
            partial_data[thread_id].push_back(carData);
        }
    };
    
    for(int i = 0; i < thread_count; i++){
        int start = i * chunk_size;
        int end = (i == thread_count - 1) ? lines.size() : start + chunk_size;
        workers.emplace_back(worker, i, start, end);
    }
    for(auto& worker : workers){
        worker.join();
    }
    for(auto& temp : partial_data){
        data.insert(data.end(), temp.begin(), temp.end());
    }
    return data;
}