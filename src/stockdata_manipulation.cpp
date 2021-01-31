
#include "includes/stockdata_manipulation.h"

// TODO(Enda): Is there a better way of doing sorting by different elements of the struct?
void sort_by_ticker(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->ticker < dp2->ticker); 
              });
}

void sort_by_open(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->open_price < dp2->open_price); 
              });
}

void sort_by_close(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->close_price < dp2->close_price); 
              });
}

void sort_by_adj_close(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->adjusted_close < dp2->adjusted_close); 
              });
}

void sort_by_high(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->high < dp2->high); 
              });
}

void sort_by_low(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->low < dp2->low); 
              });
}

void sort_by_volume(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (dp1->volume < dp2->volume); 
              });
}

void sort_by_date(std::vector<DataPoint*>* stock_data) {
    std::sort(stock_data->begin(), stock_data->end(), [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                  return (to_comaprable_date(dp1->date) < to_comaprable_date(dp2->date)); 
              });
}

// binary search with will take the largest index that matches the ticker
int binary_search_high_ticker(std::vector<DataPoint*>* stock_data, int left, int right, const std::string& ticker) {
    while (left < right) {
		int middle = left + (right - left) / 2;
		if ((*stock_data)[middle]->ticker > ticker) {
			right = middle;
		}
		else left = middle+1;
	}
	return right-1;
}

// binary search with will take the lowest index that matches the ticker
int binary_search_low_ticker(std::vector<DataPoint*>* stock_data, int left, int right, const std::string& ticker) {
    while (left < right) {
		int middle = left + (right - left) / 2;
		if ((*stock_data)[middle]->ticker < ticker) {
			left = middle+1;
		}
		else right = middle;
	}
	return left;
}

// requires tickers to be sorted
std::vector<std::string>* parse_tickers(std::vector<DataPoint*>* stock_data) {
    std::vector<std::string>* tickers = new std::vector<std::string>();
    const int size = stock_data->size();
    tickers->push_back((*stock_data)[0]->ticker);
    int pointer = binary_search_high_ticker(stock_data, 0, size, (*tickers)[0]);
    while (pointer+1 < size) {
        pointer = binary_search_high_ticker(stock_data, pointer+1, size, (*stock_data)[pointer+1]->ticker);
        tickers->push_back((*stock_data)[pointer]->ticker);
    }
    return tickers;
}

