// StdAfx.h
//
// プリコンパイル済みヘッダ
//

#pragma once

#include "win/D3D/D3DCore.h"
#include "win/D2D/D2DCore.h"

#include "win/XA2/XA2Core.h"
#include "win/XA2/SEData.h"
#include "win/XA2/BGMData.h"

// debug
#if _DEBUG
    #include "util/DebugManager.h"
    #define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
