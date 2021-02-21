/* date = January 30th 2021 2:42 pm */

#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>
#include <stdio.h>

#include "date.h"

struct DataPoint {
    std::string ticker;
    float open_price;
    float close_price;
    float adjusted_close;
    float low;
    float high;
    float volume;
    Date* date = nullptr;
    
    DataPoint(const std::string& tick, float open, float close, float adj, float lo, float hi, float vol, int day, int month, int year) : ticker{tick}, open_price{open}, close_price{close}, adjusted_close{adj}, low{lo}, high{hi}, volume{vol} {
        this->date = new Date(day, month, year);
    }
    
    void print();
};

#endif //DATAPOINT_H
