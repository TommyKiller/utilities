#ifndef IDISPOSABLE_H
#define IDISPOSABLE_H
#pragma once

// Standard Headers
#include <atomic>

// Define Namespace
namespace tk_interfaces
{
	class IDisposable
	{
	public:
		virtual void dispose() = 0;

	protected:
		std::atomic_bool _disposed;
	};
} // namespace tk_interfaces

#endif // !IDISPOSABLE_H
