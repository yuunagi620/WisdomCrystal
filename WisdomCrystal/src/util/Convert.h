// Convert.h

#pragma once

#include "Point.h"
#include "PointF.h"


namespace Convert {

Point ToPoint(const PointF& p);

PointF ToPointF(const Point& p);

} // namespace Convert
