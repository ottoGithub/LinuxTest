#include "PollPoller.h"
#include "Channel.h"
#ifdef __GNUC__
#include <poll.h>
#endif
#ifdef _WIN32
#include <WinSock2.h>
#endif
namespace xtProxima
{

	PollPoller::~PollPoller()
	{
	}

	void PollPoller::FillActiveChannels(int numEvents, ChannelList* pActiveChannels) const
	{
		for (auto iter = m_PollFds.begin(); iter != m_PollFds.end() && numEvents > 0; ++iter)
		{
			if (iter->revents > 0)
			{
				--numEvents;
				auto iterCh = m_Channels.find(iter->fd);
				assert(iterCh != m_Channels.end());
				auto pChannel = iterCh->second;
				assert(pChannel->GetFd() == iter->fd);
				pChannel->SetREvents(iter->revents);
				// pfd->revents = 0;
				pActiveChannels->push_back(pChannel);
			}
		}
	}

	void PollPoller::UpdateChannel(Channel* pChannel)
	{
		AssertInLoopThread();
		std::cout << "fd = " << pChannel->GetFd() << " events = " << pChannel->GetEvents();
		if (pChannel->GetIndex() < 0) {
			assert(m_Channels.find(pChannel->GetFd()) == m_Channels.end());
			struct pollfd pfd;
			pfd.fd = pChannel->GetFd();
			pfd.events = static_cast<short>(pChannel->GetEvents());
			pfd.revents = 0;
			m_PollFds.push_back(std::move(pfd)); // mark!
			int idx = static_cast<int>(m_PollFds.size()) - 1;
			pChannel->SetIndex(idx);
			m_Channels[pfd.fd] = pChannel;
		}
		else
		{
			assert(m_Channels.find(pChannel->GetFd()) == m_Channels.end());
			assert(m_Channels[pChannel->GetFd()] == pChannel);
			int idx = pChannel->GetIndex();
			assert(idx >= 0 && idx < static_cast<int>(m_PollFds.size()));
			struct pollfd& pfd = m_PollFds[idx];
			assert(pfd.fd == pChannel->GetFd() || pfd.fd == -1);
			pfd.events = static_cast<short>(pChannel->GetEvents());
			pfd.revents = 0;
			if (pChannel->IsNoneEvent()) {
				pfd.fd = -1;
			}
		}
	}
}