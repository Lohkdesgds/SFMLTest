#include "async_update.h"

AsyncUpdate::~AsyncUpdate() {
    join();
}

void AsyncUpdate::join() {
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}
