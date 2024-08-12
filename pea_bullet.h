#pragma once

# include "bullet.h"
# include "animation.h"
# include "resource.h"
# include "util.h"

class PeaBullet :public Bullet{
public:
	PeaBullet() {
		size.x = 64;
		size.y = 64;
		damage = 10;

		animation_bullet_break.set_atlas(&rs::atlas_pea_break);
		animation_bullet_break.set_interval(100);
		animation_bullet_break.set_loop(false);
		animation_bullet_break.set_callback([&]() {can_remove = true; });
	}
	~PeaBullet() = default;

	void on_collide() {
		Bullet::on_collide();
		switch (rand() % 3 + 1) {
		case 1:
			mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
			break;
		case 3:
			mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
			break;
		}
	}

	void on_update(int delta) {
		position = position + velocity * (float)delta;
		if (!valid)
			animation_bullet_break.on_update(delta);
		if (check_if_exceed_screen())
			can_remove = true;
	}

	void on_draw(const Camera& camera) const {
		if (valid) {
			ut::putimage_alpha(camera, position.x, position.y, &rs::img_pea);
			if (is_debug) {
				setlinecolor(RGB(255, 0, 0));
				ut::draw_line(camera, position.x, position.y, position.x + size.x, position.y);
				ut::draw_line(camera, position.x + size.x, position.y, position.x + size.x, position.y + size.y);
				ut::draw_line(camera, position.x + size.x, position.y + size.y, position.x, position.y + size.y);
				ut::draw_line(camera, position.x, position.y + size.y, position.x, position.y);
			}
		}
		else
			animation_bullet_break.on_draw(camera, position.x, position.y);
	}

private:
	Animation animation_bullet_break;

};