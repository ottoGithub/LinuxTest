#include "IPoller.h"
#include "Channel.h"
#include "EventLoop.h"
#ifdef __GNUC__
#include "PollPoller.h"
//#include "EPollPoller.h"
#elif defined(_WIN32)
#include "PollPoller.h"
#endif

namespace xtProxima
{
	IPoller::IPoller(EventLoop* pLoop)
		: m_pOwnerLoop(pLoop)
	{
	}

	IPoller::~IPoller()
	{
	}

	void IPoller::AssertInLoopThread() const 
	{
		m_pOwnerLoop->AssertInLoopThread();
	}

	bool IPoller::HasChannel(Channel* pChannel) const
	{
		AssertInLoopThread();
		auto iter = m_Channels.find(pChannel->GetFd());
		return iter != m_Channels.end() && iter->second == pChannel;
	}

	IPoller* IPoller::NewDefaultPoller(EventLoop* pLoop)
	{
#if 1
		return new PollPoller(pLoop);
#else
		//return new EPollPoller(pLoop);
		//return new IOCPPoller(pLoop);
#endif
	}
}