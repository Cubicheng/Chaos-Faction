#pragma once

# include "scene.h"
# include "scene_manager.h"
# include "atlas.h"
# include "animation.h"
# include "camera.h"
# include "timer.h"
# include <iostream>

extern IMAGE img_menu_background;
extern SceneManager scene_manager;


class MenuScene :public Scene{

public:
	MenuScene() {

	}
	~MenuScene() {

	}

	void on_enter() {
		mciSendString(_T("play bgm_menu repeat from 0"),NULL,0,NULL);
	}

	void on_update(int delta) {
		
	}

	void on_draw(const Camera & camera) {
		putimage(0, 0, &img_menu_background);
	}

	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYUP) {
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager.switch_to(SceneManager::SceneType::Selector);
		}
	}

	void on_exit() {

	}

private:
	Animation animation_peashooter_run_right;
	Camera camera;
	Timer timer;
};