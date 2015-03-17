// Month.cpp

#include <array>

#include "Month.h"


namespace Month {

const std::string& ToEnglishMonthName(int month) {
    const std::array<std::string, 13> Month = {
        "None", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    try {
        return Month.at(month);
    } catch(const std::out_of_range&) {
        return Month.at(0); // –³Œø‚ÈŒ‚Å‚ ‚Á‚½ê‡ "None" ‚ğ•Ô‚·
    }
}

} // namespace Month

