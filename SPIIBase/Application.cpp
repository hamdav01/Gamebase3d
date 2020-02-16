// Application.cpp

#include "stdafx.h"
#include "Application.h"

Application::Application()
{
	mIsRunning=true;
};

Application::~Application()
{
};

void Application::Init()
{
	mSystem.Init();
	mRenderWindow.Init(WindowParams(1024,640,false));
	if(!mRenderSystem.Init(&mRenderWindow))
	{
#ifdef _DEBUG
		printf("ERROR: Could not init rendersystem!\n");
#endif
	};
	
	mRenderWindow.Register(EVT_KEYDOWN,&mInputSystem,&InputSystem::OnKeyDown);
	mRenderWindow.Register(EVT_KEYUP,&mInputSystem,&InputSystem::OnKeyUp);
	mRenderWindow.Register(EVT_CHAR,&mInputSystem,&InputSystem::OnChar);
	mRenderWindow.Register(EVT_MOUSEMOTION,&mInputSystem,&InputSystem::OnMouseMove);
	mRenderWindow.Register(EVT_MOUSEBUTTONDOWN_LEFT,&mInputSystem,&InputSystem::OnLMouseButtonDown);
	mRenderWindow.Register(EVT_MOUSEBUTTONDOWN_RIGHT,&mInputSystem,&InputSystem::OnRMouseButtonDown);
	mRenderWindow.Register(EVT_MOUSEBUTTONDOWN_MIDDLE,&mInputSystem,&InputSystem::OnMMouseButtonDown);
	mRenderWindow.Register(EVT_MOUSEBUTTONUP_LEFT,&mInputSystem,&InputSystem::OnLMouseButtonUp);
	mRenderWindow.Register(EVT_MOUSEBUTTONUP_RIGHT,&mInputSystem,&InputSystem::OnRMouseButtonUp);
	mRenderWindow.Register(EVT_MOUSEBUTTONUP_MIDDLE,&mInputSystem,&InputSystem::OnMMouseButtonUp);

	OnInit();
};

void Application::Exit()
{
	OnExit();
	mInputSystem.Exit();
	mRenderSystem.Exit();
	mRenderWindow.Exit();
	mSystem.Exit();
};

void Application::Run()
{
	while(mIsRunning&&mRenderWindow.Update())
	{
		mSystem.Update();
		mRenderSystem.PreRender();
		OnRun();
		mRenderSystem.PostRender();
		mInputSystem.PostUpdate();
	};
};
