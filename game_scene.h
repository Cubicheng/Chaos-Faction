#pragma once

# include "scene.h"
# include "scene_manager.h"
# include "resource.h"
# include "util.h"
# include "platform.h"
# include "player.h"
# include "bullet.h"
# include "status_bar.h"
# include <iostream>

extern SceneManager scene_manager;

extern Camera camera;

extern Player* player_1;
extern Player* player_2;

std::vector<Platform> platform_list;
std::vector<Bullet*> bullet_list;

class GameScene :public Scene{
public:
	GameScene() {

	}

	~GameScene() {

	}

	void on_enter() {
		mciSendString(_T("pause bgm_menu"), NULL, 0, NULL);
		mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);

		pos_img_sky.x = (getwidth() - rs::img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - rs::img_sky.getheight()) / 2;

		pos_img_hills.x = (getwidth() - rs::img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - rs::img_hills.getheight()) / 2;

		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.img = &rs::img_platform_large;
		large_platform.render_position.x = 122;
		large_platform.render_position.y = 455;
		large_platform.collision_shape.left = large_platform.render_position.x + 30;
		large_platform.collision_shape.right = large_platform.render_position.x + rs::img_platform_large.getwidth() - 30;
		large_platform.collision_shape.y = large_platform.render_position.y + 60;

		Platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &rs::img_platform_small;
		small_platform_1.render_position.x = 175;
		small_platform_1.render_position.y = 360;
		small_platform_1.collision_shape.left = small_platform_1.render_position.x + 40;
		small_platform_1.collision_shape.right = small_platform_1.render_position.x + rs::img_platform_small.getwidth() - 40;
		small_platform_1.collision_shape.y = small_platform_1.render_position.y + rs::img_platform_small.getheight() / 2;

		Platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &rs::img_platform_small;
		small_platform_2.render_position.x = 855;
		small_platform_2.render_position.y = 360;
		small_platform_2.collision_shape.left = small_platform_2.render_position.x + 40;
		small_platform_2.collision_shape.right = small_platform_2.render_position.x + rs::img_platform_small.getwidth() - 40;
		small_platform_2.collision_shape.y = small_platform_2.render_position.y + rs::img_platform_small.getheight() / 2;

		Platform& small_platform_3 = platform_list[3];
		small_platform_3.img = &rs::img_platform_small;
		small_platform_3.render_position.x = 515;
		small_platform_3.render_position.y = 225;
		small_platform_3.collision_shape.left = small_platform_3.render_position.x + 40;
		small_platform_3.collision_shape.right = small_platform_3.render_position.x + rs::img_platform_small.getwidth() - 40;
		small_platform_3.collision_shape.y = small_platform_3.render_position.y + rs::img_platform_small.getheight() / 2;
	
		player_1->set_position(200, 50);
		player_1->set_facing_right(true);
		player_2->set_position(975, 50);
		player_2->set_facing_right(false);

		status_bar_1P.set_avatar(player_1->get_img_avatar());
		status_bar_2P.set_avatar(player_2->get_img_avatar());

		status_bar_1P.set_position(235, 625);
		status_bar_2P.set_position(675, 625);
	}

	void on_update(int delta) {
		for (int i = 0; i < bullet_list.size(); i++) {
			if (bullet_list[i]->check_can_remove()) {
				delete bullet_list[i];
				bullet_list.erase(bullet_list.begin() + i);
			}
		}

		for (Bullet* bullet : bullet_list) {
			bullet->on_update(delta);
		}

		player_1->on_update(delta);
		player_2->on_update(delta);

		main_camera.on_update(delta);

		/*bullet_list.erase(std::remove_if(
			bullet_list.begin(), bullet_list.end(),
			[](const Bullet* bullet) {
				bool deletable = bullet->check_can_remove();
				if (deletable) delete bullet;
				return deletable;
			}),
			bullet_list.end());*/
	}

	void on_draw(const Camera& camera) {
		ut::putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &rs::img_sky);
		ut::putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &rs::img_hills);

		for (const Platform& platform : platform_list) {
			platform.on_draw(camera);
		}

		player_1->on_draw(camera);
		player_2->on_draw(camera);

		for (Bullet* bullet : bullet_list) {
			bullet->on_draw(camera);
		}

		status_bar_1P.set_hp(player_1->get_hp());
		status_bar_1P.set_mp(player_1->get_mp());

		status_bar_2P.set_hp(player_2->get_hp());
		status_bar_2P.set_mp(player_2->get_mp());

		status_bar_1P.on_draw();
		status_bar_2P.on_draw();
	}

	void on_input(const ExMessage& msg) {
		player_1->on_input(msg);
		player_2->on_input(msg);

		switch (msg.message) {
		case WM_KEYDOWN:
			if (msg.vkcode == 0x51) {
				is_debug = !is_debug;
			}
			break;
		}
	}

	void on_exit() {

	}
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	StatusBar status_bar_1P;
	StatusBar status_bar_2P;
};