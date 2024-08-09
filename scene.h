#pragma once

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() = 0;
	virtual void on_update(int delta) = 0;
	virtual void on_draw() = 0;
	virtual void on_input(const ExMessage & msg) = 0;
	virtual void on_exit() = 0;
private:


};