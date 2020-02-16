// GameApp.cpp

#include "stdafx.h"
#include "Camera.h"
#include "RenderSystem.h"
#include "RenderNode.h"
#include "Mesh.h"
#include "MeshUtils.h"
#include "Texture.h"
#include "GameApp.h"
#include "Factory.h"
#include "Entity.h"
#include "EntityManager.h"
#include "InputComponent.h"
#include "CameraComponent.h"

GameApp::GameApp() : Application() {
	mpHeightmap=NULL;
	mpCube=NULL;
	entityManager = new EntityManager(&mRenderSystem);
};

GameApp::~GameApp() {
};

void GameApp::OnInit() {
	mInputSystem.RegisterKeyboardListener(&mKeyboard);
	mInputSystem.RegisterMouseListener(&mMouse);

	/*mpHeightmap=new RenderNode;
	mpHeightmap->mpMesh=mRenderSystem.CreateMesh();
	MeshUtils::CreateHeightmapFromBmp("../data/textures/heightmap01.bmp",mpHeightmap->mpMesh);
	mpHeightmap->mpTexture=mRenderSystem.CreateTexture();
	mpHeightmap->mpTexture->Create("../data/textures/tile1x1m.png");
	mpHeightmap->CalculateBoundingVolume();*/
	
	mpSkybox=new RenderNode;
	mpSkybox->mpMesh=mRenderSystem.CreateMesh();
	MeshUtils::CreateSkybox(mpSkybox->mpMesh);
	mpSkybox->mpTexture=mRenderSystem.CreateTexture();
	mpSkybox->mpTexture->Create("../data/textures/skybox.png");

	mRenderSystem.SetSkybox(mpSkybox);
	/*mpGui=new OrthoNode;
	mpGui->mpTexture=mpHeightmap->mpTexture;
	mpGui->mPosition=Vector4(10,10,256,256);
	mpGui->mTexCoords=Vector4(0,0,1,1);*/

	Entity* ent = new Entity();

	entityManager->AddEntity(ent,"../data/Meshes/cube.obj",D3DXVECTOR3(0,0,0));
	/*InputComponent* INPUTcomponent = new InputComponent(&mInputSystem);
	Camera *pCam=mRenderSystem.GetCamera();
	CameraComponent* camera = new CameraComponent(pCam);*/
	ent->AttachComponent(new CameraComponent(mRenderSystem.GetCamera()));
	ent->AttachComponent(new InputComponent(&mInputSystem));

	/*mpCube=new RenderNode;
	mpCube->mpMesh=mRenderSystem.CreateMesh();
	MeshUtils::CreateMeshFromObj("../data/Meshes/cube.obj",mpCube->mpMesh);
	mpCube->mpTexture=mRenderSystem.CreateTexture();
	mpCube->mpTexture->Create("../data/textures/tile1x1m.png");
	mpCube->CalculateBoundingVolume();*/
};

void GameApp::OnExit() {
	if(mpHeightmap!=NULL){
		delete mpHeightmap;
		mpHeightmap=NULL;
	};

	mInputSystem.UnregisterKeyboardListener(&mKeyboard);
	mInputSystem.UnregisterMouseListener(&mMouse);
};

void GameApp::OnRun() {
	if(mKeyboard.IsKeyDown(KC_Escape)) {
		mIsRunning=false;
	};

	Camera *pCam=mRenderSystem.GetCamera();
	f32 delta_time=Timer::LowResDeltaS(),camera_speed=50.0f;
	if(mMouse.IsButtonDown(MB_Right)) {
		f32 mouse_sens=0.2f;

		s32 dx=mMouse.GetDX();
		s32 dy=mMouse.GetDY();
		if(dx!=0) {
			pCam->RotateY(dx*delta_time*mouse_sens);
		};
		if(dy!=0) {
			pCam->RotateX(dy*delta_time*mouse_sens);
		};
	};
	
	/*if(mKeyboard.IsKeyDown(KC_w)) {
		pCam->MoveZ(delta_time*camera_speed);
	};
	if(mKeyboard.IsKeyDown(KC_s)) {
		pCam->MoveZ(delta_time*-camera_speed);
	};

	if(mKeyboard.IsKeyDown(KC_a)) {
		pCam->MoveX(delta_time*-camera_speed);
	};
	if(mKeyboard.IsKeyDown(KC_d)) {
		pCam->MoveX(delta_time*camera_speed);
	};*/

	/*if(mRenderSystem.GetCamera()->IsInside(&mpHeightmap->mBoundingVolume)) {
		mRenderSystem.Render(mpHeightmap);
	};*/
	//mRenderSystem.Render(mpCube);
	entityManager->Render();
	entityManager->Update(delta_time);
	//mRenderSystem.Render(mpGui);
	if(mKeyboard.IsKeyDown(KC_t)) {
		//mpCube->moveNode(Vector3(0,0,0),3.5);
	}
	
	::Sleep(10);
};
