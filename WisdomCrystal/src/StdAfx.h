// StdAfx.h
//
// �v���R���p�C���ς݃w�b�_
//

#pragma once

#include "win/WIC/WICCore.h"
#include "win/D3D/D3DCore.h"
#include "win/D2D/D2DCore.h"

#include "win/XA2/XA2Core.h"
#include "win/XA2/SEData.h"
#include "win/XA2/BGMData.h"

// debug
#if _DEBUG
    #include "win/util/DebugManager.h"
    #define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
