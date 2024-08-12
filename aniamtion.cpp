# include "animation.h"
# include "util.h"


void Animation::reset() {
	timer = 0;
	idx_frame = 0;
}

void Animation::set_atlas(Atlas* new_atlas) {
	reset();
	atlas = new_atlas;
}

void Animation::set_loop(bool flag) {
	is_loop = flag;
}

void Animation::set_interval(int ms) {
	interval = ms;
}

int Animation::get_idx_frame() {
	return idx_frame;
}

IMAGE* Animation::get_frame() {
	return atlas->get_image(idx_frame);
}

bool Animation::check_finished() {
	if (is_loop) return false;
	return (idx_frame == atlas->get_size() - 1);
}

void Animation::on_update(int delta){
	timer += delta;
	if (timer >= interval) {
		timer = 0;
		idx_frame++;
		if (idx_frame >= atlas->get_size()-1) {
			idx_frame = is_loop ? 0 : atlas->get_size() - 1;
			if (!is_loop && callback) {
				callback();
			}
		}
	}
}

void Animation::on_draw(const Camera& camera, int x, int y) const {
	ut::putimage_alpha(camera, x, y, atlas->get_image(idx_frame));
}

void Animation::set_callback(std::function<void()> callback){
	this->callback = callback;
}
