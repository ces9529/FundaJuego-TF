#include "Pig.h"



Pig::Pig(float agent_width, float agent_height, glm::vec2 position, std::string texture)
	: Agent(agent_width, agent_height, position, texture)
{
}

void Pig::update()
{
	_position.y -= 1;
}

std::string Pig::getTexture()
{
	return _texturePath;
}

Pig::~Pig()
{
}
