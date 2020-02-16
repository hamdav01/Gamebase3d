// RenderNode.cpp

#include "stdafx.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderNode.h"
#include <iostream>

RenderNode::RenderNode() {
	mpTexture=NULL;
	mpMesh=NULL;
	D3DXMatrixIdentity(&mWorld);
};
RenderNode::~RenderNode() {
	if(mpTexture!=NULL) {
		delete mpTexture;
		mpTexture=NULL;
	}
	if(mpMesh!=NULL) {
		delete mpMesh;
		mpTexture=NULL;
	}
}
void RenderNode::moveNode(Vector3 *p_vPosition) {
	D3DXMatrixTranslation(&mWorld,p_vPosition->x,p_vPosition->y,p_vPosition->z);
	CalculateBoundingVolume();
	std::cout << "RenderNode: " << p_vPosition->x << std::endl;
	//D3DXMatrixRotationY(&mWorld,rot);
};

void RenderNode::CalculateBoundingVolume() {
	if(mpMesh==NULL) {return;};
	
	Vector3 lC=mpMesh->GetCenter();
	mBoundingVolume.mRadius=mpMesh->GetRadius();
	
	//mBoundingVolume.mRadius=10.0f;
	mBoundingVolume.mCenter.x=mWorld._41+lC.x;
	mBoundingVolume.mCenter.y=mWorld._42+lC.y;
	mBoundingVolume.mCenter.z=mWorld._43+lC.z;
};
