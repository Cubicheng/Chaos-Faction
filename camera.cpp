#include "camera.h"

Camera::Camera(){
    timer_shake.set_one_shot(true);
    timer_shake.set_callback([&]() {
        is_shaking = false;
        reset();
        });
}

const Vector2& Camera::get_position() const{
    return position;
}

void Camera::reset(){
    position.x = 0;
    position.y = 0;
}

void Camera::on_update(int delta){
    timer_shake.on_update(delta);
    if (is_shaking) {
        position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
        position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
    }
}

void Camera::shake(float strength, int duration){
    is_shaking = true;
    shaking_strength = strength;

    timer_shake.set_wait_time(duration);
    timer_shake.restart();
}
