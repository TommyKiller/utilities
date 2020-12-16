#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H
#pragma once

// Standard Headers
#include <string>
#include <memory>
#include <unordered_map>

// Local Headers
#include "Event.h"

// Define Namespace
namespace events
{
	template<typename _Ret, typename... Args>
	class EventDispatcher
	{
	public:
		EventDispatcher() = default;

		EventDispatcher& addEventListener(std::string event, const Delegate<_Ret, Args...>& delegate)
		{
			if (_events.find(event) == _events.end())
			{
				_events[event] = std::make_unique<Event<_Ret, Args...>>();
			}
			_events[event].get()->addDelegate(delegate);

			return *this;
		}

		EventDispatcher& removeEventListener(std::string event, const Delegate<_Ret, Args...>& delegate)
		{
			if (_events.find(event) != _events.end())
			{
				_events[event].get()->removeDelegate(delegate);
			}

			return *this;
		}

		void pollEvent(std::string event, Args... args)
		{
			if (_events.find(event) != _events.end())
			{
				_events[event].get()->poll(args...);
			}
		}

		bool isEventActive(std::string event)
		{
			if (_events.find(event) != _events.end())
			{
				return _events[event].get()->isActive();
			}
			else
			{
				return false;
			}
		}

		void setEventActive(std::string event, bool active)
		{
			if (_events.find(event) != _events.end())
			{
				_events[event].get()->setActive(active);
			}
		}

		void erase(std::string event)
		{
			if (_events.find(event) != _events.end())
			{
				_events.erase(event);
			}
		}

		void clear()
		{
			_events.clear();
		}

		virtual ~EventDispatcher() {}

	private:
		std::unordered_map<std::string, std::unique_ptr<Event<_Ret, Args...>>> _events;
	};
} // namespace events

#endif // EVENT_DISPATCHER_H
