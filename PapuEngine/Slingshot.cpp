#include "Slingshot.h"




Slingshot::Slingshot(float agent_width, float agent_height, glm::vec2 position, std::string texture)
	: Agent(agent_width, agent_height, position, texture)
{
}

void Slingshot::update()
{
}

std::string Slingshot::getTexture()
{
	return std::string();
}

Slingshot::~Slingshot()
{
}
