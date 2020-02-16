// Entity.cpp //

#include "stdafx.h"
#include "Entity.h"
#include "RenderNode.h"
#include "MoveComponent.h"
#include "Message.h"
#include "MessageSystem.h"
#include <iostream>

Entity::Entity() {
	const char *type = "Cube";
	std::map<std::string,IProperty*>::iterator it=mProperties.find("type");
		if(it==mProperties.end()) {
			mProperties.insert(
				std::make_pair<std::string,IProperty*>(
					"type",new Property<const char>(type)));
		};
	mMessageSystem = new MessageSystem();
 };

Entity::~Entity() {
	delete mMessageSystem;
	mMessageSystem = NULL;
};

void Entity::init(RenderNode* p_pxRenderNode,Vector3 &p_vPosition) {
	
	mProperties.insert(
	std::make_pair<std::string,IProperty*>(
	"RenderNode",new Property<RenderNode>(p_pxRenderNode)));

	Vector3 *tempVec = new Vector3(p_vPosition.x,p_vPosition.y,p_vPosition.z);
	mProperties.insert(
	std::make_pair<std::string,IProperty*>(
	"Position",new Property<Vector3>(tempVec)));

	//AttachComponent(new MoveComponent());
};
void Entity::Update(float p_fDeltaTime) {
	std::vector<IComponent*>::iterator xIt=mpComponents.begin();
	for( ; xIt != mpComponents.end(); xIt++) {
		(*xIt)->OnUpdate(p_fDeltaTime);
	};
	mMessageSystem->Update(10);
};


void Entity::AttachComponent(IComponent *pComponent) {
	if(pComponent==NULL) {return;};
	pComponent->OnInit(this);
	mpComponents.push_back(pComponent);
};

