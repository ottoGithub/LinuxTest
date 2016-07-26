#include "Channel.h"
#include "EventLoop.h"
#ifdef __GNUC__
#include <poll.h>
#endif
#ifdef _WIN32
#include <WinSock2.h>
#endif

namespace xtProxima
{
	const int Channel::kNoneEvent = 0;
	const int Channel::kReadEvent = POLLIN | POLLPRI;
	const int Channel::kWriteEvent = POLLOUT;

	Channel::Channel(EventLoop* pLoop, int fd)
		: m_pLoop(pLoop), m_fd(fd)
	{
	}

	Channel::~Channel()
	{
		
	}

	void Channel::Update()
	{
		m_pLoop->UpdateChannel(this);
	}

	void Channel::HandleEvent()
	{
		if (m_REvents & POLLNVAL) {
			std::cout << __FUNCTION__ << "POLLNVAL" << std::endl;
		}
		if (m_REvents & (POLLERR | POLLNVAL)) {
			if (m_ErrorCb) { m_ErrorCb(); }
		}
		if (m_REvents & (POLLIN | POLLPRI | POLLRDHUP)) {
			if (m_ReadCb) { m_ReadCb(); }
		}
		if (m_REvents & POLLOUT ) {
			if (m_WriteCb) { m_WriteCb(); }
		}
	}
}