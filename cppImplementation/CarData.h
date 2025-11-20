#ifndef CAR_DATA_H
#define CAR_DATA_H
#include <string>
using namespace std;    

struct CarData{
    string manufacturer;
    string model;
    string year;
    string country;
    string sale_date;
    string sale_price_usd;
    string region;
};
#endif