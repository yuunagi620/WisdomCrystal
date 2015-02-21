// Convert.h

#pragma once

#include "Point.h"
#include "PointF.h"

namespace Util {
namespace Convert {

Point ToPoint(const PointF& p);

PointF ToPointF(const Point& p);

} // namespace Convert
} // namespace Util