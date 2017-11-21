#include "sserver.hpp"

sserver::sserver(uint16_t port)
: pl(::socket(AF_INET, SOCKET_STREAM, 0), uint32_t(::EPOLLIN)) {
	int opt = 1;

	//reuse address when TIME_WAIT
	int ret = 0;
	ret = ::setsockopt(this->_fd(), SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt))
	validate_ret(ret, "setsockopt, reuseaddr");

	//bind local port
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);
	ret = ::bind(this->_fd(), (struct servaddr *)&servaddr, sizeof(servaddr))
	validate_ret(ret, "bind");

	//listen
	ret = ::listen(this->_fd(), 0);
	validate_ret(ret, "listen");
}

sserver::~sserver()
{
}

size_t sserver::send(const void * buf, size_t len) {
	int ret = ::send(this->_fd(), buf, len, 0);
	validate_ret(ret, "send");
	return (size_t)ret;
}

size_t sserver::receive(void * buf, size_t len) {
	int ret = ::recv(this->_fd(), buf, len, 0);
	validate_ret(ret, "receive");
	return (size_t)ret;
}

void sserver::dispose() {

}
