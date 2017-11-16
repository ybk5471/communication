#ifndef PLR
#include <sys/epoll.h>

#include <"pl.hpp">

class plr :: public pl {
public:
	plr();
	~plr();

public:
	void add(pl & obj) const;
	void del(pl & obj) const;
	void mod(pl & obj) const;
public:
	void run();
	void dispose();
};
#endif
