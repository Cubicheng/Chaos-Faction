#pragma once

# include "graphics.h"
# include "util.h"

class StatusBar {
public:
	StatusBar() = default;
	~StatusBar() = default;

	void set_avatar(IMAGE* img) {
		img_avatar = img;
	}

	void set_position(int x, int y) {
		position.x = x;
		position.y = y;
	}

	void set_hp(int hp) {
		this->hp = hp;
	}

	void set_mp(int mp) {
		this->mp = mp;
	}

	void on_draw() {

		const int& x = position.x;
		const int& y = position.y;

		ut::putimage_alpha(x, y, img_avatar);
		 
		setfillcolor(RGB(5, 5, 5));
		solidroundrect(x + 100, y + 10, x + 100 + width + 6, y + 36, 8, 8);
		solidroundrect(x + 100, y + 45, x + 100 + width + 6, y + 71, 8, 8);

		setfillcolor(RGB(67, 47, 47));
		solidroundrect(x + 100, y + 10, x + 100 + width + 3, y + 33, 8, 8);
		solidroundrect(x + 100, y + 45, x + 100 + width + 3, y + 68, 8, 8);

		int hp_bar_width = width * max(0, hp) / 100;
		int mp_bar_width = width * min(100, mp) / 100;
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(x + 100, y + 10, x + 100 + hp_bar_width + 3, y + 33, 8, 8);
		setfillcolor(RGB(83, 131, 195));
		solidroundrect(x + 100, y + 45, x + 100 + mp_bar_width + 3, y + 68, 8, 8);


	}


private:
	const int width = 275;
	int hp;
	int mp;
	POINT position = { 0 };
	IMAGE* img_avatar = nullptr;
};