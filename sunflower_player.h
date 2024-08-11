#pragma once

# include "player.h"
# include "resource.h"
# include <iostream>

class SunflowerPlayer :public Player {
public:
	SunflowerPlayer() {
		animation_idle_left.set_atlas(&rs::atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&rs::atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&rs::atlas_sunflower_run_left);
		animation_run_right.set_atlas(&rs::atlas_sunflower_run_right);

		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);

		size.x = 96;
		size.y = 96;
	}
	~SunflowerPlayer() = default;

	void on_update(int delta) {
		Player::on_update(delta);
	}

private:


};