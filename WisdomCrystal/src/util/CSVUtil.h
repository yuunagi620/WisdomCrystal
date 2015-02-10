// CSVUtil.h

#pragma once

#include "CSVUtilImpl.h"


namespace CSVUtil {

// CSV ファイルからロード
template<typename T>
bool ImportCSVData(const std::string& filePath, T *container);



} // namespace CSVUtil
