// IComponent.h //
#ifndef ICOMPONENT_H_INCLUDED
#define ICOMPONENT_H_INCLUDED
class Entity;

class IComponent {
public:
	virtual ~IComponent() {};
	virtual void OnInit(Entity *pParent) = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void VOnInit() = 0;

protected:
	Entity *mpParent;
};
#endif

