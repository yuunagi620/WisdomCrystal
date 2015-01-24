// MmioUtil.h

#pragma once

#include <Windows.h>
#include <string>


namespace MmioUtil {

bool ReadWaveFile(WAVEFORMATEX *WaveFormatEX,
                  std::shared_ptr<BYTE> *DataBodyAddress,
                  DWORD *DataSize,
                  TCHAR* WaveFilePath);

}
