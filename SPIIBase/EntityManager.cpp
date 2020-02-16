// EntityManager.cpp //

#include "stdafx.h"
#include "EntityManager.h"
#include "RenderSystem.h"
#include "Entity.h"
#include "RenderNode.h"
#include "Mesh.h"
#include "MeshUtils.h"
#include "Texture.h"

EntityManager::EntityManager(RenderSystem* p_pxRenderSystem) {
	mRenderSystem = p_pxRenderSystem;

};
EntityManager::~EntityManager() {
	delete mRenderSystem;
	mRenderSystem=NULL;
}

void EntityManager::DestroyAll()
{
	for(int i=0; i<m_apxEntities.size(); i++) {
		delete (m_apxEntities[i]);
		m_apxEntities[i] = NULL;
	};
	m_apxEntities.clear();
};

void EntityManager::Update(float p_fDeltaTime) {
	for(int i=0; i<m_apxEntities.size(); i++) {
		m_apxEntities[i]->Update(p_fDeltaTime); // updates all the entities
	};
};

void EntityManager::DestroyEntity(Entity *p_pxEntity) {
	std::vector<Entity*>::iterator xIt=m_apxEntities.begin();
	for( ; xIt != m_apxEntities.end(); xIt++) {
		if((*xIt)==p_pxEntity) {
			delete(*xIt);
			m_apxEntities.erase(xIt);
			break;
		};
	};
};

void EntityManager::Render() {
	for(int i=0; i<m_apxEntities.size(); i++) {
		mRenderSystem->Render(m_apxEntities[i]->GetProperty<RenderNode>("RenderNode"));
		//mRenderSystem->Render(m_apxEntities[i]->GetRenderNode()); // Renders all the entities with a IsRenderable == true.
	};
}

void EntityManager::Collision() {
	for(int i=0; i<m_apxEntities.size();i++)
	{
		/*if(m_apxEntities[i]->IsCollisionable())
		{
			for(int j=i+1; j<m_apxEntities.size();j++)
			{
				//p_apxCollisionManager->Check(m_apxEntities[i],m_apxEntities[j]); // Checks collision between entities
			}
		}*/
	}
}

void EntityManager::AddEntity(Entity* p_Entity,const char *p_sFileName,Vector3 &p_vPosition) {
	if(p_Entity!= NULL) {
		if(p_Entity->GetProperty<const char>("type")=="Cube") {
			RenderNode* node=new RenderNode;
			node->mpMesh=mRenderSystem->CreateMesh();
			MeshUtils::CreateMeshFromObj(p_sFileName,node->mpMesh);
			node->mpTexture=mRenderSystem->CreateTexture();
			node->mpTexture->Create("../data/textures/tile1x1m.png");
			node->CalculateBoundingVolume();
			p_Entity->init(node,p_vPosition);
			m_apxEntities.push_back(p_Entity);
			return;
		}
	};
};
