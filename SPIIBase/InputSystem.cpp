// InputSystem.cpp

#include "stdafx.h"
#include "InputSystem.h"

std::map<u32,KeyCode> InputSystem::mKeyCodeConvert;
bool InputSystem::mIsInit=false;

InputSystem::InputSystem()
{
	mIsIgnoreOn=false;
	mLockMouseInput=false;
	if(!mIsInit)
	{
		mIsInit=true;

		mKeyCodeConvert[VK_BACK] = KC_Backspace;
		mKeyCodeConvert[VK_TAB] = KC_Tab;
		mKeyCodeConvert[VK_RETURN] = KC_Return;
		mKeyCodeConvert[VK_PAUSE] = KC_Pause;
		mKeyCodeConvert[VK_ESCAPE] = KC_Escape;
		mKeyCodeConvert[VK_SPACE] = KC_Space;
		mKeyCodeConvert[VK_PRIOR] = KC_Pageup;
		mKeyCodeConvert[VK_NEXT] = KC_Pagedown;
		mKeyCodeConvert[VK_END] = KC_End;
		mKeyCodeConvert[VK_HOME] = KC_Home;
		mKeyCodeConvert[VK_LEFT] = KC_Left;
		mKeyCodeConvert[VK_UP] = KC_Up;
		mKeyCodeConvert[VK_RIGHT] = KC_Right;
		mKeyCodeConvert[VK_DOWN] = KC_Down;
		mKeyCodeConvert[VK_SNAPSHOT] = KC_Printscreen;
		mKeyCodeConvert[VK_INSERT] = KC_Insert;
		mKeyCodeConvert[VK_DELETE] = KC_Delete;
	
		mKeyCodeConvert['0'] = KC_0;
		mKeyCodeConvert['1'] = KC_1;
		mKeyCodeConvert['2'] = KC_2;
		mKeyCodeConvert['3'] = KC_3;
		mKeyCodeConvert['4'] = KC_4;
		mKeyCodeConvert['5'] = KC_5;
		mKeyCodeConvert['6'] = KC_6;
		mKeyCodeConvert['7'] = KC_7;
		mKeyCodeConvert['8'] = KC_8;
		mKeyCodeConvert['9'] = KC_9;

		mKeyCodeConvert['A'] = KC_a;
		mKeyCodeConvert['B'] = KC_b;
		mKeyCodeConvert['C'] = KC_c;
		mKeyCodeConvert['D'] = KC_d;
		mKeyCodeConvert['E'] = KC_e;
		mKeyCodeConvert['F'] = KC_f;
		mKeyCodeConvert['G'] = KC_g;
		mKeyCodeConvert['H'] = KC_h;
		mKeyCodeConvert['I'] = KC_i;
		mKeyCodeConvert['J'] = KC_j;
		mKeyCodeConvert['K'] = KC_k;
		mKeyCodeConvert['L'] = KC_l;
		mKeyCodeConvert['M'] = KC_m;
		mKeyCodeConvert['N'] = KC_n;
		mKeyCodeConvert['O'] = KC_o;
		mKeyCodeConvert['P'] = KC_p;
		mKeyCodeConvert['Q'] = KC_q;
		mKeyCodeConvert['R'] = KC_r;
		mKeyCodeConvert['S'] = KC_s;
		mKeyCodeConvert['T'] = KC_t;
		mKeyCodeConvert['U'] = KC_u;
		mKeyCodeConvert['V'] = KC_v;
		mKeyCodeConvert['W'] = KC_w;
		mKeyCodeConvert['X'] = KC_x;
		mKeyCodeConvert['Y'] = KC_y;
		mKeyCodeConvert['Z'] = KC_z;

		mKeyCodeConvert[VK_LWIN] = KC_LeftWin;
		mKeyCodeConvert[VK_RWIN] = KC_RightWin;
		mKeyCodeConvert[VK_APPS] = KC_Apps;
		mKeyCodeConvert[VK_NUMPAD0] = KC_Numpad0;
		mKeyCodeConvert[VK_NUMPAD1] = KC_Numpad1;
		mKeyCodeConvert[VK_NUMPAD2] = KC_Numpad2;
		mKeyCodeConvert[VK_NUMPAD3] = KC_Numpad3;
		mKeyCodeConvert[VK_NUMPAD4] = KC_Numpad4;
		mKeyCodeConvert[VK_NUMPAD5] = KC_Numpad5;
		mKeyCodeConvert[VK_NUMPAD6] = KC_Numpad6;
		mKeyCodeConvert[VK_NUMPAD7] = KC_Numpad7;
		mKeyCodeConvert[VK_NUMPAD8] = KC_Numpad8;
		mKeyCodeConvert[VK_NUMPAD9] = KC_Numpad9;
		mKeyCodeConvert[VK_MULTIPLY] = KC_NumpadMultiply;
		mKeyCodeConvert[VK_ADD] = KC_NumpadAdd;
		mKeyCodeConvert[VK_SEPARATOR] = KC_NumpadSeparator;
		mKeyCodeConvert[VK_SUBTRACT] = KC_NumpadSubtract;
		mKeyCodeConvert[VK_DECIMAL] = KC_NumpadDecimal;
		mKeyCodeConvert[VK_DIVIDE] = KC_NumpadDivide;

		mKeyCodeConvert[VK_F1] = KC_F1;
		mKeyCodeConvert[VK_F2] = KC_F2;
		mKeyCodeConvert[VK_F3] = KC_F3;
		mKeyCodeConvert[VK_F4] = KC_F4;
		mKeyCodeConvert[VK_F5] = KC_F5;
		mKeyCodeConvert[VK_F6] = KC_F6;
		mKeyCodeConvert[VK_F7] = KC_F7;
		mKeyCodeConvert[VK_F8] = KC_F8;
		mKeyCodeConvert[VK_F9] = KC_F9;
		mKeyCodeConvert[VK_F10] = KC_F10;
		mKeyCodeConvert[VK_F11] = KC_F11;
		mKeyCodeConvert[VK_F12] = KC_F12;
		mKeyCodeConvert[VK_F13] = KC_F13;
		mKeyCodeConvert[VK_F14] = KC_F14;
		mKeyCodeConvert[VK_F15] = KC_F15;

		mKeyCodeConvert[VK_NUMLOCK] = KC_Numlock;
		mKeyCodeConvert[VK_SCROLL] = KC_ScrollLock;

		mKeyCodeConvert[VK_LSHIFT] = KC_LeftShift;
		mKeyCodeConvert[VK_RSHIFT] = KC_RightShift;
		mKeyCodeConvert[VK_LCONTROL] = KC_LeftControl;
		mKeyCodeConvert[VK_RCONTROL] = KC_RightControl;
		mKeyCodeConvert[VK_LMENU] = KC_LeftAlt;
		mKeyCodeConvert[VK_RMENU] = KC_RightAlt;
	};

	mMouseX=0;
	mMouseY=0;
	mLoops=0;
};

void InputSystem::Exit()
{
	//Utils::DeleteVectorElements(mKeyboardListeners);
	//Utils::DeleteVectorElements(mMouseListeners);
	//Utils::DeleteVectorElements(mTextInputListeners);
};

void InputSystem::PostUpdate()
{
	u32 iC=mKeyboardListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mKeyboardListeners[i]->postUpdate();
	};
	iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->postUpdate();
	};
};

void InputSystem::RegisterKeyboardListener(BasicKeyboardListener* pListener)
{
	mKeyboardListeners.push_back(pListener);
};

void InputSystem::RegisterMouseListener(BasicMouseListener *pListener)
{
	mMouseListeners.push_back(pListener);
};

void InputSystem::RegisterTextInputListener(BasicTextInputListener<u8> *pListener)
{
	mTextInputListeners.push_back(pListener);
};

void InputSystem::UnregisterKeyboardListener(BasicKeyboardListener *pListener)
{
	std::vector<BasicKeyboardListener*>::iterator it=mKeyboardListeners.begin();
	while(it!=mKeyboardListeners.end())
	{
		if((*it)==pListener)
		{
			mKeyboardListeners.erase(it);
			break;
		};
		++it;
	};
};

void InputSystem::UnregisterMouseListener(BasicMouseListener *pListener)
{
	std::vector<BasicMouseListener*>::iterator it=mMouseListeners.begin();
	while(it!=mMouseListeners.end())
	{
		if((*it)==pListener)
		{
			mMouseListeners.erase(it);
			break;
		};
		++it;
	};
};

void InputSystem::UnregisterTextInputListener(BasicTextInputListener<u8> *pListener)
{
	std::vector<BasicTextInputListener<u8>*>::iterator it=mTextInputListeners.begin();
	while(it!=mTextInputListeners.end())
	{
		if((*it)==pListener)
		{
			mTextInputListeners.erase(it);
			break;
		};
		++it;
	};
};


void InputSystem::OnKeyDown(u32 wParam,u32 lParam)
{
	if(mKeyboardListeners.empty()||mIsIgnoreOn) {return;};
	u32 key=0;
	key=(wParam&0xffff);
	KeyCode kc=keyCodeConvert(key);

	u32 iC=mKeyboardListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mKeyboardListeners[i]->mKeysCurr[kc]=true;
	};
};

void InputSystem::OnKeyUp(u32 wParam,u32 lParam)
{
	if(mKeyboardListeners.empty()||mIsIgnoreOn) {return;};
	u32 key=0;
	key=(wParam&0xffff);
	KeyCode kc=keyCodeConvert(key);

	u32 iC=mKeyboardListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mKeyboardListeners[i]->mKeysCurr[kc]=false;
	};
};

void InputSystem::OnChar(u32 wParam,u32 lParam)
{
	if(mTextInputListeners.empty()||mIsIgnoreOn) {return;};
	u8 key=wParam;
	//mCharBuffer+=(key);
};

void InputSystem::OnMouseMove(u32 wParam,u32 lParam)
{
	// NOTE: Redo procedure to handle events for mousemove?
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	//if(mLockMouseInput) {return;};

	s32 iX=LOWORD(lParam),iY=HIWORD(lParam);
	mMouseX=iX;	mMouseY=iY;
	if(mMouseX>12345||mMouseX<-12345)
	{
		int asd=0;
	};

	//printf("InputSystem: %d/%d",iX,iY);

	mLoops++;

	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mDX=iX-mMouseListeners[i]->mX;
		mMouseListeners[i]->mDY=iY-mMouseListeners[i]->mY;
		mMouseListeners[i]->mX=iX;
		mMouseListeners[i]->mY=iY;

		//printf(" : [%d/%d]",mMouseListeners[i]->mDX,mMouseListeners[i]->mDY);
	};
	//printf("\n");
};

void InputSystem::OnMouseWheel(u32 wParam,u32 lParam)
{
	// void
};

void InputSystem::OnLMouseButtonDown(u32 wParam,u32 lParam)
{
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mButtons[MB_Left]=true;
	};
};

void InputSystem::OnLMouseButtonUp(u32 wParam,u32 lParam)
{
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mButtons[MB_Left]=false;
	};
};

void InputSystem::OnRMouseButtonDown(u32 wParam,u32 lParam)
{
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mButtons[MB_Right]=true;
	};
};

void InputSystem::OnRMouseButtonUp(u32 wParam,u32 lParam)
{
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mButtons[MB_Right]=false;
	};
};

void InputSystem::OnMMouseButtonDown(u32 wParam,u32 lParam)
{
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mButtons[MB_Middle]=true;
	};
};

void InputSystem::OnMMouseButtonUp(u32 wParam,u32 lParam)
{
	if(mMouseListeners.empty()||mIsIgnoreOn) {return;}
	u32 iC=mMouseListeners.size();
	for(u32 i=0;i<iC;i++)
	{
		mMouseListeners[i]->mButtons[MB_Middle]=false;
	};
};

void InputSystem::OnRawInput(u32 wParam,u32 lParam)
{
	// void
};

KeyCode InputSystem::keyCodeConvert(u32 key)
{
	std::map<u32,KeyCode>::iterator it=mKeyCodeConvert.find(key);
	if(it==mKeyCodeConvert.end()) {return KC_Invalid;};
	return it->second;
};

void InputSystem::SetIgnoreInput(bool state)
{
	mIsIgnoreOn=state;
};

void InputSystem::LockMouseInput(bool state)
{
	if(mLockMouseInput!=state)
	{
	};
	mLockMouseInput=state;
};
