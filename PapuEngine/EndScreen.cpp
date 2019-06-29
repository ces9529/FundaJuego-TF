#include "EndScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>


EndScreen::~EndScreen()
{
}

EndScreen::EndScreen(Window * window) :
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_OVER;
}

void EndScreen::initGUI()
{
	_spriteFont = new SpriteFont("Fonts/angrybirds-regular.ttf", 144);
	background = new Background("Textures/winscreen.png");
	button = new Button("Textures/button_reset.png",80, 80, glm::vec2(350, 50));
	btn_exit = new Button("Textures/button_quit.png", 40, 40, glm::vec2(710, 10));
}

void EndScreen::initSystem()
{
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void EndScreen::destroy()
{
	delete background;
	delete button;
	delete btn_exit;
	delete _spriteFont;
}

void EndScreen::onExit(){}

void EndScreen::onEntry()
{
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	initGUI();
}

void EndScreen::update()
{
	_camera2D.update();
	if (button->click(_game->_inputManager.getMouseCoords())) {
		button->setColor(ColorRGBA(180, 180, 180, 255));
		if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			if (
				!button->getClicked()
				) {
				button->setClicked(true);
				std::cout << "Back!" << std::endl;
				_currentState = ScreenState::CHANGE_PREVIOUS;
			}
		}
	}
	else {
		button->setColor(ColorRGBA(255, 255, 255, 255));
	}

	if (btn_exit->click(_game->_inputManager.getMouseCoords())) {
		btn_exit->setColor(ColorRGBA(180, 180, 180, 255));
		if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			if (
				!btn_exit->getClicked()
				) {
				btn_exit->setClicked(true);
				std::cout << "EXIT!" << std::endl;
				_currentState = ScreenState::EXIT_APPLICATION;
			}
		}
	}
	else {
		btn_exit->setColor(ColorRGBA(255, 255, 255, 255));
	}

	checkInput();
}

void EndScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		_game->onSDLEvent(event);
	}
}

void EndScreen::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	char buffer[256];

	_spriteBatch.begin();
	background->draw(_spriteBatch);

	button->draw(_spriteBatch);
	btn_exit->draw(_spriteBatch);

	sprintf(buffer, "VICTORIA");

	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(270, 380), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 200, 0, 255));


	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void EndScreen::build() {}

int EndScreen::getNextScreen() const
{
	return SCREEN_INDEX_MENU;
}

int EndScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_GAME;
}


