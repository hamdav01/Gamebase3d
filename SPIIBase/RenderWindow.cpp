// RenderWindow.cpp

#include "stdafx.h"
#include "RenderWindow.h"

RenderWindow::RenderWindow()
	: mWndParams(800,600,false)
{
	mWnd=NULL;
	mEventLut[WM_CHAR] = (u32)EVT_CHAR;
	mEventLut[WM_SETFOCUS] = (u32)EVT_FOCUS;
	mEventLut[WM_MOVE] = (u32)EVT_MOVE;
	mEventLut[WM_DESTROY] = (u32)EVT_DESTROY;
	mEventLut[WM_CREATE] = (u32)EVT_CREATE;	
	mEventLut[WM_SIZE] = (u32)EVT_SIZE;
	mEventLut[WM_INPUT] = (u32)EVT_INPUT;
	mEventLut[WM_QUIT] = (u32)EVT_QUIT;
	mEventLut[WM_CLOSE] = (u32)EVT_CLOSE;
	mEventLut[WM_KEYUP]	= (u32)EVT_KEYUP;
	mEventLut[WM_KEYDOWN] = (u32)EVT_KEYDOWN;
	mEventLut[WM_RBUTTONUP]	= (u32)EVT_MOUSEBUTTONUP_RIGHT;	
	mEventLut[WM_LBUTTONDOWN] = (u32)EVT_MOUSEBUTTONDOWN_LEFT;
	mEventLut[WM_MOUSEMOVE]	= (u32)EVT_MOUSEMOTION;
	mEventLut[WM_LBUTTONUP]	= (u32)EVT_MOUSEBUTTONUP_LEFT;
	mEventLut[WM_RBUTTONDOWN] = (u32)EVT_MOUSEBUTTONDOWN_RIGHT;
	mEventLut[WM_MBUTTONUP] = (u32)EVT_MOUSEBUTTONUP_MIDDLE;
	mEventLut[WM_MBUTTONDOWN] = (u32)EVT_MOUSEBUTTONDOWN_MIDDLE;
	mEventLut[WM_ENTERSIZEMOVE]	= (u32)EVT_ENTERSIZEMOVE;
	mEventLut[WM_EXITSIZEMOVE]	= (u32)EVT_EXITSIZEMOVE;

	mIsCursorLocked=false;
	mIsCursorVisible=true;
};

RenderWindow::~RenderWindow()
{
	Exit();
};

bool RenderWindow::Init(const WindowParams &params)
{
	mWndParams=params;

	WNDCLASSEX wc={sizeof(WNDCLASSEX),CS_CLASSDC,(WNDPROC)staticWindowProc,0,0,::GetModuleHandle(NULL),NULL,::LoadCursor(NULL,IDC_ARROW),NULL,NULL,"spiiRenderWindow",NULL};
	::RegisterClassEx(&wc);

	RECT cr={100,200,100+mWndParams.mWidth,200+mWndParams.mHeight};
	u32 wndSt=(WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME|WS_MAXIMIZEBOX));
	::AdjustWindowRect(&cr,wndSt,FALSE);

	mWnd=::CreateWindowEx(0,"spiiRenderWindow","spiiRenderWindow",wndSt,cr.left,cr.top,cr.right-cr.left,cr.bottom-cr.top,NULL,NULL,wc.hInstance,NULL);

	mWndDiffX=::GetSystemMetrics(SM_CXFIXEDFRAME);
	mWndDiffY=::GetSystemMetrics(SM_CYFIXEDFRAME)+::GetSystemMetrics(SM_CYCAPTION);

	if(mWnd==NULL)
	{
		return false;
	};

	::SetWindowLongPtr(mWnd,GWLP_USERDATA,(LONG_PTR)this);
	::ShowWindow(mWnd,SW_SHOW);

	return true;
};

void RenderWindow::Exit()
{
	if(mWnd!=NULL)
	{
		::DestroyWindow(mWnd);
		mWnd=NULL;
	};
	if(!mCallbacks.empty())
	{
		std::map<u32,std::vector<IEventCallback*>>::iterator itB=mCallbacks.begin();
		while(itB!=mCallbacks.end())
		{
			for(u32 i=0;i<itB->second.size();i++)
			{
				delete itB->second.at(i);
			};
			itB->second.clear();
			++itB;
		};
		mCallbacks.clear();
	};
};

bool RenderWindow::Update()
{
	MSG msg={0};
	while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		if(msg.message==WM_QUIT)
		{
			return false;
		};
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	};

	if(mIsCursorLocked)
	{
		lockCursor();
	};

	return true;
};

HWND RenderWindow::GetHandle()
{
	return mWnd;
};

WindowParams &RenderWindow::GetParams()
{
	return mWndParams;
};

void RenderWindow::SetCaption(const String &caption)
{
	::SetWindowText(mWnd,caption.c_str());
};

void RenderWindow::SetCursorVisibility(bool state)
{
	if(state!=mIsCursorVisible)
	{
		while(::ShowCursor(state?TRUE:FALSE)>0) {};
		mIsCursorVisible=state;
	};
};

void RenderWindow::SetCursorPosition(s32 x,s32 y)
{
	RECT wr={0};
	RECT cr={0};
	::GetWindowRect(mWnd,&wr);
	::GetClientRect(mWnd,&cr);
	::SetCursorPos(wr.left+x,wr.top+y);
};

void RenderWindow::SetCursorLock(bool state)
{
	mIsCursorLocked=state;
	if(!mIsCursorLocked)
	{
		::ClipCursor(NULL);
	}
	else
	{
		RECT wr={0};
		::GetWindowRect(mWnd,&wr);
		::ClipCursor(&wr);
		lockCursor();
	};
};

void RenderWindow::Unregister(u32 evt,void *pObj)
{
	std::map<u32,std::vector<IEventCallback*>>::iterator it=mCallbacks.find(evt);
	if(it==mCallbacks.end())
	{
		return;
	};

	std::vector<IEventCallback*>::iterator itVB=it->second.begin();
	std::vector<IEventCallback*>::iterator itVE=it->second.end();
	while(itVB!=itVE)
	{
		if((*itVB)->Compare(pObj))
		{
			delete pObj;
			it->second.erase(itVB);
			break;
		};
		++itVB;
	};
};

// private
LRESULT CALLBACK RenderWindow::staticWindowProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg==WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	};
	RenderWindow *pThis=NULL;
	pThis=(RenderWindow*)::GetWindowLongPtr(hWnd,GWLP_USERDATA);
	if(pThis!=NULL)
	{
		if(msg==WM_MOUSEMOVE)
		{
			pThis->mainWindowProc(msg,wParam,lParam);
			return 0;
		}
		else
		{
			pThis->mainWindowProc(msg,wParam,lParam);
		};
	};

	return ::DefWindowProc(hWnd,msg,wParam,lParam);
};

long long RenderWindow::mainWindowProc(u32 msg,u32 wParam,u32 lParam)
{
	std::map<u32,u32>::iterator itL=mEventLut.find(msg);
	if(itL==mEventLut.end())
	{
		// TODO: Add all WM_ events? (Need to add all window events?)
		return 0;
	};
	
	std::map<u32,std::vector<IEventCallback*>>::iterator it=mCallbacks.find(itL->second);
	if(it==mCallbacks.end())
	{
		return 0;
	};
	u32 count=it->second.size();
	for(u32 i=0;i<count;i++)
	{
		it->second.at(i)->Invoke(wParam,lParam);
	};
	return 0;
};

void RenderWindow::lockCursor()
{
	RECT cr={0};
	RECT wr={0};
	::GetClientRect(mWnd,&cr);
	::GetWindowRect(mWnd,&wr);
	POINT pt={wr.left+cr.right/2,wr.top+cr.bottom/2};

	POINT mt={0};
	::GetCursorPos(&mt);
	::ScreenToClient(mWnd,&mt);
	s32 x=mt.x;//-wr.left;
	s32 y=mt.y;//-wr.top;

	s32 lParam=MAKELONG(x,y);
	//printf("RenderWindow: %d/%d (%d/%d)\n",x,y,mt.x,mt.y);
	//::SendMessageA(mWnd,WM_MOUSEMOVE,0,(LPARAM)MAKELONG(x,y));

	//::ScreenToClient(mWnd,&pt);
	//::SetCursorPos(pt.x,pt.y);
	//::GetCursorPos(&mp);
	//mouse_event(MOUSEEVENTF_ABSOLUTE,pt.x,pt.y,0,0);
};
