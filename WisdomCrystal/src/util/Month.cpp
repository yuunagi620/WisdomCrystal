// Month.cpp

#include "Month.h"


namespace Util {
namespace Month {

std::string ToEnglishMonthName(int month) {
    const std::array<std::string, 13> Month = { "None",
                                                "Jan",
                                                "Feb",
                                                "Mar",
                                                "Apr",
                                                "May",
                                                "Jun",
                                                "Jul",
                                                "Aug",
                                                "Sep",
                                                "Oct",
                                                "Nov",
                                                "Dec" };

    try {
        return Month.at(month);
    } catch(const std::out_of_range&) {
        return Month.at(0); // ñ≥å¯Ç»åéÇ≈Ç†Ç¡ÇΩèÍçá "None" Çï‘Ç∑
    }
}

} // namespace Month
} // namespace Util
