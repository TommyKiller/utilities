#ifndef DELEGATE_H
#define DELEGATE_H
#include <functional>

namespace Events
{
	template <typename _Ret, typename... Args>
	class Delegate
	{
	public:
		Delegate()
			: _Function(nullptr),
			_Func_Ptr(nullptr),
			_Object_Ptr(nullptr)
		{}

		template <typename Object>
		Delegate(_Ret(Object::* method)(Args...), Object* obj)
			: _Func_Ptr((void*&)method),
			_Object_Ptr(obj)
		{
			_Function = [obj, method](Args... args) -> _Ret {return (obj->*method)(args...); };
		}

		Delegate(_Ret(*func)(Args...))
			: _Function(func),
			_Func_Ptr(func),
			_Object_Ptr(nullptr)
		{}

		_Ret operator()(Args... args)
		{
			if (_Function)
			{
				return _Function(args...);
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
		std::function<_Ret(Args...)> _Function;
		void* _Func_Ptr;
		void* _Object_Ptr;

	};
}

#endif
