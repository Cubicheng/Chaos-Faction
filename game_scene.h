#pragma once

# include "scene.h"
# include "scene_manager.h"
# include <iostream>

extern SceneManager scene_manager;

class GameScene :public Scene{
public:
	GameScene() {

	}

	~GameScene() {

	}

	void on_enter() {
		std::cout << "enter game scene" << std::endl;
	}

	void on_update(int delta) {
		std::cout << "game scene running" << std::endl;
	}

	void on_draw() {
		outtextxy(10, 10, _T("game scene on drawing"));
	}

	void on_input(const ExMessage& msg) {
		if (msg.message == WM_KEYDOWN) {
			scene_manager.switch_to(SceneManager::SceneType::Menu);
		}
	}

	void on_exit() {
		std::cout << "exit game scene" << std::endl;
	}
};