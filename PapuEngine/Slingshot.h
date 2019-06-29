#pragma once
#include "Agent.h"
class Slingshot : public Agent
{
public:
	Slingshot(float agent_width,
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

	void drawLine(int x0, int y0, int x, int y) {
		glColor3f(255, 255, 255);
		glBegin(GL_LINES);
			glVertex3f(x0, y0, 0.0f);
			glVertex3f(x, y, 0.0f);
		glEnd();
		glFlush();
	}
	std::string getTexture();
	~Slingshot();
};

