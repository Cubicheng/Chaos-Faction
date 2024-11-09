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

		mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);

		is_game_over = false;
		is_slide_out_started = false;

		pos_img_winner_bar.x = -rs::img_winner_bar.getwidth();
		pos_img_winner_bar.y = (getheight() - rs::img_winner_bar.getheight()) / 2;
		pos_x_img_winner_bar_dst = (getwidth() - rs::img_winner_bar.getwidth()) / 2;
		
		pos_img_winner_text.x = -rs::img_1P_winner.getwidth();
		pos_img_winner_text.y = (getheight() - rs::img_1P_winner.getheight()) / 2;
		pos_x_img_winner_text_dst = (getwidth() - rs::img_1P_winner.getwidth()) / 2;


		timer_winner_slide_in.restart();
		timer_winner_slide_in.set_wait_time(2500);
		timer_winner_slide_in.set_one_shot(true);
		timer_winner_slide_in.set_callback([&]() {is_slide_out_started = true; });


		timer_winner_slide_out.restart();
		timer_winner_slide_out.set_wait_time(1000);
		timer_winner_slide_out.set_one_shot(true);
		timer_winner_slide_out.set_callback([&]() {scene_manager.switch_to(SceneManager::SceneType::Menu); });


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

		for (auto it = bullet_list.begin(); it != bullet_list.end();) {
			if ((*it)->check_can_remove()) {
				delete (*it);
				it = bullet_list.erase(it);
			}
			else
				it++;
		}

		for (Bullet* bullet : bullet_list) {
			bullet->on_update(delta);
		}

		player_1->on_update(delta);
		player_2->on_update(delta);

		main_camera.on_update(delta);

		if (!is_game_over && (player_1->get_hp() <= 0 || player_2->get_hp() <= 0)) {
			mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
			mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
			is_game_over = true;
		}


		if (is_game_over) {
			pos_img_winner_bar.x += (int)(speed_winner_bar * delta);
			pos_img_winner_text.x += (int)(speed_winner_text * delta);

			if (!is_slide_out_started) {
				timer_winner_slide_in.on_update(delta);
				if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst)
					pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
				if (pos_img_winner_text.x > pos_x_img_winner_text_dst)
					pos_img_winner_text.x = pos_x_img_winner_text_dst;
			}
			else
				timer_winner_slide_out.on_update(delta);
		}
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

		if (!is_game_over) {
			status_bar_1P.on_draw();
			status_bar_2P.on_draw();
		}
		else {
			ut::putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &rs::img_winner_bar);
			ut::putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y,
				player_1->get_hp() > 0 ? &rs::img_1P_winner : &rs::img_2P_winner);
		}
	}

	void on_input(const ExMessage& msg) {
		player_1->on_input(msg);
		player_2->on_input(msg);

		/*switch (msg.message) {
		case WM_KEYDOWN:
			if (msg.vkcode == 0x51) {
				is_debug = !is_debug;
			}
			break;
		}*/
	}

	void on_exit() {
		delete player_1;
		player_1 = nullptr;
		delete player_2;
		player_2 = nullptr;

		bullet_list.clear();
		main_camera.reset();
	}
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	StatusBar status_bar_1P;
	StatusBar status_bar_2P;

	const float speed_winner_bar = 3.0f;
	const float speed_winner_text = 1.5f;

	bool is_game_over = false;
	POINT pos_img_winner_bar = { 0 };
	POINT pos_img_winner_text = { 0 };
	int pos_x_img_winner_bar_dst = 0;
	int pos_x_img_winner_text_dst = 0;
	Timer timer_winner_slide_in;
	Timer timer_winner_slide_out;
	bool is_slide_out_started = false;
};