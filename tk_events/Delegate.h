#ifndef DELEGATE_H
#define DELEGATE_H
#pragma once

// Standard Headers
#include <functional>
#include <tuple>

// Define Namespace
namespace tk_events
{
	template <typename ret_t, typename... args_t>
	class Delegate
	{
	public:
		using ret_type = ret_t;
		using args_type = std::tuple<args_t...>;

		Delegate()
			: _Function(nullptr),
			_Func_Ptr(nullptr),
			_Object_Ptr(nullptr)
		{}

		template <typename Object>
		Delegate(ret_t(Object::* method)(args_t...), Object* obj)
			: _Func_Ptr((void*&)method),
			_Object_Ptr(obj)
		{
			_Function = [obj, method](args_t... args) -> ret_t {return (obj->*method)(args...); };
		}

		Delegate(ret_t(*func)(args_t...))
			: _Function(func),
			_Func_Ptr(func),
			_Object_Ptr(nullptr)
		{}

		ret_t operator()(args_type args)
		{
			if (_Function)
			{
				return std::apply(_Function, args);
			}
		}

		bool operator!()
		{
			return (!_Function);
		}

		bool operator==(const Delegate& delegate)
		{
			return (this->_Object_Ptr == delegate._Object_Ptr &&
				this->_Func_Ptr == delegate._Func_Ptr);
		}

		bool operator!=(const Delegate& delegate)
		{
			return (this->_Object_Ptr != delegate._Object_Ptr ||
				this->_Func_Ptr != delegate._Func_Ptr);
		}

	private:
		std::function<ret_t(args_t...)> _Function;
		void* _Func_Ptr;
		void* _Object_Ptr;

	};
} // namespace tk_events

#endif // !DELEGATE_H
