// CameraComponent.h //
#ifndef CAMERACOMPONENT_H_INCLUDED
#define CAMERACOMPONENT_H_INCLUDED
#include "IComponent.h"

class Camera;
class CameraComponent : public IComponent {
public:
	CameraComponent(Camera *cam);
	CameraComponent();
	~CameraComponent();
	void OnInit(Entity *pParent);
	void VOnInit();
	void OnUpdate(float deltatime);
private:
	void MoveRight(class IMessage* p_Message);
	void MoveLeft(class IMessage* p_Message);
	void MoveForward(class IMessage* p_Message);
	void MoveBack(class IMessage* p_Message);
	Vector3* m_vPosition;
	Camera* mCamera;
	float m_fSpeed;
};
#endif
	
	

