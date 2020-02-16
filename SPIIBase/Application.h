// Application.h

#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "RenderWindow.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "SystemUtils.h"

class Application
{
public:
	Application();
	virtual ~Application();

	void Init();
	void Exit();
	void Run();

protected:
	virtual void OnInit() = 0;
	virtual void OnExit() = 0;
	virtual void OnRun() = 0;

protected:
	bool mIsRunning;
	OSSystem mSystem;
	RenderWindow mRenderWindow;
	RenderSystem mRenderSystem;
	InputSystem mInputSystem;
};

#endif // APPLICATION_H_INCLUDED
