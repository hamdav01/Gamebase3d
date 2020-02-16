// MessageSystem.h //
#ifndef MESSAGESYSTEM_H_INCLUDED
#define MESSAGESYSTEM_H_INCLUDED

#include "stdafx.h"
#include "IMessage.h"
#include "ICallback.h"
#include "Callback.h"

class MessageSystem {
public:
	MessageSystem();
	~MessageSystem();
	void Enqueue(IMessage *pMessage);
	void Update(long long maxMs);
	void UnregisterCallback(const std::string &messageType,void *pObj);

	template <class T>
	void RegisterCallback(const std::string &messageType,T *pObj,void(T::*pFnc)(class IMessage*)) {
		std::map<std::string,std::vector<ICallback*>>::iterator it=mCallbacks.find(messageType);
		if(it==mCallbacks.end()) {
			mCallbacks.insert(
			std::make_pair<std::string,std::vector<ICallback*>>(
			messageType,std::vector<ICallback*>()));
			it=mCallbacks.find(messageType);
		};
		it->second.push_back(new Callback<T>(pObj,pFnc));
	};
private:
std::map<std::string,std::vector<ICallback*>> mCallbacks;
std::list<IMessage*> mMessageQueue;
};
#endif