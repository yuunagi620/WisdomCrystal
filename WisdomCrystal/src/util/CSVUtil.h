// CSVUtil.h

#pragma once

#include "CSVUtilImpl.h"


namespace CSVUtil {

// CSV �t�@�C�����烍�[�h
template<typename T>
bool ImportCSVData(const std::string& filePath, T *container);



} // namespace CSVUtil
