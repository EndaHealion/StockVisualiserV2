
#include "includes/stockdata_manipulation.h"

std::vector<std::string>* i_sort(std::vector<DataPoint*>* stock_data) {
    std::stable_sort(stock_data->begin(), stock_data->end(),
                     [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                         return (to_comparable_date(dp1->date) < to_comparable_date(dp2->date));
                     });
    
    std::stable_sort(stock_data->begin(), stock_data->end(),
                         [](DataPoint* dp1, DataPoint* dp2) -> bool { 
                             return (dp1->ticker < dp2->ticker); 
                         });
    
    return parse_tickers(stock_data);
}

// TODO(Enda): FIX MEEEEE
std::vector<std::string>* init_sort(std::vector<DataPoint*>* stock_data) {
    sort_by_ticker(stock_data);
    std::vector<std::string>* tickers = parse_tickers(stock_data);
    const size_t stock_data_size = stock_data->size();
    const size_t tickers_size = tickers->size();
    
    for (unsigned int t=tickers_size-1; t>0; t--) {
        const int low_index = binary_search_low_ticker(stock_data, 0, (int)stock_data_size, (*tickers)[t]);
        const int high_index = binary_search_high_ticker(stock_data, 0, (int)stock_data_size, (*tickers)[t]);
        
        std::vector<DataPoint*>* stock_data_of_ticker = new std::vector<DataPoint*>();
        stock_data_of_ticker->resize(high_index-low_index+1);
        
        for (int i=low_index; i<=high_index; i++) {
            (*stock_data_of_ticker)[i-low_index] = (*stock_data)[i];
        }
        
        sort_by_date(stock_data_of_ticker);
        
        for (int i=low_index; i<=high_index; i++) {
            (*stock_data)[i-low_index] = (*stock_data_of_ticker)[i-low_index];
        }
    }
    
    return tickers;
}

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
                  return (to_comparable_date(dp1->date) < to_comparable_date(dp2->date));
              });
}

// binary search with will take the largest index that matches the ticker
int binary_search_high_ticker(std::vector<DataPoint*>* stock_data, int left, int right, const std::string& ticker) {
    while (left < right) {
		int middle = left + (right - left) / 2;
		if ((*stock_data)[middle]->ticker.compare(ticker) > 0) {
			right = middle;
		}
		else left = middle+1;
	}
	return right-1;
}

// TODO(Enda): Have a better look at this
std::vector<DataPoint*>* filter_between_dates(std::vector<DataPoint*>* stock_data, std::vector<std::string>* tickers, Date* start_date, Date* end_date) {
    const size_t tickers_size = tickers->size();
    const size_t stock_data_size = stock_data->size();
    std::vector<DataPoint*>* output = new std::vector<DataPoint*>();
    const int start_date_int = to_comparable_date(start_date);
    const int end_date_int = to_comparable_date(end_date);
    
    for (int t=0; t<tickers_size; t++) {
        const int low = binary_search_low_ticker(stock_data, 0, stock_data_size, (*tickers)[t]);
        const int high = binary_search_high_ticker(stock_data, 0, stock_data_size, (*tickers)[t]);
        for (int i=high; i>low; i--) {
            const int current_date = to_comparable_date((*stock_data)[i]->date);
            if (current_date >= start_date_int && current_date <= end_date_int) {
                output->push_back((*stock_data)[i]);
            }
        }
    }
    return output;
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

