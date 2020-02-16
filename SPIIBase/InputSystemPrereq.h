// InputSystemPrereq.h

#ifndef INPUTSYSTEMPREREQ_H_INCLUDED
#define INPUTSYSTEMPREREQ_H_INCLUDED

#pragma warning(disable:4800)

#include "RenderWindowPrereq.h"

// enums
enum KeyCode
{
	KC_Invalid,
	KC_Backspace,KC_Tab,KC_Clear,KC_Return,KC_Pause,KC_Escape,KC_Space,KC_Pageup,KC_Pagedown,KC_End,KC_Home,KC_Left,KC_Up,KC_Right,KC_Down,KC_Select,KC_Print,KC_Execute,KC_Printscreen,KC_Insert,KC_Delete,
	KC_0,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,
	KC_a,KC_b,KC_c,KC_d,KC_e,KC_f,KC_g,KC_h,KC_i,KC_j,KC_k,KC_l,KC_m,KC_n,KC_o,KC_p,KC_q,KC_r,KC_s,KC_t,KC_u,KC_v,KC_w,KC_x,KC_y,KC_z,
	KC_LeftWin,KC_RightWin,KC_Apps,KC_Sleep,
	KC_Numpad0,KC_Numpad1,KC_Numpad2,KC_Numpad3,KC_Numpad4,KC_Numpad5,KC_Numpad6,KC_Numpad7,KC_Numpad8,KC_Numpad9,
	KC_NumpadMultiply,KC_NumpadAdd,KC_NumpadSeparator,KC_NumpadSubtract,KC_NumpadDecimal,KC_NumpadDivide,
	KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_F13,KC_F14,KC_F15,KC_F16,KC_F17,KC_F18,KC_F19,KC_F20,KC_F21,KC_F22,KC_F23,KC_F24,
	KC_Numlock,KC_ScrollLock,KC_LeftShift,KC_RightShift,KC_LeftControl,KC_RightControl,KC_LeftAlt,KC_RightAlt,
	KC_COUNT, 
};

enum KeyModifier
{
	KM_Zero,KM_Alt=1,KM_Ctrl=2,KM_Shift=4,
};

enum MouseButton
{
	MB_Left,MB_Right,MB_Middle,
	MB_User1,MB_User2,MB_User3,
	MB_COUNT,
};


// classes
class InputSystem;

#pragma pack(push)
#pragma pack(1)
struct Signal
{
	bool mActive;
	u8 mModifier;
};
#pragma pack(pop)

class BasicKeyboardListener
{
	friend class InputSystem;
public:
	BasicKeyboardListener();
	bool IsKeyDown(u32 key) const;
	bool IsKeyDownOnce(u32 key) const;

private:
	void postUpdate();

protected:
	bool mKeysCurr[KC_COUNT];
	bool mKeysPrev[KC_COUNT];
};

class BasicMouseListener
{
	friend class InputSystem;
public:
	BasicMouseListener();
	bool IsButtonDown(u32 button) const;
	void GetMousePosition(s32 &x,s32 y);
	s32 GetX() const;
	s32 GetY() const;
	s32 GetDX() const;
	s32 GetDY() const;

private:
	void postUpdate();

protected:
	s32 mX,mY,mDX,mDY;
	bool mButtons[MB_COUNT];
};

template <class T>
class BasicTextInputListener
{
	friend class InputSystem;
public:
	BasicTextInputListener() {};
	u32 Size() const {return mBuffer.size();};
	void Push(T c) {mBuffer.push_back(c);};
	bool Pop(T &c) {if(mBuffer.empty()) {c=0; return false;}; c=mBuffer.front(); mBuffer.pop_front(); return true;};

private:
	std::list<T> mBuffer;
};




// -!!!Experimental!!!-----------------------------------------------------------------
class Event
{
	friend class InputSystem;
	WndEvt mType;
public:
	Event(WndEvt evt) {mType=evt;};
	WndEvt GetType() const {return mType;};
};

class MouseEvent : public Event
{
	s32 mX,mY;
	u32 mButton;
	u32 mModifier;
public:
	enum {ME_Move,ME_Down,ME_Up,ME_DblClk};
	MouseEvent(WndEvt evt) : Event(evt) {};
	s32 GetX() const {return mX;};
	s32 GetY() const {return mY;};
	u32 GetButton() const {return mButton;};
	bool IsModifierPressed(u32 mod) {return (bool)(mModifier|mod);};
};

class KeyboardEvent : public Event
{
	KeyCode mKey;
	u32 mModifier;
public:
	enum {KE_Down,KE_Up};
	KeyboardEvent(WndEvt evt,KeyCode key,u32 mod) : Event(evt) {mKey=key;mModifier=mod;};
	KeyCode GetKey() const {mKey;};
	bool IsModifierPressed(u32 mod) {return (bool)(mModifier|mod);};
};


// interfaces and impl of callbacks
class IMouseListener
{
public:
	virtual ~IMouseListener() {};
	virtual void Invoke(MouseEvent &evt) = 0;
};

template <class T>
class MouseListener : public IMouseListener
{
	T *mpObj; void(T::*mpFnc)(MouseEvent&);
public:
	MouseListener(T *pObj,void(T::*mpFnc)(MouseEvent&)) : mpObj(pObj), mpFnc(pFnc) {};
	void Invoke(MouseEvent &evt) {(*mpObj.*mpFnc)(evt);};
};

class IKeyboardListener
{
public:
	virtual ~IKeyboardListener() {};
	virtual void Invoke(KeyboardEvent &evt) = 0;
};

template <class T>
class KeyboardListener : public IKeyboardListener
{
	T *mpObj; void(T::*mpFnc)(KeyboardEvent&);
public:
	KeyboardListener(T *pObj,void(T::*pFnc)(KeyboardEvent&)) : mpObj(pObj), mpFnc(pFnc) {};
	void Invoke(KeyboardEvent &evt) {(*mpObj.*mpFnc)(evt);};
};

#endif // INPUTSYSTEMPREREQ_H_INCLUDED
