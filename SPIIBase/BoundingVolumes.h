// BoundingVolumes.h

#ifndef BOUNDINGVOLUMES_H_INCLUDED
#define BOUNDINGVOLUMES_H_INCLUDED

class BoundingVolume {
public:
	Vector3 mCenter;
	f32 mRadius;
};

class AxisAlignedBoundingBox {
public:
	Vector3 mMin;
	Vector3 mMax;
};

#endif // BOUNDINGVOLUMES_H_INCLUDED
