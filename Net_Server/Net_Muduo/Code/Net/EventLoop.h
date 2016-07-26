#pragma once
#include "Base/Common.h"
#include <functional>
#include <thread>
#include <vector>
#include "IPoller.h"

namespace xtProxima
{
	class Channel;
	class EventLoop
	{
		NoCopy(EventLoop);
	public:
		EventLoop();
		~EventLoop();

		void Loop();
		void Quit();
		void AssertInLoopThread();
		bool IsInLoopThread() const { return m_ThreadID == std::this_thread::get_id(); }

		//////////////////////////////////////////////////////////////////////////
		//Channel:
		void UpdateChannel(Channel* pChannel);
		void RemoveChannel(Channel* pChannel);
		bool HasChannel(Channel* pChannel);
		//////////////////////////////////////////////////////////////////////////

		static EventLoop* GetCurrentEventLoop();
	private:
		void AbortNotInLoopThread();

	private:
		typedef std::vector<Channel*> ChannelList;

		bool m_bLooping{ false };
		bool m_bQuit{ false };
		bool m_bEventHandling{false};

		std::thread::id m_ThreadID;
		std::unique_ptr<IPoller> m_pIPoller;
		ChannelList m_ActiveChannels;
	};


}