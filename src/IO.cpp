
#include "includes/IO.h"

unsigned int get_num_datapoint_entries(const std::string& file_location) {
    std::ifstream* file = new std::ifstream(file_location);
    unsigned int size = 0;
    if (file->is_open()) {
        std::string line = "";
        while(std::getline(*file, line)) {
            size++;
        }
    }
    else {
        fprintf(stderr, "ERROR: Could not open file in get_num_datapoint_entries(): %s\n", file_location.c_str());
        assert(false);
    }
    return size;
}

std::vector<DataPoint*>* parse_datapoints_from_file(const std::string& file_location) {
    const unsigned int dp_size = get_num_datapoint_entries(file_location);
    std::vector<DataPoint*>* dp = new std::vector<DataPoint*>();
    dp->resize(dp_size);
    
    // File format: ticker,open,close,adj,low,high,volume,date{year-month-day}
    const unsigned int num_entries = 8;
    std::ifstream* in_file = new std::ifstream(file_location);
    if (in_file->is_open()) {
        std::string line;
        for (unsigned int i=0; i<dp_size; i++) {
            std::getline(*in_file, line);
            const int line_size = line.size();
            std::string line_data[num_entries]{};
            int line_char = 0;
            int line_data_ptr = 0;
            // split input lines by ','
            while (line_data_ptr < num_entries) {
                std::string line_entry = "";
                while (line_char<line_size && line[line_char] != ',') {
                    line_entry += line[line_char++];
                }
                line_char++;
                line_data[line_data_ptr++] = line_entry;
            }
            
            // parse day, month, and year
            int dates[3]{};
            int date_ptr = 0;
            int date_i = 0;
            const int date_size = line_data[num_entries-1].size();
            while (date_ptr < 3) {
                std::string date_data = "";
                while (date_i<date_size && line_data[num_entries-1][date_i] != '-') {
                    date_data += line_data[num_entries-1][date_i++];
                }
                date_i++;
                dates[date_ptr++] = atoi(date_data.c_str());
            }
            
            (*dp)[i] = new DataPoint(line_data[0],            // ticker
                                     std::stof(line_data[1]), // open
                                     std::stof(line_data[2]), // close
                                     std::stof(line_data[3]), // adj. close
                                     std::stof(line_data[4]), // low
                                     std::stof(line_data[5]), // high
                                     std::stof(line_data[6]), // volume
                                     dates[2],                // day
                                     dates[1],                // month
                                     dates[0]                 // year
                                     );
        }
        in_file->close();
    }
    else {
        fprintf(stderr, "ERROR: Could not open file in parse_datapoints_from_file(): %s\n", file_location.c_str());
        assert(false);
    }
    return dp;
}
