#pragma once

# include <functional>

class Timer {
public:
	Timer() = default;
	~Timer() = default;

	void resart() {
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(int val) {
		wait_time = val;
	}

	void set_one_shot(bool flag) {
		one_shot = flag;
	}

	void on_update(int delta) {
		if (paused) return;
		pass_time += delta;
		if (pass_time >= wait_time) {
			if ((!one_shot || (one_shot || !shotted) && callback))
				callback();
			shotted = true;
			pass_time = 0;
		}
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	void pause() {
		paused = true;
	}

	void resume() {
		paused = false;
	}

protected:
	std::function<void()> callback;
	int pass_time = 0;//已过时间
	int wait_time = 0;//等待时间
	bool paused = false;//是否暂停
	bool shotted = false;//是否触发
	bool one_shot = false;//单次触发
};