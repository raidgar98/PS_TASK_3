#include "drag_n_drop.h"

void swap_drag_n_drop(arg_type current, arg_type external)
{
	const Point cur{ current->point };
	const Point ext{ external->point };

	current->point = ext;
	external->point = cur;

	current->require_sync = true;
	external->require_sync = true;
}
