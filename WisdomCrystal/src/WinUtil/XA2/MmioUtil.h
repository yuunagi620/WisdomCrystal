// MmioUtil.h

#pragma once

#include <Windows.h>

namespace MmioUtil {

bool ReadWaveFile(WAVEFORMATEX *WaveFormatEX,
                  std::shared_ptr<BYTE> *DataBodyAddress,
                  DWORD *DataSize,
                  TCHAR *WaveFilePath);

}
