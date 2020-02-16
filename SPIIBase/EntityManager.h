// EntityManager.h //
// A class that holds,renders,destroys,creates, send collisions check calls and updates all the entities in the scene. //
#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include "stdafx.h"

class Entity;
class RenderSystem;

class EntityManager
{
public:
	EntityManager(RenderSystem* p_pxRenderSystem);
	~EntityManager();
	void Update(float p_fDeltaTime);
	void ResetEntity(); // Resets all the entites to their start position.
	void DestroyEntity(Entity *p_pxEntity);  // Destroy specific entity.
	void Render(); // Renders the entity.
	void Collision(); // Checks collision between all entities.
	void DestroyAll(); // Destroys all the entities in the current scene.
	void AddEntity(Entity* p_Entity,const char *p_sFileName,Vector3 &p_vPosition);
private:
	std::vector<Entity*> m_apxEntities; // Vector with all the entities created.
	RenderSystem* mRenderSystem;
};

#endif
