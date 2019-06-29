#include "Box.h"


Box::Box(float agent_width, float agent_height, glm::vec2 position, std::string texture)
	: Agent(agent_width, agent_height, position, texture)
{
	
}

void Box::update()
{
	
}

std::string Box::getTexture()
{
	return std::string();
}

Box::~Box()
{
}
