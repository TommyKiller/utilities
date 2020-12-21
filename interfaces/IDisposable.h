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
		void dispose();

	protected:
		virtual void dispose(bool disposing) = 0;

		std::atomic_bool _disposed;
	};
} // namespace interfaces

#endif // !IDISPOSABLE_H
