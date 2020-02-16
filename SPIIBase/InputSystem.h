// InputSystem.h

#ifndef INPUTSYSTEM_H_INCLUDED
#define INPUTSYSTEM_H_INCLUDED

#include "InputSystemPrereq.h"

class InputSystem
{
public:
	InputSystem();

	void Exit();
	void PostUpdate();

	void RegisterKeyboardListener(BasicKeyboardListener* pListener);
	void RegisterMouseListener(BasicMouseListener *pListener);
	void RegisterTextInputListener(BasicTextInputListener<u8> *pListener);
	void UnregisterKeyboardListener(BasicKeyboardListener *pListener);
	void UnregisterMouseListener(BasicMouseListener *pListener);
	void UnregisterTextInputListener(BasicTextInputListener<u8> *pListener);

	void OnKeyDown(u32 wParam,u32 lParam);
	void OnKeyUp(u32 wParam,u32 lParam);
	void OnChar(u32 wParam,u32 lParam);
	void OnMouseMove(u32 wParam,u32 lParam);
	void OnMouseWheel(u32 wParam,u32 lParam);
	void OnLMouseButtonDown(u32 wParam,u32 lParam);
	void OnLMouseButtonUp(u32 wParam,u32 lParam);
	void OnRMouseButtonDown(u32 wParam,u32 lParam);
	void OnRMouseButtonUp(u32 wParam,u32 lParam);
	void OnMMouseButtonDown(u32 wParam,u32 lParam);
	void OnMMouseButtonUp(u32 wParam,u32 lParam);
	void OnRawInput(u32 wParam,u32 lParam);

	void SetIgnoreInput(bool state);
	void LockMouseInput(bool state);

private:
	static KeyCode keyCodeConvert(u32 key);

private:
	static bool mIsInit;
	static std::map<u32,KeyCode> mKeyCodeConvert;
	bool mIsIgnoreOn;
	bool mLockMouseInput;
	s32 mMouseX,mMouseY;
	std::vector<BasicKeyboardListener*> mKeyboardListeners;
	std::vector<BasicMouseListener*> mMouseListeners;
	std::vector<BasicTextInputListener<u8>*> mTextInputListeners;

	u32 mLoops;

	// -!!!Exper.!!!----
	//std::map<u32,std::vector<IKeyboardListener*>> mKeyboardListenersM;
};

#endif // INPUTSYSTEM_H_INCLUDED
