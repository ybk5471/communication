#pragma once

#include <sys/socket.h>

class sserver : public pl, public cb {
public:
	sserver();
	~sserver();

	size_t send();
	size_t receive();

	void dispose();
};
