// Camera.h

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

class BoundingVolume;
class AxisAlignedBoundingBox;

class Frustum {
public:
	Frustum();

	void Update(const Matrix4 &viewproj);
	bool IsInside(BoundingVolume *volume);
	bool IsInside(AxisAlignedBoundingBox *aabb);

private:
	Plane mPlanes[6];
};

class Camera {
	friend class RenderSystem;
public:
	Camera();

	void Update();

	void RotateX(f32 v);
	void RotateY(f32 v);
	void RotateZ(f32 v);
	void MoveX(f32 v);
	void MoveY(f32 v);
	void MoveZ(f32 v);

	void DoView(const Vector3 &eye,const Vector3 &look_at,const Vector3 &up);
	void DoProj(f32 aspect,f32 fov,f32 znear,f32 zfar);

	bool IsInside(BoundingVolume *volume);
	bool IsInside(AxisAlignedBoundingBox *aabb);

private:
	bool mIsDirty;
	Matrix4 mView,mProj,mTransform;
	f32 mYaw,mPitch,mRoll;
	Vector3 mPosition,mRight,mUp,mLook;
	Frustum mFrustum;
};

#endif // CAMERA_H_INCLUDED
