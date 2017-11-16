#pragma once

#include <sys/socket.h>

class sserver : public pl, public cb {
public:
	sserver();
	~sserver();

	void send();
	void receive();

	void dispose();
};
