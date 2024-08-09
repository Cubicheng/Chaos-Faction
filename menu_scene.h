#pragma once

# include "scene.h"
# include "scene_manager.h"
# include "atlas.h"
# include "animation.h"
# include "camera.h"
# include "timer.h"
# include <iostream>

class MenuScene :public Scene{

public:
	MenuScene() {

	}
	~MenuScene() {

	}

	void on_enter() {
		
	}

	void on_update(int delta) {
		
	}

	void on_draw() {

	}

	void on_input(const ExMessage& msg) {
		
	}

	void on_exit() {

	}

private:
	Animation animation_peashooter_run_right;
	Camera camera;
	Timer timer;
};