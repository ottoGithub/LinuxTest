#pragma once
#include "Base/Common.h"
#include <functional>
namespace xtProxima
{
	class EventLoop;

	class Channel
	{
		NoCopy(Channel);
	public:
		typedef std::function<void()> EventCallback;
		Channel(EventLoop* pLoop, int fd);
		~Channel();

		void HandleEvent();
		void SetReadCb(const EventCallback& cb) { m_ReadCb = cb; }
		void SetWriteCb(const EventCallback& cb) { m_WriteCb = cb; }
		void SetErrorCb(const EventCallback& cb) { m_ErrorCb = cb; }

		int GetFd() const { return m_fd; }
		int GetEvents() const { return m_Events; }
		void SetREvents(int rEvents) { m_REvents = rEvents; }
		bool IsNoneEvent() const { return m_Events == kNoneEvent; }

		void EnableReading() { m_Events |= kReadEvent; Update(); }
		void EnableWriting() { m_Events |= kWriteEvent; Update(); }
		void DisableWriting() { m_Events &= ~kWriteEvent; Update(); }
		void DisableAll() { m_Events = kNoneEvent; Update(); }

		int GetIndex() { return m_Index; }
		void SetIndex(int idx) { m_Index = idx; }

		EventLoop* GetOwnerLoop() { return m_pLoop; }
	private:
		void Update();

	private:
		static const int kNoneEvent;
		static const int kReadEvent;
		static const int kWriteEvent;

		EventLoop* m_pLoop{ nullptr };
		const int m_fd{ -1 };
		int m_Events{ 0 };
		int m_REvents{ 0 };
		int m_Index{ -1 };

		EventCallback m_ReadCb;
		EventCallback m_WriteCb;
		EventCallback m_ErrorCb;
	};
}