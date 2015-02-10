// CSVUtil.h

#pragma once

#include "CSVUtilImpl.h"


namespace CSVUtil {

// CSV ファイルを読み込み
template<typename T>
bool ImportData(const std::string& filePath, T *data);

// CSV ファイルへ書き込み
template<typename T>
bool ExportData(const std::string& filePath, T *data);


} // namespace CSVUtil
