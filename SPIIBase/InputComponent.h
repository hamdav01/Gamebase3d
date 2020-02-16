// InputComponent.h //
#ifndef INPUTCOMPONENT_H_INCLUDED
#define INPUTCOMPONENT_H_INCLUDED
#include "IComponent.h"
#include "InputSystem.h"

class InputComponent : public IComponent {
public:
	InputComponent(InputSystem* pInputSystem);
	~InputComponent();
	void OnInit(Entity *pParent);
	void VOnInit();
	void OnUpdate(float);
private:
	InputSystem* mInputSystem;
	BasicKeyboardListener mKeyboard;
	BasicMouseListener mMouse;
};
#endif