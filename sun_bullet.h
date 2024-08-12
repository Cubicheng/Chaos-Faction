#pragma once

# include "bullet.h"
# include "resource.h"
# include "animation.h"

extern Camera main_camera;

class SunBullet :public Bullet {
public:
	SunBullet() {
		size.x = 96;
		size.y = 96;
		damage = 20;
		animation_idle.set_atlas(&rs::atlas_sun);
		animation_idle.set_interval(50);

		animation_explode.set_atlas(&rs::atlas_sun_explode);
		animation_explode.set_interval(50);
		animation_explode.set_loop(false);
		animation_explode.set_callback([&]() {can_remove = true; });

		IMAGE* fram_idle = animation_idle.get_frame();
		IMAGE* frame_explode = animation_explode.get_frame();
		explode_render_offset.x = (fram_idle->getwidth() - frame_explode->getwidth()) / 2;
		explode_render_offset.y = (fram_idle->getheight() - frame_explode->getheight()) / 2;
	}

	~SunBullet() = default;

	void on_collide() {
		Bullet::on_collide();
		main_camera.shake(5, 250);
		mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
	}

	void on_update(int delta) {
		if (valid) {
			velocity.y += gravity*delta;
			position = position + velocity * delta;
		}

		if (!valid)
			animation_explode.on_update(delta);
		else
			animation_idle.on_update(delta);

		if (check_if_exceed_screen())
			can_remove = true;
	}

	void on_draw(const Camera& camera) const {
		if (valid) {
			animation_idle.on_draw(camera, position.x, position.y);
			if (is_debug) {
				setlinecolor(RGB(255, 0, 0));
				ut::draw_line(camera, position.x, position.y, position.x + size.x, position.y);
				ut::draw_line(camera, position.x + size.x, position.y, position.x + size.x, position.y + size.y);
				ut::draw_line(camera, position.x + size.x, position.y + size.y, position.x, position.y + size.y);
				ut::draw_line(camera, position.x, position.y + size.y, position.x, position.y);
			}
		}
		else
			animation_explode.on_draw(camera, position.x + explode_render_offset.x, position.y + explode_render_offset.y);
	}

private:
	const float gravity = 1e-3f;

	Animation animation_idle;
	Animation animation_explode;
	Vector2 explode_render_offset;
};