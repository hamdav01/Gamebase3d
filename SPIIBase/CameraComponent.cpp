// CameraComponent.cpp //
#include "stdafx.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "Entity.h"
#include "MessageSystem.h"
#include "RenderNode.h"

CameraComponent::CameraComponent(Camera *cam) {
	mCamera=cam;
};
CameraComponent::CameraComponent() {
};

CameraComponent::~CameraComponent() {
	delete mCamera;
	mCamera=NULL;
};

void CameraComponent::OnInit(Entity *pParent) {
	mpParent=pParent;
	m_vPosition=mpParent->GetProperty<Vector3>("Position");
	mCamera;
	mpParent->mMessageSystem->RegisterCallback<CameraComponent>("MoveRight",this,&CameraComponent::MoveRight);
	mpParent->mMessageSystem->RegisterCallback<CameraComponent>("MoveLeft",this,&CameraComponent::MoveLeft);
	mpParent->mMessageSystem->RegisterCallback<CameraComponent>("MoveForward",this,&CameraComponent::MoveForward);
	mpParent->mMessageSystem->RegisterCallback<CameraComponent>("MoveBack",this,&CameraComponent::MoveBack);
};
void CameraComponent::OnUpdate(float deltatime) {
};
void CameraComponent::VOnInit() {
};

void CameraComponent::MoveRight(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	mCamera->MoveX(0.1f);
	m_vPosition->x+=0.1f;
	node->moveNode(m_vPosition);
};
void CameraComponent::MoveLeft(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	mCamera->MoveX(-0.1f);
	m_vPosition->x-=0.1f;
	node->moveNode(m_vPosition);
};
void CameraComponent::MoveForward(class IMessage* p_Message){
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	mCamera->MoveZ(0.1f);
	m_vPosition->z+=0.1f;
	node->moveNode(m_vPosition);
};
void CameraComponent::MoveBack(class IMessage* p_Message) {
	RenderNode* node = mpParent->GetProperty<RenderNode>("RenderNode");
	mCamera->MoveZ(-0.1);
	m_vPosition->z-=0.1f;
	node->moveNode(m_vPosition);
};
