#pragma once

# include "camera.h"
# include "graphics.h"
# include "util.h"

extern bool is_debug;

class Platform {
public:
	Platform() = default;
	~Platform() = default;

	struct CollisionShape {
		float y;
		float left, right;
	};

	CollisionShape collision_shape;
	IMAGE* img;
	POINT render_position = { 0 };

	void on_draw(const Camera& camera)const {
		ut::putimage_alpha(camera, render_position.x, render_position.y, img);
		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));
			ut::draw_line(camera, collision_shape.left, collision_shape.y, collision_shape.right, collision_shape.y);
		}
	}

private:

};