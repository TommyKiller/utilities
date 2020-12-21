#ifndef EVENT_H
#define EVENT_H
#pragma once

// Standard Headers
#include <vector>
#include <atomic>

// Local Headers
#include "Delegate.h"

// Define Namespace
namespace tk_events
{
	template <typename _Ret, typename... Args>
	class Event
	{
	public:
		Event() = default;

		bool isActive()
		{
			return _active.load();
		}

		void setActive(bool active)
		{
			_active.exchange(active);
		}

		Event& addDelegate(const Delegate<_Ret, Args...>& delegate)
		{
			_delegates.push_back(delegate);

			return *this;
		}

		Event& removeDelegate(const Delegate<_Ret, Args...>& delegate)
		{
			auto found_r = std::find(_delegates.rbegin(), _delegates.rend(), delegate);
			if (found_r != _delegates.rend()) _delegates.erase((found_r + 1).base());

			return *this;
		}

		void poll(Args... args)
		{
			if (isActive())
			{
				for (Delegate<_Ret, Args...>& delegate : _delegates)
				{
					delegate(args...);
				}
			}
		}

		void clear()
		{
			_delegates.clear();
		}

	private:
		std::vector<Delegate<_Ret, Args...>> _delegates;

		std::atomic<bool> _active {true};

		Event(const Event&) = delete;

		Event& operator=(const Event&) = delete;

	};
} // namespace tk_events

#endif // !EVENT_H
