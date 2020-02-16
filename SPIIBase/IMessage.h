// IMessage.h //
#ifndef IMESSAGE_H_INCLUDED
#define IMESSAGE_H_INCLUDED
#include "stdafx.h"

enum Priority {
	PRIO_ZERO = (0),
	PRIO_LOW = (1<<0),
	PRIO_MEDIUM = (1<<1),
	PRIO_HIGH = (1<<2),
};

class IMessage { 
public:
	virtual ~IMessage() {};
	virtual const std::string const &GetType() const = 0;
	virtual Priority GetPrio() const = 0;
private:
};
#endif // IMESSAGE_H_INCLUDED

