#pragma once

# include "camera.h"
# include "graphics.h"
# include "vector2.h"
# include "animation.h"
# include "platform.h"
# include "player_id.h"
# include "bullet.h"
# include "particle.h"

extern std::vector<Platform> platform_list;
extern std::vector<Bullet*> bullet_list;

extern Camera main_camera;

class Player {
public:

	Player() {

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);
		timer_attack_cd.set_callback([&]() {can_attack = true; });


		timer_invulnerable.set_wait_time(750);
		timer_invulnerable.set_one_shot(true);
		timer_invulnerable.set_callback([&]() {
			is_invulnerable = false;
			timer_invulnerable_blink.pause();
			});

		timer_invulnerable_blink.set_wait_time(75);
		timer_invulnerable_blink.set_callback([&]() {is_showing_sketch_frame = !is_showing_sketch_frame; });


		timer_run_effect_generation.set_wait_time(75);
		timer_run_effect_generation.set_callback([&]() {
			Vector2 particle_position;
			IMAGE* frame = rs::atlas_run_effect.get_image(0);
			particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			particle_position.y = position.y + size.y - frame->getheight();
			particle_list.push_back(new Particle(particle_position,&rs::atlas_run_effect,45));
			});


		timer_die_effect_generation.set_wait_time(35);
		timer_die_effect_generation.set_callback([&]() {
			Vector2 particle_position;
			IMAGE* frame = rs::atlas_run_effect.get_image(0);
			particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			particle_position.y = position.y + size.y - frame->getheight();
			particle_list.push_back(new Particle(particle_position, &rs::atlas_run_effect, 150));
			});



		animation_jump_effect.set_atlas(&rs::atlas_jump_effect);
		animation_jump_effect.set_interval(25);
		animation_jump_effect.set_loop(false);
		animation_jump_effect.set_callback([&]() {is_jump_effect_visible = false; });

		animation_land_effect.set_atlas(&rs::atlas_land_effect);
		animation_land_effect.set_interval(50);
		animation_land_effect.set_loop(false);
		animation_land_effect.set_callback([&]() {is_land_effect_visible = false; });
	}

	~Player() = default;

	virtual void on_update(int delta) {

		int direction = is_right_key_down - is_left_key_down;

		if (is_attacking_ex)
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		else {
			if (direction != 0) {
				is_facing_right = direction > 0;
				current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
				float distance = direction * run_velocity * delta;
				on_run(distance);
			}
			else {
				current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
				timer_run_effect_generation.pause();
			}
		}

		current_animation->on_update(delta);

		animation_jump_effect.on_update(delta);
		animation_land_effect.on_update(delta);

		timer_attack_cd.on_update(delta);
		timer_invulnerable.on_update(delta);
		timer_invulnerable_blink.on_update(delta);
		timer_run_effect_generation.on_update(delta);


		if (hp <= 0)
			timer_die_effect_generation.on_update(delta);

		for (auto it = particle_list.begin(); it != particle_list.end();) {
			if (!(*it)->check_valid()) {
				delete (*it);
				it = particle_list.erase(it);
			}
			else it++;
		}

		for (Particle* particle : particle_list) {
			particle->on_update(delta);
		}
			
		if (is_showing_sketch_frame && is_invulnerable)
			ut::sketch_image(current_animation->get_frame(), &img_sketch);

		move_and_collide(delta);
	}

	virtual void on_run(float distance) {
		if (is_attacking_ex)
			return;
		position.x += distance;

		timer_run_effect_generation.resume();
	}

	virtual void on_draw(const Camera& camera) {
		if (is_jump_effect_visible)
			animation_jump_effect.on_draw(camera, position_jump_effect.x, position_jump_effect.y);

		if (is_land_effect_visible)
			animation_land_effect.on_draw(camera, position_land_effect.x, position_land_effect.y);


		for (Particle* particle : particle_list) {
			particle->on_draw(camera);
		}


		if (hp > 0 && is_showing_sketch_frame && is_invulnerable)
			ut::putimage_alpha(camera, position.x, position.y, &img_sketch);
		else
			current_animation->on_draw(camera, (int)position.x, (int)position.y);


		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));
			ut::draw_line(camera, position.x, position.y, position.x+size.x, position.y);
			ut::draw_line(camera, position.x + size.x, position.y, position.x + size.x, position.y+size.y);
			ut::draw_line(camera, position.x + size.x, position.y + size.y, position.x, position.y+size.y);
			ut::draw_line(camera, position.x, position.y + size.y, position.x, position.y);
		}
	}

	virtual void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_KEYDOWN:
			switch (id) {
			case PlayerID::P1:
				switch (msg.vkcode) {
				case 0x41:
					is_left_key_down = true;
					break;
				case 0x44:
					is_right_key_down = true;
					break;
				case 0x57:
					on_jump();
					break;
				case 0x46:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case 0x47:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode) {
				case VK_LEFT:
					is_left_key_down = true;
					break;
				case VK_RIGHT:
					is_right_key_down = true;
					break;
				case VK_UP:
					on_jump();
					break;
				case VK_OEM_PERIOD:
					if (can_attack) {
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case VK_OEM_2:
					if (mp >= 100) {
						on_attack_ex();
						mp = 0;
					}
					break;
				}
			}
			break;
		case WM_KEYUP:
			switch (id) {
			case PlayerID::P1:
				switch (msg.vkcode) {
				case 0x41:
					is_left_key_down = false;
					break;
				case 0x44:
					is_right_key_down = false;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode) {
				case VK_LEFT:
					is_left_key_down = false;
					break;
				case VK_RIGHT:
					is_right_key_down = false;
					break;
				}
			}
			break;
		}
	}

	void set_id(PlayerID id) {
		this->id = id;
	}

	void set_position(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void set_facing_right(bool is_facing_right) {
		this->is_facing_right = is_facing_right;
	}

	virtual void on_jump() {
		if (velocity.y != 0 || is_attacking_ex) return;
		velocity.y += jump_velocity;

		is_jump_effect_visible = true;
		animation_jump_effect.reset();

		IMAGE* frame = animation_jump_effect.get_frame();
		position_jump_effect.x = position.x + (size.x - frame->getwidth()) / 2;
		position_jump_effect.y = position.y + size.y - frame->getheight();
	}

	virtual void on_attack() = 0;

	virtual void on_attack_ex() = 0;

	const Vector2& get_position() {
		return position;
	}

	const Vector2& get_size() {
		return size;
	}

	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable.restart();
		timer_invulnerable_blink.resume();
	}

	int get_hp() {
		return hp;
	}

	int get_mp() {
		return mp;
	}

	IMAGE* get_img_avatar() {
		return img_avatar;
	}

	virtual void on_land() {
		is_land_effect_visible = true;
		animation_land_effect.reset();

		IMAGE* frame = animation_land_effect.get_frame();
		position_land_effect.x = position.x + (size.x - frame->getwidth()) / 2;
		position_land_effect.y = position.y + size.y - frame->getheight();
	}

protected:

	void move_and_collide(int delta) {
		float last_frame_velocity = velocity.y;
		velocity.y += gravity * delta;
		position = position + velocity * delta;
		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.collision_shape;
				bool is_collide_x = (shape.left <= position.x && position.x <= shape.right ||
					shape.left <= position.x + size.x && position.x + size.x <= shape.right);
				bool is_collide_y = (position.y <= shape.y && shape.y <= position.y + size.y);
				if (is_collide_x && is_collide_y) {
					float delta_pos_y = velocity.y * delta;
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;
					if (last_tick_foot_pos_y <= shape.y) {
						position.y = shape.y - size.y;
						velocity.y = 0;

						if (last_frame_velocity != 0)
							on_land();
						break;
					}
				}
			}
		}

		if (is_invulnerable) return;
		for (Bullet* bullet : bullet_list) {
			if (!bullet->get_valid() || bullet->get_collide_target() != id)
				continue;
			if (bullet->check_collision(position, size)) {
				make_invulnerable();
				bullet->set_valid(false);
				bullet->on_collide();
				hp -= bullet->get_damage();
			}
		}
	}

	int mp = 0;
	int hp = 100;

	const float run_velocity = 0.55f;
	const float gravity = 1.6e-3f;
	const float jump_velocity = -0.85f;

	Vector2 size;
	Vector2 position;
	Vector2 velocity;

	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;


	Animation animation_jump_effect;
	Animation animation_land_effect;

	bool is_jump_effect_visible = false;
	bool is_land_effect_visible = false;

	Vector2 position_jump_effect;
	Vector2 position_land_effect;

	IMAGE img_sketch;


	Animation* current_animation = nullptr;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_facing_right = true;
	bool is_attacking_ex = false;

	bool is_invulnerable = false;
	bool is_showing_sketch_frame = false;
	Timer timer_invulnerable;
	Timer timer_invulnerable_blink;

	int attack_cd = 500;
	bool can_attack = true;
	Timer timer_attack_cd;

	IMAGE* img_avatar = nullptr;

	PlayerID id;

	std::vector<Particle*> particle_list;

	Timer timer_run_effect_generation;
	Timer timer_die_effect_generation;
};