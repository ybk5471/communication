#pragma once
#include <fcntl.h>
#include <stdint.h>

class pl {
public:
	pl(uint32_t event, int fd);
	~pl();

	int fctl(int cmd);
	template<typename _T>
	int fctl(int cmd, _T arg);

public:
	uint32_t _evt() const {return m_event;}
	int _fd() const {return m_fd;}

	virtual void dispose() = 0;
private:
	uint32_t m_event;
	const int m_fd;
};
