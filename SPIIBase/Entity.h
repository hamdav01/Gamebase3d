// Entity.h //
// A class that holds an object without a visual //
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "stdafx.h"

class IComponent;
class RenderNode;
class MessageSystem;

class Entity
{
	
	class IProperty {
	public:
		virtual ~IProperty() {};
	};

	template <class T>
	class Property : public IProperty {
	public:
		Property(T *pData) : mpData(pData){};
		T *mpData;
	};

public:
	Entity();
	virtual ~Entity();

	void AttachComponent(IComponent *pComponent);
	virtual void init(RenderNode* p_pxRenderNode,Vector3 &p_vPosition);
	virtual void Update(float p_fDeltaTime); // Updates the entity.

	template <class T>
	T *GetProperty(const std::string &propertyName) {
		T *pData=NULL;
		std::map<std::string,IProperty*>::iterator it=mProperties.find(propertyName);
		if(it==mProperties.end()) {
			pData=new T;
			mProperties.insert(
			std::make_pair<std::string,IProperty*>(
			propertyName,new Property<T>(pData)));
		}
		else {
			Property<T> *pP=dynamic_cast<Property<T>*>(it->second);
			if(pP!=NULL)
			{
				pData=pP->mpData;
			};
		};
		return pData;
	};

	MessageSystem *mMessageSystem;
protected:
	std::vector<IComponent*> mpComponents;
	std::map<std::string,IProperty*> mProperties;
	Vector3 *vec;
};

#endif


