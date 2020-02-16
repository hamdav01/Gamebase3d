// ICallback.h
#ifndef ICALLBACK_H_INCLUDED
#define ICALLBACK_H_INCLUDED
class ICallback {
public:
	virtual ~ICallback() {};
	virtual void Invoke(class IMessage*) = 0;
	virtual bool Compare(void*) const = 0;
};

#endif // ICALLBACK_H_INCLUDED