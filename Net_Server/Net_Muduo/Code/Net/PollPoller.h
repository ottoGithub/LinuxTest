#pragma once
#include "Base/Common.h"
#include "Net/EventLoop.h"
#include "IPoller.h"
struct  pollfd;

namespace xtProxima
{
	class Channel;

	class PollPoller : public IPoller
	{
		NoCopy(PollPoller)
	public:
		using IPoller::IPoller;
		~PollPoller();

		//Timestamp Poll(int timeoutMS, ChannelList* pActiveChannels);
		void UpdateChannel(Channel* pChannel) override;
		void RemoveChannel(Channel* pChannel) override {};

	private:
		void FillActiveChannels(int numEvents, ChannelList* pActiveChannels) const;
	private:
		typedef std::vector<struct pollfd> PollFdList;
		PollFdList m_PollFds;
	};


}