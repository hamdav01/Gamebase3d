// MessageSystem.cpp
#include "stdafx.h"
#include "MessageSystem.h"
#include "ICallback.h"
#include "SystemUtils.h"

MessageSystem::MessageSystem(){
};

MessageSystem::~MessageSystem() {
	// empty message queue
	if(!mMessageQueue.empty()) {

		std::list<IMessage*>::iterator itB=mMessageQueue.begin();
		while(itB!=mMessageQueue.end()) {
			delete (*itB);
			++itB;
		};
		mMessageQueue.clear();
	};
	// delete all callbacks
	if(!mCallbacks.empty()) {
		std::map<std::string,std::vector<ICallback*>>::iterator
		itB=mCallbacks.begin();
		while(itB!=mCallbacks.end())
		{
			std::vector<ICallback*> &v=itB->second;
			for(unsigned int i=0;i<v.size();i++) {
				delete v[i];
			};
			v.clear();
			++itB;
		};
	};
};

void MessageSystem::Enqueue(IMessage *pMessage) {
	if(pMessage->GetPrio()>PRIO_MEDIUM) {
		mMessageQueue.push_front(pMessage);
	}
	else {
		mMessageQueue.push_back(pMessage);
	};
};

void MessageSystem::Update(long long maxMs) {

	IMessage *pMsg=NULL;
	long long deltaTime=0,timeSpent=0;
	std::map<std::string,std::vector<ICallback*>>::iterator it = mCallbacks.end();
	
	while(timeSpent<maxMs && !mMessageQueue.empty()) {
		pMsg=mMessageQueue.front();
		mMessageQueue.pop_front();
		it=mCallbacks.find(pMsg->GetType());
		if(it!=mCallbacks.end()) {
			for(unsigned int i=0;i<it->second.size();i++) {
				it->second.at(i)->Invoke(pMsg);
			};
		};
		delete pMsg;
		pMsg=NULL;
		deltaTime=Timer::LowResDeltaS();
		timeSpent+=deltaTime;
	};
};

void MessageSystem::UnregisterCallback(const std::string &messageType,void *pObj)
{
	std::map<std::string,std::vector<ICallback*>>::iterator it=mCallbacks.find(messageType);
	if(it==mCallbacks.end()) {
		return;
	};
	std::vector<ICallback*>::iterator itVB=it->second.begin();
	std::vector<ICallback*>::iterator itVE=it->second.end();
	while(itVB!=itVE)
	{
		if((*itVB)->Compare(pObj)) {
			delete (*itVB);
			it->second.erase(itVB);
			return;
		};
		++itVB;
	};
};
