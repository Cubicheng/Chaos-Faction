# include "frame_timer.h"

namespace frame_timer {
	DWORD frame_start_time;
	DWORD frame_end_time;
	DWORD frame_time;


	void frame_sleep() {
		frame_end_time = GetTickCount();
		frame_time = frame_end_time - frame_start_time;
		if (frame_time < 1000 / 60) {
			Sleep(1000 / 60 - frame_time);
		}
	}
}