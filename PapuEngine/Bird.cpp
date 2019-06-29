#include "Bird.h"
#include <SDL\SDL.h>
#include <math.h>
#include <iostream>

using namespace std;
Bird::Bird(float agent_width, float agent_height, glm::vec2 position, std::string texture, InputManager * _inputManager)
	: Agent(agent_width, agent_height, position, texture)
{
	inputManager = _inputManager;
	//_velocidad = velocidad;
	//_theta = theta * Pi / 180.0;
}

void Bird::update()
{
	//_theta = (atan(fabs(_y_o - _y) / fabs(_x_o - _x))) * (180 / Pi);
	//_s = _x_o - _x;
	if (!_fly) 
	{
		_position.y = 500 - inputManager->getMouseCoords().y - _agent_height / 2;
		_position.x = inputManager->getMouseCoords().x - _agent_width / 2;
	}

	//_position.x = _x_o + (_s * fabs(cos(_theta)) * fabs(cos(_theta)) * _t);
	//_position.y = _y_o + (_s * fabs(sin(_theta)) * _t - (gravedad * (_t * _t) / 2.0));
	//_t += 0.25;
}

void Bird::flying()
{
	//_theta *= Pi / 180.0;
	_position.x = _x_o + short(_s * fabs(cos(_theta)) * _t);
	_position.y = _y_o + short(_s * fabs(sin(_theta)) * _t - (gravedad * (_t * _t) / 2.0));
	_t += 0.08f;
}

void Bird::setColor(ColorRGBA _color)
{
	color = _color;
}

bool Bird::click(glm::vec2 _positionM)
{
	bool result = (_positionM.x > _position.x)
		&& (_positionM.x < _position.x + _agent_width)
		&& (500 - _positionM.y > _position.y)
		&& (500 - _positionM.y < _position.y + _agent_height);
	return result;
}

std::string Bird::getTexture()
{
	return std::string();
}

Bird::~Bird()
{
}
