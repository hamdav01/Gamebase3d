// RenderNode.h

#ifndef RENDENODE_H_INCLUDED
#define RENDENODE_H_INCLUDED

#include "BoundingVolumes.h"

class Mesh;
class Texture;

class RenderNode {
public:
	RenderNode();
	~RenderNode();
	void CalculateBoundingVolume();
	void moveNode(Vector3 *p_vPosition);
	//Vector3 m_vPosition;
	Texture *mpTexture;
	Mesh *mpMesh;
	Matrix4 mWorld;
	BoundingVolume mBoundingVolume;
};

#endif //RENDENODE_H_INCLUDED
