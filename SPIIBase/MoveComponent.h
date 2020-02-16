// MoveComponent.h //
#ifndef MOVECOMPONENT_H_INCLUDED
#define MOVECOMPONENT_H_INCLUDED
#include "IComponent.h"
class Entity;

class MoveComponent : public IComponent {
public:
	MoveComponent();
	~MoveComponent();
	void OnInit(Entity *pParent);
	void VOnInit();
	void OnUpdate(float);
private:
	void MoveRight(class IMessage* p_Message);
	void MoveLeft(class IMessage* p_Message);
	void MoveForward(class IMessage* p_Message);
	void MoveBack(class IMessage* p_Message);
	Vector3* m_vPosition;
};
#endif // MOVECOMPONENT_H_INCLUDED
