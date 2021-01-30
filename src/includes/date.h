/* date = January 30th 2021 2:44 pm */

#ifndef DATE_H
#define DATE_H

#include <string>

struct Date{
    int day;
    int month;
    int year;
    
    Date(int day, int month, int year) : day{day}, month{month}, year{year} {}
    
    std::string to_string();
};

#endif //DATE_H
