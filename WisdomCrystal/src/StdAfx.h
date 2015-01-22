// StdAfx.h
//
// プリコンパイル済みヘッダ
//

#pragma once

#include "WinUtil/D3D/D3DCore.h"
#include "WinUtil/D2D/D2DCore.h"

#include "WinUtil/XA2/XA2Core.h"
#include "WinUtil/XA2/SEData.h"
#include "WinUtil/XA2/BGMData.h"

// debug
#if _DEBUG
    #include "util/DebugManager.h"
    #define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
