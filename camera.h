#pragma once

# include "vector2.h"
# include "timer.h"

class Camera {
public:
	Camera();
	~Camera() = default;

	const Vector2& get_position()const;
	void reset();
	void on_update(int delta);
	void shake(float strength, int duration);

private:
	Vector2 position;
	Timer timer_shake;
	bool is_shaking = false;
	float shaking_strength = 0;
};