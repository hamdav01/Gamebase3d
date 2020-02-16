// RenderWindowPrereq.h

#ifndef RENDERWINDOWPREREQ_H_INCLUDED
#define RENDERWINDOWPREREQ_H_INCLUDED

enum WndEvt
{
	EVT_INVALID,
	EVT_CREATE,
	EVT_DESTROY,
	EVT_MOVE,
	EVT_ENTERSIZEMOVE,
	EVT_SIZE,
	EVT_EXITSIZEMOVE,
	EVT_FOCUS,
	EVT_CLOSE,
	EVT_QUIT,
	EVT_INPUT,

	EVT_MOUSEMOTION,
	EVT_MOUSEBUTTONDOWN_LEFT,
	EVT_MOUSEBUTTONUP_LEFT,
	EVT_MOUSEBUTTONDOWN_RIGHT,
	EVT_MOUSEBUTTONUP_RIGHT,
	EVT_MOUSEBUTTONDOWN_MIDDLE,
	EVT_MOUSEBUTTONUP_MIDDLE,

	EVT_KEYDOWN,
	EVT_KEYUP,
	EVT_CHAR,

	EVT_COUNT,
};

class IEventCallback
{
public:
	virtual ~IEventCallback() {};
	virtual void Invoke(u32,u32) = 0;
	virtual bool Compare(void*) = 0;
};

template <class T>
class EventCallback : public IEventCallback
{
	T *mpObj; void(T::*mpFnc)(u32,u32);
public:
	EventCallback(T *pObj,void(T::*pFnc)(u32,u32)) : mpObj(pObj), mpFnc(pFnc) {};
	void Invoke(u32 x,u32 y) {(*mpObj.*mpFnc)(x,y);};
	bool Compare(void *pObj) {return mpObj==pObj;};
};


// -helper classes-
struct WindowParams
{
	WindowParams(u32 w,u32 h,bool fs) {mWidth=w;mHeight=h;mFullscreen=fs;};
	u32 mWidth,mHeight;
	bool mFullscreen;
};

#endif // RENDERWINDOWPREREQ_H_INCLUDED
