// Camera.cpp

#include "stdafx.h"
#include "BoundingVolumes.h"
#include "Camera.h"

// frustum
Frustum::Frustum() {};

void Frustum::Update(const Matrix4 &viewproj) {
	u32 i=0;
	// left plane
	mPlanes[i].a=viewproj._14+viewproj._11;
	mPlanes[i].b=viewproj._24+viewproj._21;
	mPlanes[i].c=viewproj._34+viewproj._31;
	mPlanes[i].d=viewproj._44+viewproj._41;

	// right plane
	i++;
	mPlanes[i].a=viewproj._14-viewproj._11;
	mPlanes[i].b=viewproj._24-viewproj._21;
	mPlanes[i].c=viewproj._34-viewproj._31;
	mPlanes[i].d=viewproj._44-viewproj._41;

	// top
	i++;
	mPlanes[i].a=viewproj._14-viewproj._12;
	mPlanes[i].b=viewproj._24-viewproj._22;
	mPlanes[i].c=viewproj._34-viewproj._32;
	mPlanes[i].d=viewproj._44-viewproj._42;

	// bottom
	i++;
	mPlanes[i].a=viewproj._14+viewproj._12;
	mPlanes[i].b=viewproj._24+viewproj._22;
	mPlanes[i].c=viewproj._34+viewproj._32;
	mPlanes[i].d=viewproj._44+viewproj._42;

	// near plane
	i++;
	mPlanes[i].a=viewproj._13;
	mPlanes[i].b=viewproj._23;
	mPlanes[i].c=viewproj._33;
	mPlanes[i].d=viewproj._43;

	// far plane
	i++;
	mPlanes[i].a=viewproj._14-viewproj._13;
	mPlanes[i].b=viewproj._24-viewproj._23;
	mPlanes[i].c=viewproj._34-viewproj._33;
	mPlanes[i].d=viewproj._44-viewproj._43;

	for(s32 i=0;i<6;i++) {
		D3DXPlaneNormalize(&mPlanes[i],&mPlanes[i]);
	};
};

bool Frustum::IsInside(BoundingVolume *volume) {
	for(s32 i=0;i<6;i++) {
		if(D3DXPlaneDotCoord(&mPlanes[i],&volume->mCenter) + volume->mRadius < 0.0f) {
			return false;
		};
	};
	return true;
};

bool Frustum::IsInside(AxisAlignedBoundingBox *aabb) {
	s32 result=1;
	for(s32 i=0;i<6;i++) {
		Vector3 p0(
			mPlanes[i].a>0.0f?aabb->mMax.x:aabb->mMin.x,
			mPlanes[i].b>0.0f?aabb->mMax.y:aabb->mMin.y,
			mPlanes[i].c>0.0f?aabb->mMax.z:aabb->mMin.z);
		Vector3 n0(
			mPlanes[i].a<0.0f?aabb->mMax.x:aabb->mMin.x,
			mPlanes[i].b<0.0f?aabb->mMax.y:aabb->mMin.y,
			mPlanes[i].c<0.0f?aabb->mMax.z:aabb->mMin.z);

		f32 n=D3DXPlaneDotCoord(&mPlanes[i],&p0);
		if(n<0.0f) return false;
		f32 m=D3DXPlaneDotCoord(&mPlanes[i],&n0);
		if(m<0.0f) result = 0; 
	};
	return result!=0;
};

// camera
Camera::Camera() {
	D3DXMatrixIdentity(&mView);
	D3DXMatrixIdentity(&mProj);
	D3DXMatrixIdentity(&mTransform);
	mYaw=mPitch=mRoll=0.0f;
	mIsDirty=true;
	mPosition=Vector3(0,0,0);
	mRight=Vector3(1,0,0);
	mUp=Vector3(0,1,0);
	mLook=Vector3(0,0,1);
};

void Camera::Update() {
	if(!mIsDirty) {return;};
	mIsDirty=false;

	Vector3 look(0,0,1);
	Vector3 up(0,1,0);
	Vector3 right(1,0,0);

	Matrix4 yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix,&up,mYaw);
	D3DXVec3TransformCoord(&look,&look,&yawMatrix);
	D3DXVec3TransformCoord(&right,&right,&yawMatrix);

	Matrix4 pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix,&right,mPitch);
	D3DXVec3TransformCoord(&look,&look,&pitchMatrix);
	D3DXVec3TransformCoord(&up,&up,&pitchMatrix);

	Matrix4 rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix,&look,mRoll);
	D3DXVec3TransformCoord(&up,&up,&rollMatrix);
	D3DXVec3TransformCoord(&right,&right,&rollMatrix);

	mRight=right;
	DoView(mPosition,look,up);

	mTransform=mView*mProj;
	mFrustum.Update(mTransform);
};

void Camera::RotateX(f32 v) {
	static const f32 a=Math::ToRad(89.0f);
	mIsDirty=true;
	mPitch+=v;
	Math::Clamp(mPitch,-a,a);
};

void Camera::RotateY(f32 v) {
	static const f32 a=Math::ToRad(360.0f);
	mIsDirty=true;
	mYaw+=v;
	Math::Wrap(mYaw,a);
};

void Camera::RotateZ(f32 v) {
	static const f32 a=Math::ToRad(360.0f);
	mIsDirty=true;
	mRoll+=v;
	Math::Wrap(mRoll,a);
};

void Camera::MoveX(f32 v) {
	mIsDirty=true;
	mPosition+=mRight*v;
};

void Camera::MoveY(f32 v) {
	mIsDirty=true;
	mPosition+=mUp*v;
};

void Camera::MoveZ(f32 v) {
	mIsDirty=true;
	mPosition+=mLook*v;
};

void Camera::DoView(const Vector3 &eye,const Vector3 &look_at,const Vector3 &up) {
	//D3DXMatrixLookAtLH(&mView,&eye,&look_at,&up);

	mUp=up;
	mLook=look_at;
	mPosition=eye;

	D3DXVec3Normalize(&mRight,&mRight);
	D3DXVec3Normalize(&mUp,&mUp);
	D3DXVec3Normalize(&mLook,&mLook);

	mView._11=mRight.x; mView._12=mUp.x; mView._13=mLook.x;
	mView._21=mRight.y; mView._22=mUp.y; mView._23=mLook.y;
	mView._31=mRight.z; mView._32=mUp.z; mView._33=mLook.z;

	mView._41=-D3DXVec3Dot(&mPosition,&mRight);
	mView._42=-D3DXVec3Dot(&mPosition,&mUp);
	mView._43=-D3DXVec3Dot(&mPosition,&mLook);
	mView._44=1.0f;
};

void Camera::DoProj(f32 aspect,f32 fov,f32 znear,f32 zfar) {
	D3DXMatrixPerspectiveFovLH(&mProj,fov,aspect,znear,zfar);
};

bool Camera::IsInside(BoundingVolume *volume) {
	return mFrustum.IsInside(volume);
};

bool Camera::IsInside(AxisAlignedBoundingBox *aabb) {
	return mFrustum.IsInside(aabb);
};
