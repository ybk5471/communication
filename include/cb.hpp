#pragma once

#include <functional>

class cb {
public:
	typedef std::function<void()> func_cb_t;
public:
	cb();
	~cb();

	void connect(const func_cb_t & callback);
	void disconnect();
	void exec();
private:
	func_cb_t m_callback;
};
