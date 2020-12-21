#ifndef IDISPOSABLE_H
#define IDISPOSABLE_H
#pragma once

// Standard Headers
#include <atomic>

// Define Namespace
namespace interfaces
{
	class IDisposable
	{
	public:
		virtual void dispose() = 0;

	protected:
		std::atomic_bool _disposed;
	};
} // namespace interfaces

#endif // !IDISPOSABLE_H
