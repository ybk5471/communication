#include "cb.hpp"

cb::cb() : m_callback(nullptr) {}

cb::~cb() {}

void cb::connect(const func_cb_t & callback) {
	m_callback = callback;
}

void cb::disconnect() {
	m_callback = nullptr;
}

void cb::exec() {
	if (m_callback) {
		m_callback();
	}
}
