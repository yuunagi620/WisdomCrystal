// Convert.cpp

#include "Convert.h"


namespace Util {

Point Convert::ToPoint(const PointF& p) {
    return Point(static_cast<int>(p.x), static_cast<int>(p.y));
}


PointF Convert::ToPointF(const Point& p) {
    return PointF(static_cast<float>(p.x), static_cast<float>(p.y));
}

} // namespace Util
