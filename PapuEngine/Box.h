#pragma once
#include <vector>
#include "Agent.h"
using namespace std;
class Box : public Agent
{
public:
	Box(float agent_width,
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
	std::string getTexture();

	~Box();
};

