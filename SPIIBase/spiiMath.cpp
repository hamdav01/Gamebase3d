// spiiMath.cpp

#include "stdafx.h"
#include "spiiMath.h"

namespace Math
{
	f32 Sqrt(f32 v) {return ::sqrtf(v);};
	f32 Sin(f32 a) {return ::sinf(a);};
	f32 Cos(f32 a) {return ::cosf(a);};
	f32 Tan(f32 a) {return ::tanf(a);};
	f32 ATan(f32 a) {return ::atanf(a);};
	f32 ToRad(f32 a) {return a*PI/180.0f;};
	f32 ToDeg(f32 r) {return r*180.0f/PI;};
	f32 Abs(f32 v) {return ::fabs(v);};
};
