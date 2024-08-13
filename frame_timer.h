#pragma once

# include "graphics.h"

namespace frame_timer {
	extern DWORD frame_start_time;
	extern DWORD frame_end_time;
	extern DWORD frame_time;
	void frame_sleep();
}