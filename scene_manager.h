#pragma once

# include "scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	enum class SceneType {
		Menu = 0,
		Game,
		Selector
	};

	void set_current_scene(Scene* scene) {
		current_scene = scene;
		current_scene->on_enter();
	}

	void switch_to(SceneType type) {
		current_scene->on_exit();
		switch (type) {
		case SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneType::Game:
			current_scene = game_scene;
			break;
		case SceneType::Selector:
			current_scene = selector_scene;
			break;
		default:
			break;
		}
		current_scene->on_enter();
	}

	void on_update(int delta) {
		current_scene->on_update(delta);
	}

	void on_draw() {
		current_scene->on_draw();
	}

	void on_input(const ExMessage & msg){
		current_scene->on_input(msg);
	}

private:
	Scene* current_scene = nullptr;
};