#include "EventLoop.h"
#include "Channel.h"
namespace xtProxima
{
	thread_local EventLoop* p_LoopInThisThread = nullptr;

	EventLoop* EventLoop::GetCurrentEventLoop()
	{
		return p_LoopInThisThread;
	}

	EventLoop::EventLoop() 
		: m_ThreadID(std::this_thread::get_id()),
		m_pIPoller(IPoller::NewDefaultPoller(this))
	{
		std::cout << "EventLoop created [" << __FUNCTION__ <<
			"] in thread [" << m_ThreadID << "]." << std::endl;
		if (p_LoopInThisThread)
		{
			std::cout << "Another EventLoop " << p_LoopInThisThread <<
				" already exists in this thread " << m_ThreadID;
		}
		else
		{
			p_LoopInThisThread = this;
		}
	}

	EventLoop::~EventLoop()
	{
		assert(!m_bLooping);
		p_LoopInThisThread = nullptr;
	}

	void EventLoop::Loop()
	{
		assert(!m_bLooping);
		AssertInLoopThread();

		m_bLooping = true;
		m_bQuit = false;
		while (!m_bQuit)
		{
			m_ActiveChannels.clear();
			//m_pIPoller->poll(...);

			m_bEventHandling = true;
			for(auto it : m_ActiveChannels) {
				it->HandleEvent();
			}
			m_bEventHandling = false;
		}

		std::cout << "EventLoop [" << __FUNCTION__ << "] stop looping";
		m_bLooping = false;
	}

	void EventLoop::Quit()
	{
		m_bQuit = true;
		if (!IsInLoopThread())
		{
			//wakeup();
		}
	}

	void EventLoop::AssertInLoopThread()
	{
		if (!IsInLoopThread())
		{
			AbortNotInLoopThread();
		}
	}

	void EventLoop::AbortNotInLoopThread()
	{
		std::cout << __FUNCTION__ << "EventLoop was created in thread[" << m_ThreadID
			<< "], current thread id = [" << std::this_thread::get_id() << "]" << std::endl;
	}


	void EventLoop::UpdateChannel(Channel* pChannel)
	{
		assert(pChannel->GetOwnerLoop() == this);
		AssertInLoopThread();
		m_pIPoller->UpdateChannel(pChannel);
	}

	void EventLoop::RemoveChannel(Channel* pChannel)
	{
		assert(pChannel->GetOwnerLoop() == this);
		AssertInLoopThread();
		//std::find(channel);
		m_pIPoller->RemoveChannel(pChannel);
	}

	bool EventLoop::HasChannel(Channel* pChannel)
	{
		assert(pChannel->GetOwnerLoop() == this);
		AssertInLoopThread();
		//return poller->HasChannel(pChannel);
		return true;
	}
}