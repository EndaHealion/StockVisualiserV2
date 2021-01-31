/* date = January 30th 2021 3:04 pm */

#ifndef _I_O_H
#define _I_O_H

#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include <stdio.h>

#include "datapoint.h"
#include "date.h"

std::vector<DataPoint*>* parse_datapoints_from_file(const std::string& file_location);
unsigned int get_num_datapoint_entries(const std::string& file_location);

#endif //_I_O_H
