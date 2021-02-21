/* date = January 30th 2021 10:10 pm */

#ifndef STOCKDATA_MANIPULATION_H
#define STOCKDATA_MANIPULATION_H

#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "datapoint.h"
#include "date.h"

std::vector<std::string>* init_sort(std::vector<DataPoint*>* stock_data);
std::vector<std::string>* i_sort(std::vector<DataPoint*>* stock_data);

void sort_by_ticker(std::vector<DataPoint*>* stock_data);
void sort_by_open(std::vector<DataPoint*>* stock_data);
void sort_by_close(std::vector<DataPoint*>* stock_data);
void sort_by_adj_close(std::vector<DataPoint*>* stock_data);
void sort_by_high(std::vector<DataPoint*>* stock_data);
void sort_by_low(std::vector<DataPoint*>* stock_data);
void sort_by_volume(std::vector<DataPoint*>* stock_data);
void sort_by_date(std::vector<DataPoint*>* stock_data); // oldest -> newest

std::vector<DataPoint*>* filter_between_dates(std::vector<DataPoint*>* stock_data, std::vector<std::string>* tickers, Date* start_date, Date* end_date);

int binary_search_high_ticker(std::vector<DataPoint*>* stock_data, int left, int right, const std::string& ticker);
int binary_search_low_ticker(std::vector<DataPoint*>* stock_data, int left, int right, const std::string& ticker);

// must be sorted first
std::vector<std::string>* parse_tickers(std::vector<DataPoint*>* stock_data);

#endif //STOCKDATA_MANIPULATION_H
