# include <graphics.h>
# include "frame_timer.h"
# include "menu_scene.h"
# include "game_scene.h"
# include "scene_manager.h"
# include "selector_scene.h"
# include "util.h"
# include "atlas.h"

#pragma comment(lib,"Winmm.lib")

IMAGE img_menu_background;//���˵�����

IMAGE img_VS;//VS ������
IMAGE img_1P;//1P �ı�
IMAGE img_2P;//2P �ı�

IMAGE img_1P_desc;//1P ��λ����

IMAGE img_2P_desc;//2P ��λ����
IMAGE img_gravestone_left;//�������Ĺ��
IMAGE img_gravestone_right;//�����ҵ�Ĺ��
IMAGE img_selector_tip;//ѡ�ǽ�����ʾ��Ϣ�ı�
IMAGE img_selector_background;//ѡ�ǽ��汳��ͼ
IMAGE img_1P_selector_btn_idle_left;//1P ����ѡ��ťĬ��״̬
IMAGE img_1P_selector_btn_idle_right;//1P ����ѡ��ťĬ��״̬
IMAGE img_1P_selector_btn_down_left;//1P ����ѡ��ť����״̬
IMAGE img_1P_selector_btn_down_right;//1P ����ѡ��ť����״̬
IMAGE img_2P_selector_btn_idle_left;//2P ����ѡ��ťĬ��״̬
IMAGE img_2P_selector_btn_idle_right;//2P ����ѡ��ťĬ��״̬
IMAGE img_2P_selector_btn_down_left;//2P ����ѡ��ť����״̬
IMAGE img_2P_selector_btn_down_right;//2P ����ѡ��ť����״̬
IMAGE img_peashooter_selector_background_left;//ѡ�ǽ��泯�����������
IMAGE img_peashooter_selector_background_right;//ѡ�ǽ��泯���ҵ�������
IMAGE img_sunflower_selector_background_left;//ѡ�ǽ��泯��������տ�
IMAGE img_sunflower_selector_background_right;//ѡ�ǽ��泯���ҵ����տ�

IMAGE img_sky;//���
IMAGE img_hills;//ɽ��
IMAGE img_platform_large;//����ƽ̨
IMAGE img_platform_small;//С��ƽ̨

IMAGE img_1P_cursor;//1P ָʾ���
IMAGE img_2P_cursor;//2P ָʾ���

IMAGE img_1P_winner;//1P ��ʤ�ı�ͼƬ
IMAGE img_2P_winner;//2P ��ʤ�ı�ͼƬ
IMAGE img_winner_bar;//��ʤ����ı�����ͼƬ


IMAGE img_avatar_peashooter;//������ͷ��ͼƬ
IMAGE img_avatar_sunflower;//���տ�ͷ��ͼƬ


// ������ͼ��
Atlas atlas_peashooter_idle_left;//�������Ĭ�϶���
Atlas atlas_peashooter_idle_right;//�����ҵ�Ĭ�϶���
Atlas atlas_peashooter_run_left;//������ı��ܶ���
Atlas atlas_peashooter_run_right;//�����ҵı��ܶ���
Atlas atlas_peashooter_attack_ex_left;//����������⹥������
Atlas atlas_peashooter_attack_ex_right;//�����ҵ����⹥������
Atlas atlas_peashooter_die_left;//���������������
Atlas atlas_peashooter_die_right;//�����ҵ���������

//���տ�ͼ��
Atlas atlas_sunflower_idle_left;//�������Ĭ�϶���
Atlas atlas_sunflower_idle_right;//�����ҵ�Ĭ�϶���
Atlas atlas_sunflower_run_left;//������ı��ܶ���
Atlas atlas_sunflower_run_right;//�����ҵı��ܶ���
Atlas atlas_sunflower_attack_ex_left;//����������⹥������
Atlas atlas_sunflower_attack_ex_right;//�����ҵ����⹥������
Atlas atlas_sunflower_die_left;//���������������
Atlas atlas_sunflower_die_right;//�����ҵ���������


IMAGE img_pea;//��ͼƬ
Atlas atlas_pea_break;//�����鶯��ͼ��
Atlas atlas_sun;//�չ⶯��ͼ��
Atlas atlas_sun_explode;//�չⱬը����ͼ��
Atlas atlas_sun_ex;//�����չ⶯��ͼ��
Atlas atlas_sun_ex_explode;//�����չⱬը����ͼ��
Atlas atlas_sun_text;//"��"�ı�����ͼ��

Atlas atlas_run_effect;//������Ч����ͼ��
Atlas atlas_jump_effect;//��Ծ��Ч����ͼ��
Atlas atlas_land_effect;


void load_game_resources() {

	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_VS, _T("resources/vs.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	ut::flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1p_selector_btn_idle.png"));
	ut::flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1p_selector_btn_down.png"));
	ut::flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	ut::flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	ut::flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));

	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));

	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	ut::flip_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	ut::flip_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	ut::flip_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	ut::flip_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
	ut::flip_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	ut::flip_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	ut::flip_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	ut::flip_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("resources/pea.png"));
	atlas_pea_break.load_from_file(_T("resources/pea_break_%d. png"), 3);
	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);

	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
	loadimage(&img_winner_bar, _T("resources/winnner_bar.png"));

	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 8, NULL);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
}

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
SceneManager scene_manager;

void init() {
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();
	load_game_resources();

	initgraph(1280, 720, EX_SHOWCONSOLE);

	scene_manager.set_current_scene(menu_scene);

	BeginBatchDraw();
}

void loop() {

	ExMessage msg;

	while (true) {

		timer::frame_start_time = GetTickCount();

		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;

		scene_manager.on_update(delta_tick);

		last_tick_time = current_tick_time;

		cleardevice();

		scene_manager.on_draw();

		FlushBatchDraw();

		timer::frame_sleep();
	}

}

int main() {

	init();

	loop();

	return 0;
}