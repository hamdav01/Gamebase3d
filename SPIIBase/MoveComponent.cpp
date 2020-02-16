// MoveComponent.cpp //
#include "stdafx.h"
#include "Entity.h"
#include "MoveComponent.h"
#include "MessageSystem.h"
#include "IMessage.h"
#include "RenderNode.h"

MoveComponent::MoveComponent() {
};
MoveComponent::~MoveComponent() {
};
void MoveComponent::OnInit(Entity *pParent) {
	mpParent=pParent;
	m_vPosition = mpParent->GetProperty<Vector3>("Position");
	mpParent->mMessageSystem->RegisterCallback<MoveComponent>("MoveRight",this,&MoveComponent::MoveRight);
	mpParent->mMessageSystem->RegisterCallback<MoveComponent>("MoveLeft",this,&MoveComponent::MoveLeft);
	mpParent->mMessageSystem->RegisterCallback<MoveComponent>("MoveForward",this,&MoveComponent::MoveForward);
	mpParent->mMessageSystem->RegisterCallback<MoveComponent>("MoveBack",this,&MoveComponent::MoveBack);
};
void MoveComponent::VOnInit() {
};
void MoveComponent::OnUpdate(float p_deltatime) {
	
};
void MoveComponent::MoveRight(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	m_vPosition->x+=0.01;
	node->moveNode(m_vPosition);
};
void MoveComponent::MoveLeft(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	m_vPosition->x-=1;
	node->moveNode(m_vPosition);
};
void MoveComponent::MoveForward(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	m_vPosition->z+=1;
	node->moveNode(m_vPosition);
};
void MoveComponent::MoveBack(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	m_vPosition->z-=1;
	node->moveNode(m_vPosition);
};