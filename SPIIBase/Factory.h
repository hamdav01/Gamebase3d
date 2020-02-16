#include "stdafx.h"

// Abstract class of the Creators.
/*template<class Base>
class CreatorBase {
public:
    virtual ~CreatorBase() {}
    virtual Base * Create() const = 0;
};

template<class Current, class Base> 
class IComponentCreator : public CreatorBase<Base> {
public:
    virtual Base * Create() const {
		return new Current; // Returns a new current class.
	};
};

template<class Current, class Base> 
class iEntityConstructor : public CreatorBase<Base> {
public:
    virtual Base * Create() const {
		return new Current; // Returns a new current class.
	};
};

template <class T>
class ComponentFactory {
public:
	void RegisterComponentCreator(const std::string &type, IComponentCreator *pCreator) {
		std::map<std::string,IComponentCreator*>::iterator it = mComponentCreator.find(type);
		if(it== mComponentCreator.end()) {
			mComponentCreator.insert(
			std::make_pair<std::string,IComponentCreator*>(type,pCreator));
		};
	};

	void RegisterEntityConstructor(const std::string &type,IEntityConstructor *pConstructor) {
		std::map<std::string,iEntityConstructor*>::iterator it = mEntityConstructor.find(type);
		if (it == mEntityConstructor.end()) { 
			mEntityConstructor.insert(
			std::make_pair<std::string,iEntityConstructor<T>*>(type,iEntityConstructor)); 
		};
	};

	IComponent *CreateComponent(const std::string &type) {
		std::map<std::string,IComponentCreator*>::iterator it = mComponentCreator.find(type);
		if (it == mComponentCreator.end()) {
			return NULL;
		};
		return (*it).second->Create(); 
	};

	Entity *CreateEntity(const std::string &type) {
		std::map<std::string,iEntityConstructor*>::iterator it = mEntityConstructor.find(type);
		if (it == mEntityConstructor.end()) { 
			return NULL; 
		};
		return (*it).second->Create();
	};
private:
	std::map<std::string,IComponentCreator*> mComponentCreator;
	std::map<std::string,iEntityConstructor*> mEntityConstructor;
};*/
