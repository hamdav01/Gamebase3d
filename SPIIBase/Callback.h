// Callback.h //
#ifndef CALLBACK_H_INCLUDED
#define CALLBACK_H_INCLUDED

#include "ICallback.h"

template <class T>
class Callback : public ICallback {

	T *mpObj;
	void(T::*mpFnc)(class IMessage*);
public:
	Callback(T *pObj,void(T::*pFnc)(class IMessage*))
		: mpObj(pObj), mpFnc(pFnc) {};

	void Invoke(class IMessage *pMsg) {
		(*mpObj.*mpFnc)(pMsg);
	};

	bool Compare(void *pObj) const {
		return mpObj==pObj;
	};
};
#endif