#pragma once
#include "Agent.h"
#include "InputManager.h"
#include <math.h>

#define gravedad 9.8
#define Pi 3.14159

#define PosIniX 190
#define PosIniY 200

class Bird : public Agent
{
private:
	InputManager* inputManager;
	bool clicked;
	int _x_o;
	int _y_o;
	int _x;
	int _y;
	bool _fly = false;
	float _s;
	float _t;
	float _theta;
public:
	Bird(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		InputManager* _inputManager);
	void update();
	void flying();
	void setPosition(glm::vec2 position) {
		_position = position;
	}
	void changeTexture(std::string texturePath) {
		_texturePath = texturePath;
	}

	void setXo(int x_o) {
		_x_o = x_o;
	}
	int getXo() {
		return _x_o;
	}
	void setYo(int y_o) {
		_y_o = y_o;
	}
	int getYo() {
		return _y_o;
	}

	void setX(int x) {
		_x = x;
	}
	int getX() {
		return _x;
	}
	void setY(int y) {
		_y = y;
	}
	int getY() {
		return _y;
	}

	float getS() {
		return _s;
	}
	void setS(float s) {
		_s = s;
	}

	float getT() {
		return _t;
	}
	void setT(float t) {
		_t = t;
	}

	float getTheta() {
		return _theta;
	}
	void setTheta(float theta) {
		_theta = theta;
	}

	bool getFly() {
		return _fly;
	}
	void setFly(bool fly) {
		_fly = fly;
	}

	int getWidth() {
		return _agent_width;
	}
	int getHeight() {
		return _agent_height;
	}

	void setColor(ColorRGBA _color);
	ColorRGBA getColor() const {
		return color;
	}

	bool click(glm::vec2 _position);
	void setClicked(bool _clicked) {
		clicked = _clicked;
	}
	bool getClicked()const {
		return clicked;
	}

	void reset() {

		_position = glm::vec2(PosIniX, PosIniY);
		_fly = false;
		_s = 0.0f;
		_t = 0.0f;
		_theta = 0.0f;
		_texturePath = "Textures/birdredStatic.png";

	}
	std::string getTexture();
	
	~Bird();
};

