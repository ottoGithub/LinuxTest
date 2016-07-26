#pragma once
#include "Base/Common.h"
#include <vector>
#include <map>

namespace xtProxima
{
	class Channel;
	class EventLoop;
	class IPoller
	{
		NoCopy(IPoller)
	public:
		typedef std::vector<Channel*> ChannelList;

		IPoller(EventLoop* pLoop);
		virtual ~IPoller();

		//virtual Timestamp Poll(int timeoutMS, ChannelList* pActiveChannels);
		virtual void UpdateChannel(Channel* pChannel) = 0;
		virtual void RemoveChannel(Channel* pChannel) = 0;
		virtual bool HasChannel(Channel* pChannel) const;

		void AssertInLoopThread() const;
		static IPoller* NewDefaultPoller(EventLoop* pLoop);

	protected:
		typedef std::map<int, Channel*> ChannelMap;
		ChannelMap m_Channels;
	private:
		EventLoop* m_pOwnerLoop{ nullptr };
	};
}