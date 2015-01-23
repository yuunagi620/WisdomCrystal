// CSVUtil.h

#pragma once

#include <array>


namespace CSVUtil {

bool ImportCSVData(std::string fileName, std::array<int, 880> *vector);

}