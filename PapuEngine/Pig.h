#pragma once
#include "Agent.h"
#include "InputManager.h"

class Pig : public Agent
{
private:
	bool stop = false;
public:
	Pig(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture);
	void update();
	void setPosition(glm::vec2 position) {
		_position = position;
	}
	void changeTexture(std::string texturePath) {
		_texturePath = texturePath;
	}
	void setStop(bool _stop) {
		stop = _stop;
	}
	bool getStop() {
		return stop;
	}
	std::string getTexture();
	~Pig();
};

