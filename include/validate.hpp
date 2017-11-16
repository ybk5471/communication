#pragma once
#include <system_error>
#include <errorn.h>

inline int validate_fd(int fd, const char * info) {
	if (fd < 0) {
		throw std::system_error(errno, std::system_category(), info);
	}
	return fd;
}

inline void validate_ret(int ret, const char * info) {
	if (ret == -1) {
		throw std::system_error(errno, std::system_category(), info);
	}
	return ret;
}
