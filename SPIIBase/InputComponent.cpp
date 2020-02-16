// InputComponent.cpp //

#include "stdafx.h"
#include "Entity.h"
#include "InputComponent.h"
#include "MessageSystem.h"
#include "Message.h"


InputComponent::InputComponent(InputSystem* pInputSystem) {
	mInputSystem = pInputSystem;
};

InputComponent::~InputComponent() {
	delete mInputSystem;
	mInputSystem = NULL;
	mInputSystem->UnregisterKeyboardListener(&mKeyboard);
	mInputSystem->UnregisterMouseListener(&mMouse);
};
void InputComponent::OnInit(Entity *pParent) {
	mpParent=pParent;
	mInputSystem->RegisterKeyboardListener(&mKeyboard);
	mInputSystem->RegisterMouseListener(&mMouse);

};
void InputComponent::VOnInit() {
};
void InputComponent::OnUpdate(float deltatime) {

	if(mKeyboard.IsKeyDown(KC_w)) {
		mpParent->mMessageSystem->Enqueue(new Message("MoveForward",PRIO_HIGH));
	};
	if(mKeyboard.IsKeyDown(KC_s)) {
		mpParent->mMessageSystem->Enqueue(new Message("MoveBack",PRIO_HIGH));
	};

	if(mKeyboard.IsKeyDown(KC_a)) {
		mpParent->mMessageSystem->Enqueue(new Message("MoveLeft",PRIO_HIGH));
	};
	if(mKeyboard.IsKeyDown(KC_d)) {
		mpParent->mMessageSystem->Enqueue(new Message("MoveRight",PRIO_HIGH));
	};
};