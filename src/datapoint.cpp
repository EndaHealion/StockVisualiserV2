
#include "includes/datapoint.h"

void DataPoint::print() {
    printf("\"%s\", open: %f, close: %f, adj.close: %f, low: %f, high: %f, volume: %f, date: %s\n", ticker.c_str(), open_price, close_price, adjusted_close, low, high, volume, date->to_string().c_str());
}

