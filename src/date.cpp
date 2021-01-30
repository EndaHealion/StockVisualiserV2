
#include "includes/date.h"

std::string Date::to_string() {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}
