// RenderWindow.h

#ifndef RENDERWINDOW_H_INCLUDED
#define RENDERWINDOW_H_INCLUDED

#include "RenderWindowPrereq.h"

class RenderWindow
{
public:
	RenderWindow();
	virtual ~RenderWindow();

	bool Init(const WindowParams &params);
	void Exit();
	bool Update();

	HWND GetHandle();
	WindowParams &GetParams();
	void SetCaption(const String &caption);
	void SetCursorVisibility(bool state);
	void SetCursorPosition(s32 x,s32 y);
	void SetCursorLock(bool state);

	void Unregister(u32 evt,void *pObj);
	template <class T>
	void Register(u32 evt,T *pObj,void(T::*pFnc)(u32,u32))
	{
		std::map<u32,std::vector<IEventCallback*>>::iterator it=mCallbacks.find(evt);
		if(it==mCallbacks.end())
		{
			mCallbacks.insert(std::make_pair<u32,std::vector<IEventCallback*>>(evt,std::vector<IEventCallback*>()));
			it=mCallbacks.find(evt);
		};
		it->second.push_back(new EventCallback<T>(pObj,pFnc));
	};

private:
	static LRESULT CALLBACK staticWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
	long long mainWindowProc(u32 msg,u32 wParam,u32 lParam);

private:
	void lockCursor();

protected:
	std::map<u32,u32> mEventLut;
	std::map<u32,std::vector<IEventCallback*>> mCallbacks;
	WindowParams mWndParams;
	HWND mWnd;

	bool mIsCursorVisible;
	bool mIsCursorLocked;
	s32 mWndDiffX,mWndDiffY;
};

#endif // RENDERWINDOW_H_INCLUDED
