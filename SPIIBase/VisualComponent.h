// VisualComponent //

#include "IComponent.h"
#include "Entity.h"

class IComponent;

class VisualComponent : public IComponent {
public:
	void OnInit(Entity *pParent) {
		pParent->GetProperty<Vector3>("Position")->z = 5;
	};
	void OnUpdate(float deltaTime) {
	};
	void VOnInit() {
	};
private:
	Matrix4 *mpTransform;
};