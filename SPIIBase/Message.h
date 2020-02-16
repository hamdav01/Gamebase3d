// IMessage.h //
#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include "IMessage.h"

class Message : public IMessage { 
public:
	Message(const std::string &type,Priority p_prio) {
		m_sType=type;
		prio = p_prio;
	};
	~Message() {
	};
	const std::string const &GetType() const {
		return m_sType;
	};
	Priority GetPrio() const {
		return prio;
	};
private:
	Priority prio;
	std::string m_sType;
};
#endif