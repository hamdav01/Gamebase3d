// stdafx.h

#pragma once
#include "targetver.h"
#include <stdio.h>

#define WIN32_MEAN_AND_LEAN
#define VC_EXTRALEAN
#include <Windows.h>

#include <D3D10.h>
#include <D3DX10.h>
#pragma comment(lib,"d3d10.lib")
#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib,"dxerr.lib")
#pragma comment(lib,"d3dx10d.lib")
#else
#pragma comment(lib,"d3dx10.lib")
#endif

#include "Prereq.h"
#include "spiiUtils.h"
