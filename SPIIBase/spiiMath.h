// spiiMath.h

#ifndef SPIIMATH_H_INCLUDED
#define SPIIMATH_H_INCLUDED

namespace Math
{
	const f32 PI = 3.1415f;
	const f32 EPSILON = 0.00001f;

	f32 Sqrt(f32 v);
	f32 Sin(f32 a);
	f32 Cos(f32 a);
	f32 Tan(f32 a);
	f32 ATan(f32 a);
	f32 ToRad(f32 a);
	f32 ToDeg(f32 r);
	f32 Abs(f32 v);

	template <class T>
	void Swap(T &a,T &b) {
		T c=a;a=b;b=c;
	};

	template <class T>
	void Clamp(T& v,T a,T b) {
		v=v<a?a:v>b?b:v;
	};

	template <class T>
	void Wrap(T& v,T a) {
		if(v<-a) {
			v+=a;
		}
		else if(v>a) {
			v-=a;
		};
	};
};

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX Matrix4;
typedef D3DXQUATERNION Quaternion;
typedef D3DXPLANE Plane;

#endif // SPIIMATH_H_INCLUDED
