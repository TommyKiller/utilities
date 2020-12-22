#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H
#pragma once

// Standard Headers
#include <memory>
#include <unordered_map>

// Local Headers
#include "Event.h"

// Define Namespace
namespace tk_events
{
	template<class delegate_t, typename... keys_t>
	class EventDispatcher {};

	template<class delegate_t, typename key_t, typename key1_t, typename... keys_t>
	class EventDispatcher<delegate_t, key_t, key1_t, keys_t...>
	{
	public:
		EventDispatcher() = default;

		EventDispatcher& addEventListener(const delegate_t& delegate, key1_t key1,  keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) == _events.end())
			{
				_events[key] = std::make_unique<Event<delegate_t>>();
			}
			_events[key].get()->addEventListener(delegate);

			return *this;
		}

		EventDispatcher& removeEventListener(const delegate_t& delegate, key1_t key1, keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) != _events.end())
			{
				_events[key].get()->removeEventListener(delegate);
			}

			return *this;
		}

		void dispatchEvent(typename delegate_t::args_type args, key1_t key1, keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) != _events.end())
			{
				_events[key].get()->dispatch(args);
			}
		}

		bool muted(key1_t key1, keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) != _events.end())
			{
				return _events[key].get()->muted();
			}
			else
			{
				return true;
			}
		}

		void mute(key1_t key1, keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) != _events.end())
			{
				_events[key].get()->mute();
			}
		}

		void unmute(key1_t key1, keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) != _events.end())
			{
				_events[key].get()->unmute();
			}
		}

		void erase(key1_t key1, keys_t... keys)
		{
			key_t key = assembleKey(key1, keys...);

			if (_events.find(key) != _events.end())
			{
				_events.erase(key);
			}
		}

		void reset()
		{
			_events.reset();
		}

		virtual ~EventDispatcher() {}

	protected:
		virtual key_t assembleKey(key1_t key1, keys_t... keys) = 0;

	private:
		std::unordered_map<key_t, std::unique_ptr<Event<delegate_t>>> _events;

	};

	template<class delegate_t, typename key_t>
	class EventDispatcher<delegate_t, key_t>
	{
	public:
		EventDispatcher() = default;

		EventDispatcher& addEventListener(const delegate_t& delegate, key_t key)
		{
			if (_events.find(key) == _events.end())
			{
				_events[key] = std::make_unique<Event<delegate_t>>();
			}
			_events[key].get()->addEventListener(delegate);

			return *this;
		}

		EventDispatcher& removeEventListener(const delegate_t& delegate, key_t key)
		{
			if (_events.find(key) != _events.end())
			{
				_events[key].get()->removeEventListener(delegate);
			}

			return *this;
		}

		void dispatchEvent(typename delegate_t::args_type args, key_t key)
		{
			if (_events.find(key) != _events.end())
			{
				_events[key].get()->dispatch(args);
			}
		}

		bool muted(key_t key)
		{
			if (_events.find(key) != _events.end())
			{
				return _events[key].get()->muted();
			}
			else
			{
				return true;
			}
		}

		void mute(key_t key)
		{
			if (_events.find(key) != _events.end())
			{
				_events[key].get()->mute();
			}
		}

		void unmute(key_t key)
		{
			if (_events.find(key) != _events.end())
			{
				_events[key].get()->unmute();
			}
		}

		void erase(key_t key)
		{
			if (_events.find(key) != _events.end())
			{
				_events.erase(key);
			}
		}

		void reset()
		{
			_events.reset();
		}

		virtual ~EventDispatcher() {}

	private:
		std::unordered_map<key_t, std::unique_ptr<Event<delegate_t>>> _events;

	};
} // namespace tk_events

#endif // !EVENT_DISPATCHER_H
