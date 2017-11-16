#include <plr.hpp>

plr::plr()
: pl(epoll_create1(EPOLL_CLOEXEC), uint32_t(::EPOLLIN | ::EPOLLOUT | ::EPOLLPRI)) {}

plr::~plr() {}

void plr::add(pl & obj) const {
	struct epoll_event evt;
	evt.events = obj._evt();
	evt.ptr = &obj;
	int ret = ::epoll_ctl(this->_fd(), EPOOL_CTL_ADD, obj->_fd(), &evt);
	validate_ret(ret, "epoll add fd");
}

void plr::del(pl & obj) const {
	int ret = ::epoll_ctl(this->_fd(), EPOOL_CTL_DEL, obj->_fd(), NULL);
	validate_ret(ret, "epoll del fd");
}

void plr::mod(pl & obj) const {
	struct epool_event evt;
	evt.events = obj._evt();
	evt.ptr = &obj;
	int ret = ::epoll_ctl(this->_fd(), EPOOL_CTL_MOD, obj->_fd(), &evt);
	validate_ret(ret, "epoll mod fd");
}

void run() {
	struct epoll_event evt;
	while(1) {
		int ret = ::epoll_wait(this->_fd(), &evt, 1, 0);
/* 		epoll_wait运行的原理是:
** 		等侍注册在epfd上的socket fd的事件的发生，如果发生则将发生的sokct fd和事件类型放入到events数组中。
** 		并且将注册在epfd上的socket fd的事件类型给清空，所以如果下一个循环你还要关注这个socket fd的话，则需要用epoll_ctl(epfd,EPOLL_CTL_MOD,listenfd,&ev)来重新设置socket fd的事件类型。
** 		这时不用EPOLL_CTL_ADD,因为socket fd并未清空，只是事件类型清空。这一步非常重要
*/
		if (ret < 1) {
			continue;
		}
		(pl *) evt.data.ptr -> dispose();
	}
}

void dispose() {
	struct epoll_event evt;
	while(1) {
		int ret = ::epoll_wait(this->_fd(), &evt, 1, 0);
		if (ret < 1) {
			break;
		}
		(pl *) evt.data.ptr -> dispose();
	}
}
