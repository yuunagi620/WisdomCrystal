// CSVUtil.h

#pragma once

#include "CSVUtilImpl.h"


namespace CSVUtil {

// CSV �t�@�C����ǂݍ���
template<typename T>
bool ImportData(const std::string& filePath, T *data);

// CSV �t�@�C���֏�������
template<typename T>
bool ExportData(const std::string& filePath, T *data);


} // namespace CSVUtil
