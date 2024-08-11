#pragma once

# include "scene.h"
# include "scene_manager.h"
# include "resource.h"
# include "animation.h"
# include "util.h"
# include "peashooter_player.h"
# include "sunflower_player.h"

extern Player* player_1;
extern Player* player_2;

extern SceneManager scene_manager;

class SelectorScene :public Scene {
public:
	SelectorScene() {

	}
	~SelectorScene() {

	}

	void on_enter() {

		animation_peashooter.set_atlas(&rs::atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&rs::atlas_sunflower_idle_right);
		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);

		static const int OFFSET_X = 50;

		pos_img_VS.x = (getwidth() - rs::img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - rs::img_VS.getheight()) / 2;

		pos_img_tip.x = (getwidth() - rs::img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;


		pos_img_1P.x = (getwidth() / 2 - rs::img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;

		pos_img_2P.x = getwidth()/2 + (getwidth() / 2 - rs::img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;


		pos_img_1P_desc.x = (getwidth() / 2 - rs::img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;

		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - rs::img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;


		pos_img_1P_gravestone.x = (getwidth() / 2 - rs::img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + rs::img_1P.getheight() + 35;

		pos_img_2P_gravestone.x = getwidth() / 2+(getwidth() / 2 - rs::img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;


		pos_animation_1P.x = (getwidth() / 2 - rs::atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 80;

		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - rs::atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;

		pos_img_1P_name.y = pos_animation_1P.y + 155;
		pos_img_2P_name.y = pos_img_1P_name.y;


		pos_img_1P_selector_btn_left.x = pos_img_1P_gravestone.x - rs::img_1P_selector_btn_idle_left.getwidth();
		pos_img_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (rs::img_gravestone_right.getheight() - rs::img_1P_selector_btn_idle_left.getwidth()) / 2;
		pos_img_1P_selector_btn_right.x = pos_img_1P_gravestone.x + rs::img_gravestone_right.getwidth();
		pos_img_1P_selector_btn_right.y = pos_img_1P_selector_btn_left.y;

		pos_img_2P_selector_btn_left.x = pos_img_2P_gravestone.x - rs::img_2P_selector_btn_idle_left.getwidth();
		pos_img_2P_selector_btn_left.y = pos_img_1P_selector_btn_left.y;
		pos_img_2P_selector_btn_right.x = pos_img_2P_gravestone.x + rs::img_gravestone_left.getwidth();
		pos_img_2P_selector_btn_right.y = pos_img_1P_selector_btn_right.y;
	}

	void on_update(int delta) {
		animation_peashooter.on_update(delta);
		animation_sunflower.on_update(delta);
		selector_background_scroll_offset_x += 5;
		if (selector_background_scroll_offset_x >= rs::img_peashooter_selector_background_left.getwidth())
			selector_background_scroll_offset_x = 0;
	}

	void on_draw(const Camera& camera) {
		IMAGE* img_p1_selector_background = nullptr;
		IMAGE* img_p2_selector_background = nullptr;

		switch (player_type_2) {
		case PlayerType::Peashooter:
			img_p1_selector_background = &rs::img_peashooter_selector_background_right;
			break;
		case PlayerType::Sunflower:
			img_p1_selector_background = &rs::img_sunflower_selector_background_right;
			break;
		default:
			img_p1_selector_background = &rs::img_peashooter_selector_background_right;
		}

		switch (player_type_1) {
		case PlayerType::Peashooter:
			img_p2_selector_background = &rs::img_peashooter_selector_background_left;
			break;
		case PlayerType::Sunflower:
			img_p2_selector_background = &rs::img_sunflower_selector_background_left;
			break;
		default:
			img_p2_selector_background = &rs::img_peashooter_selector_background_left;
		}


		putimage(0, 0, &rs::img_selector_background);

		ut::putimage_alpha(selector_background_scroll_offset_x-img_p1_selector_background->getwidth(),0,img_p1_selector_background);

		ut::putimage_alpha(selector_background_scroll_offset_x, 0,
			img_p1_selector_background->getwidth() - selector_background_scroll_offset_x, 0, img_p1_selector_background, 0, 0);


		ut::putimage_alpha(getwidth()-img_p2_selector_background->getwidth(), 0,
			img_p2_selector_background->getwidth() - selector_background_scroll_offset_x, 0, img_p2_selector_background, selector_background_scroll_offset_x, 0);

		ut::putimage_alpha(getwidth() - selector_background_scroll_offset_x, 0, img_p2_selector_background);



		ut::putimage_alpha(pos_img_VS.x, pos_img_VS.y, &rs::img_VS);

		ut::putimage_alpha(pos_img_1P.x, pos_img_1P.y, &rs::img_1P);
		ut::putimage_alpha(pos_img_2P.x, pos_img_2P.y, &rs::img_2P);

		ut::putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &rs::img_gravestone_right);
		ut::putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &rs::img_gravestone_left);

		switch (player_type_1) {
		case PlayerType::Peashooter: 
			animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (rs::img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
			break;
		case PlayerType::Sunflower: 
			animation_sunflower.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (rs::img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
			break;
		}

		switch (player_type_2) {
		case PlayerType::Peashooter:
			animation_peashooter.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (rs::img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
			break;
		case PlayerType::Sunflower:
			animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (rs::img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
			break;
		}

		ut::putimage_alpha(pos_img_1P_selector_btn_left.x, pos_img_1P_selector_btn_left.y,
			is_btn_1P_left_down ? &rs::img_1P_selector_btn_down_left : &rs::img_1P_selector_btn_idle_left);

		ut::putimage_alpha(pos_img_1P_selector_btn_right.x, pos_img_1P_selector_btn_right.y,
			is_btn_1P_right_down ? &rs::img_1P_selector_btn_down_right : &rs::img_1P_selector_btn_idle_right);

		ut::putimage_alpha(pos_img_2P_selector_btn_left.x, pos_img_2P_selector_btn_left.y,
			is_btn_2P_left_down ? &rs::img_2P_selector_btn_down_left : &rs::img_2P_selector_btn_idle_left);

		ut::putimage_alpha(pos_img_2P_selector_btn_right.x, pos_img_2P_selector_btn_right.y,
			is_btn_2P_right_down ? &rs::img_2P_selector_btn_down_right : &rs::img_2P_selector_btn_idle_right);


		ut::putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &rs::img_1P_desc);
		ut::putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &rs::img_2P_desc);


		ut::putimage_alpha(pos_img_tip.x, pos_img_tip.y, &rs::img_selector_tip);
	}

	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case 0x41:
				is_btn_1P_left_down = true;
				break;
			case 0x44:
				is_btn_1P_right_down = true;
				break;
			case VK_LEFT:
				is_btn_2P_left_down = true;
				break;
			case VK_RIGHT:
				is_btn_2P_right_down = true;
				break;
			}
		}
		else if(msg.message == WM_KEYUP){
			switch (msg.vkcode) {
			case 0x41:
				is_btn_1P_left_down = false;
				player_type_1 = (PlayerType)((PlayerType::Invalid + player_type_1 - 1) % PlayerType::Invalid);
				break;
			case 0x44:
				is_btn_1P_right_down = false;
				player_type_1 = (PlayerType)((player_type_1 + 1) % PlayerType::Invalid);
				break;
			case VK_LEFT:
				is_btn_2P_left_down = false;
				player_type_2 = (PlayerType)((PlayerType::Invalid + player_type_2 - 1) % PlayerType::Invalid);
				break;
			case VK_RIGHT:
				is_btn_2P_right_down = false;
				player_type_2 = (PlayerType)((player_type_2 + 1) % PlayerType::Invalid);
				break;
			case VK_RETURN:
				scene_manager.switch_to(SceneManager::SceneType::Game);
				break;
			}
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
		}
	}

	void on_exit() {
		switch (player_type_1) {
		case PlayerType::Peashooter:
			player_1 = new PeashooterPlayer();
			break;
		case PlayerType::Sunflower:
			player_1 = new SunflowerPlayer();
			break;
		}

		player_1->set_id(Player::PlayerID::P1);

		switch (player_type_2) {
		case PlayerType::Peashooter:
			player_2 = new PeashooterPlayer();
			break;
		case PlayerType::Sunflower:
			player_2 = new SunflowerPlayer();
			break;
		}

		player_2->set_id(Player::PlayerID::P2);
	}

	void outtextxy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}

private:
	enum PlayerType {
		Peashooter = 0,
		Sunflower,
		Invalid
	};

private:

	POINT pos_img_VS = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };
	POINT pos_animation_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };

	POINT pos_img_1P_selector_btn_right = { 0 };
	POINT pos_img_1P_selector_btn_left = { 0 };
	
	POINT pos_img_2P_selector_btn_right = { 0 };
	POINT pos_img_2P_selector_btn_left = { 0 };

	Animation animation_peashooter;
	Animation animation_sunflower;

	PlayerType player_type_1 = PlayerType::Peashooter;
	PlayerType player_type_2 = PlayerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("ÕÒ∂∫…‰ ÷");
	LPCTSTR str_sunflower_name = _T("¡˙»’ø˚");

	int selector_background_scroll_offset_x = 0;

	bool is_btn_1P_left_down = false;
	bool is_btn_1P_right_down = false;
	bool is_btn_2P_left_down = false;
	bool is_btn_2P_right_down = false;
};