#include "IDisposable.h"

void interfaces::IDisposable::dispose()
{
	dispose(true);
}
