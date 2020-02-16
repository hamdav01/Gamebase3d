// RenderNodeManager.cpp //
#include "stdafx.h"
#include "RenderNodeManager.h"
#include "RenderSystem.h"
#include "RenderNode.h"
#include "Texture.h"
#include "Mesh.h"
#include "MeshUtils.h"

RenderNodeManager::RenderNodeManager(RenderSystem *p_pxRenderSystem) {
	m_pxRenderSystem = p_pxRenderSystem;
};

RenderNodeManager::~RenderNodeManager() {
	std::vector<RenderNode*>::iterator xIt = m_apxRenderNode.begin();

	for( ; xIt != m_apxRenderNode.end();xIt++) {
		delete(*xIt);
		m_apxRenderNode.erase(xIt);
		break;
	};
};

RenderNode *RenderNodeManager::Load(const char *meshName,const char *textureName) {
	RenderNode* node=new RenderNode;
	node->mpMesh=m_pxRenderSystem->CreateMesh();
	MeshUtils::CreateHeightmapFromBmp(meshName,node->mpMesh);
	node->mpTexture=m_pxRenderSystem->CreateTexture();
	node->mpTexture->Create("../data/textures/tile1x1m.png");
	node->CalculateBoundingVolume();
	return node;
};
