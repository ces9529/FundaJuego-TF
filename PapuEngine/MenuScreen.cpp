#include "MenuScreen.h"
#include "MyScreens.h"
#include "Game.h"
#include <iostream>

MenuScreen::MenuScreen(Window* window):
	_window(window), btnGameClicked(false)
{
	_screenIndex = SCREEN_INDEX_MENU;
}

void MenuScreen::initGUI() {
	_spriteFont = new SpriteFont("Fonts/angrybirds-regular.ttf", 144);
	_gFont = new SpriteFont("Fonts/angrybirds-regular.ttf", 35);
	background = new Background("Textures/background_Menu.png");
	button = new Button("Textures/button_play.png", 164, 84, glm::vec2(286, 152));
	btn_exit = new Button("Textures/button_quit.png", 40, 40, glm::vec2(710, 10));
}

void MenuScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
							"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void MenuScreen::destroy() {
	delete background;
	delete button;
	delete btn_exit;
	delete _spriteFont;
	delete _gFont;
}

void MenuScreen::onExit() {}

void MenuScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(), 
					_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	initGUI();
}

void MenuScreen::update() {
	_camera2D.update();
	if (button->click(_game->_inputManager.getMouseCoords())) {
		button->setColor(ColorRGBA(180, 180, 180, 255));
		if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			if (
				!button->getClicked()
				) {
				button->setClicked(true);
				std::cout << "Play!" << std::endl;
				_currentState = ScreenState::CHANGE_NEXT;
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

void MenuScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void MenuScreen::draw() {
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
	char buffer2[256];

	_spriteBatch.begin();
	background->draw(_spriteBatch);
	button->draw(_spriteBatch);
	btn_exit->draw(_spriteBatch);

	sprintf(buffer, "POLLOS ENOJADOS");

	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(130, 340), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 0, 255));
	
	sprintf(buffer2, "u201420396 - Salinas Cesar \nu201422771 - Chancolla Steve \nu201413062 - Lozano Diego");

	_gFont->draw(_spriteBatch, buffer2,
		glm::vec2(280, 50), glm::vec2(0.5), 0.0f,
		ColorRGBA(0, 0, 0, 255));

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void MenuScreen::build() {}

int MenuScreen::getPreviousScreen() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int MenuScreen::getNextScreen() const {
	return SCREEN_INDEX_GAME;
}

MenuScreen::~MenuScreen()
{
}
