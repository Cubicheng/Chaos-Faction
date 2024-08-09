#include "menu_scene.h"
# include "scene_manager.h"
# include "atlas.h"

# include <iostream>

extern Atlas atlas_peashooter_run_right;

extern SceneManager scene_manager;

void MenuScene::on_enter() {
	
}

void MenuScene::on_update(int delta) {
	animation_peashooter_run_right.on_update(delta);
}

void MenuScene::on_draw() {
	const Vector2& pos_camera = camera.get_position();
	animation_peashooter_run_right.on_draw((int)(100-pos_camera.x), (int)(100 - pos_camera.y));
}

void MenuScene::on_input(const ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {
		scene_manager.switch_to(SceneManager::SceneType::Game);
	}
}

void MenuScene::on_exit() {
	std::cout << "exit menu scene" << std::endl;
}
