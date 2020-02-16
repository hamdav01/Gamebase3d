// InputSystemPrereq.cpp

#include "stdafx.h"
#include "InputSystemPrereq.h"

// keyboard
BasicKeyboardListener::BasicKeyboardListener()
{
	::memset(mKeysCurr,0,sizeof(mKeysCurr));
	::memset(mKeysPrev,0,sizeof(mKeysPrev));
};

bool BasicKeyboardListener::IsKeyDown(u32 key) const
{
	if(key>=KC_COUNT) {return false;};
	return mKeysCurr[key];
};

bool BasicKeyboardListener::IsKeyDownOnce(u32 key) const
{
	if(key>=KC_COUNT) {return false;};
	return mKeysCurr[key]&&!mKeysPrev[key];
};

void BasicKeyboardListener::postUpdate()
{
	::memcpy(mKeysPrev,mKeysCurr,sizeof(mKeysCurr));
};


// mouse
BasicMouseListener::BasicMouseListener()
{
	mX=mY=0;
	mDX=mDY=0;
	::memset(mButtons,0,sizeof(mButtons));
};

bool BasicMouseListener::IsButtonDown(u32 button) const
{
	if(button>=MB_COUNT) {return false;};
	return mButtons[button];
};

void BasicMouseListener::GetMousePosition(s32 &x,s32 y) {x=mX;y=mY;};
s32 BasicMouseListener::GetX() const {return mX;};
s32 BasicMouseListener::GetY() const {return mY;};
s32 BasicMouseListener::GetDX() const {return mDX;};
s32 BasicMouseListener::GetDY() const {return mDY;};

void BasicMouseListener::postUpdate()
{
	mDX=mDY=0;
};