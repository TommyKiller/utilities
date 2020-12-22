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
	template <class delegate_t>
	class Event
	{
	public:
		Event() = default;

		bool muted()
		{
			return _muted.load();
		}

		void mute()
		{
			_muted.store(true);
		}

		void unmute()
		{
			_muted.store(false);
		}

		Event& addEventListener(const delegate_t& delegate)
		{
			_delegates.push_back(delegate);

			return *this;
		}

		Event& removeEventListener(const delegate_t& delegate)
		{
			auto found_r = std::find(_delegates.rbegin(), _delegates.rend(), delegate);
			if (found_r != _delegates.rend()) _delegates.erase((found_r + 1).base());

			return *this;
		}

		void dispatch(typename delegate_t::args_type args)
		{
			if (!muted())
			{
				for (delegate_t& delegate : _delegates)
				{
					delegate(args);
				}
			}
		}

		void reset()
		{
			_delegates.reset();
		}

	private:
		std::vector<delegate_t> _delegates;

		std::atomic<bool> _muted {false};

		Event(const Event&) = delete;

		Event& operator=(const Event&) = delete;

	};
} // namespace tk_events

#endif // !EVENT_H
