#include "pl.hpp"
#include "validate.hpp"

pl::pl(uint32_t event, int fd)
: m_event(event)
, m_fd(validate_fd(fd, "set pl fd"))
{
	int ret;
	ret = fctl(F_SETFL, fctl(F_GETFL) | O_NONBLOCK);
	validate_ret(ret, "set nonblock");

	ret = fctl(F_SETFD, fctl(F_GETFD) | FD_CLOEXEC);
	validate_ret(ret, "set cloexec");
}

pl::~pl()
{
	close(m_fd);
}

int pl::fctl(int cmd) {
	return ::fcntl(m_fd, cmd);
}

template<typename _T>
int pl::fctl(int cmd, _T arg) {
	return ::fcntl(m_fd, cmd, arg);
}
