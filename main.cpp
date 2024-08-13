# include <graphics.h>
# include "frame_timer.h"
# include "menu_scene.h"
# include "game_scene.h"
# include "scene_manager.h"
# include "selector_scene.h"
# include "util.h"
# include "atlas.h"
# include "resource.h"
# include "player.h"
# include "bullet.h"

#pragma comment(lib,"Winmm.lib")

bool is_debug = true;

Player* player_1 = nullptr;
Player* player_2 = nullptr;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
SceneManager scene_manager;

Camera main_camera;

void init() {
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();
	rs::load_game_resources();

	initgraph(1280, 720, EX_SHOWCONSOLE);

	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	scene_manager.set_current_scene(menu_scene);

	BeginBatchDraw();
}

void loop() {

	ExMessage msg;

	while (true) {

		frame_timer::frame_start_time = GetTickCount();

		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;

		scene_manager.on_update(delta_tick);

		last_tick_time = current_tick_time;

		cleardevice();

		scene_manager.on_draw(main_camera);

		FlushBatchDraw();

		frame_timer::frame_sleep();
	}

}

int main() {

	init();

	loop();

	return 0;
}