
#include "includes/IO.h"

// TODO(Enda): Test if it is quicker to get the number of lines in the file and resize the vector or to use push_back()
std::vector<DataPoint*>* parse_datapoints_from_file(const std::string& filename) {
    std::vector<DataPoint*>* dp = new std::vector<DataPoint*>();
    std::ifstream* in_file = new std::ifstream(filename);
    // ticker, open, close, adj, low, high, volume, date
    if (in_file->is_open()) {
        std::string line;
        while(std::getline(*in_file, line)) {
            const int line_size = line.size();
            const int num_entries = 8;
            std::string dp_data[num_entries]{};
            int i = 0;
            int dp_data_ptr = 0;
            // split input lines by ','
            while (dp_data_ptr < num_entries) {
                std::string dp_entry = "";
                while (i<line_size && line[i] != ',') {
                    dp_entry += line[i++];
                }
                i++;
                dp_data[dp_data_ptr++] = dp_entry;
            }
            
            // parse day, month, and year
            int dates[3]{};
            int date_ptr = 0;
            int date_i = 0;
            const int date_size = dp_data[num_entries-1].size();
            while (date_ptr < 3) {
                std::string date_data = "";
                while (date_i<date_size && dp_data[num_entries-1][date_i] != '-') {
                    date_data += dp_data[num_entries-1][date_i++];
                }
                date_i++;
                dates[date_ptr++] = atoi(date_data.c_str());
            }
            
            dp->push_back(new DataPoint(dp_data[0],            // ticker
                                        std::stof(dp_data[1]), // open
                                        std::stof(dp_data[2]), // close
                                        std::stof(dp_data[3]), // adj. close
                                        std::stof(dp_data[4]), // low
                                        std::stof(dp_data[5]), // high
                                        std::stof(dp_data[6]), // volume
                                        dates[2],              // day
                                        dates[1],              // month
                                        dates[0]               // year
                                        ));
        }
        in_file->close();
    }
    else {
        fprintf(stderr, "ERROR: Could not open file: %s\n", filename.c_str());
        assert(false);
    }
    return dp;
}
