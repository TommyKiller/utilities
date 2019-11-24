#ifndef EVENT_H
#define EVENT_H
#include <vector>
#include "Delegate.h"

namespace Events
{
	template <typename _Ret, typename... Args>
	class Event
	{
	public:
		Event() = default;

		Event& operator+=(const Delegate<_Ret, Args...>& delegate)
		{
			_Delegates.push_back(delegate);

			return *this;
		}

		Event& operator-=(const Delegate<_Ret, Args...>& delegate)
		{
			_Delegates.erase(std::find(_Delegates.begin(), _Delegates.end(), delegate));

			return *this;
		}

		void operator()(Args... args)
		{
			for (Delegate<_Ret, Args...>& delegate : _Delegates)
			{
				delegate(args...);
			}
		}

	private:
		std::vector<Delegate<_Ret, Args...>> _Delegates;

		Event(const Event&) = delete;

		Event& operator=(const Event&) = delete;

	};
}

#endif
