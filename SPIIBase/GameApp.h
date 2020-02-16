// GameApp.h

#ifndef GAMEAPP_H_INCLUDED
#define GAMEAPP_H_INCLUDED

#include "Application.h"
class EntityManager;
class Entity;

class GameApp : public Application {
public:
	GameApp();
	~GameApp();

protected:
	void OnInit();
	void OnExit();
	void OnRun();

private:
	Entity *mEntity;
	OrthoNode *mpGui;
	RenderNode *mpCube;
	RenderNode *mpSkybox;
	RenderNode *mpHeightmap;
	EntityManager* entityManager;
	BasicKeyboardListener mKeyboard;
	BasicMouseListener mMouse;

};

#endif // GAMEAPP_H_INCLUDED
