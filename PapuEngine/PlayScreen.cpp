#include "PlayScreen.h"

#include "MyScreens.h"

#include<math.h>
#include <iostream>

#define Pi 3.14159
#define PosIniX 190
#define PosIniY 200
using namespace std;

PlayScreen::PlayScreen(Window* window):_window(window)
{
	_screenIndex = SCREEN_INDEX_GAME;
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteFont = new SpriteFont("Fonts/angrybirds-regular.ttf", 75);
	_ShotsFont = new SpriteFont("Fonts/angrybirds-regular.ttf", 75);
	background = new Background("Textures/background_1.png");
	button1 = new Button("Textures/button_menu.png", 40, 40, glm::vec2(10, 450));
	btn_exit = new Button("Textures/button_quit.png", 40, 40, glm::vec2(710, 10));
	slingshot = new Slingshot(25, 70, glm::vec2(185, 160),"Textures/slingshot2.png");
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	delete background;
	delete button1;
	delete btn_exit;
	delete _spriteFont;
	
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();
	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	_spriteBatch.init();
	
	/*
	randomX = uniform_int_distribution<int>(1, _window->getScreenWidth());
	randomY = uniform_int_distribution<int>(_window->getScreenHeight() / 2, _window->getScreenHeight());
	//RANDOM PARA GENERAR ENEMIGOS EN UN TIEMPO X
	random100 = uniform_int_distribution<int>(1, 100);
	*/
	/*
	player = new Gamer(106, 79,
		glm::vec2(200, 200), "Textures/Player.png", 
		&_game->_inputManager);
	*/

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_real_distribution<float>
		randX(_window->getScreenWidth() / 2, _window->getScreenWidth() - 60);
	std::uniform_real_distribution<float>
		randY(_window->getScreenHeight() / 2, _window->getScreenHeight() - 60);
	
	init = "Textures/birdredStatic.png";
	mid = "Textures/birdredTeeth.png";
	finish = "Textures/birdredScream.png";
	bird = new Bird(30, 30, 
		glm::vec2(PosIniX, PosIniY), init,
		&_game->_inputManager);

	for (int i = 0; i < 5; i++)
	{
		int x = int(randX(randomEngine));
		int y = int(randY(randomEngine));
		pigs.push_back(new Pig(35, 35, glm::vec2(x,y), "Textures/pign.png"));
	}
	posBox.push_back(glm::vec2(400, 105));
	posBox.push_back(glm::vec2(490, 140));
	posBox.push_back(glm::vec2(580, 200));
	posBox.push_back(glm::vec2(630, 105));

	for (int i = 0; i < posBox.size(); i++)
	{
		int y = int(randY(randomEngine));
		boxs.push_back(new Box(50, 50, glm::vec2(posBox[i].x,posBox[i].y), "Textures/box.png"));
	}

	initGUI();
	
}

void PlayScreen::update() {

	_camera2D.update();
	
	if (button1->click(_game->_inputManager.getMouseCoords())) {
		button1->setColor(ColorRGBA(180, 180, 180, 255));
		if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			if (
				!button1->getClicked()
				) {
				button1->setClicked(true);
				std::cout << "MENU!" << std::endl;
				_currentState = ScreenState::CHANGE_PREVIOUS;
			}
		}
	}
	else {
		button1->setColor(ColorRGBA(255, 255, 255, 255));
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

	if (bird->click(_game->_inputManager.getMouseCoords()) && !bird->getFly()) {
		bird->setColor(ColorRGBA(180, 180, 180, 255));
		
		if (_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			if (!bird->getClicked()) {
				bird->setClicked(true);
				cout << "inicioX: " << bird->getPosition().x << std::endl;
				cout << "inicioY: " << bird->getPosition().y << std::endl;
				cout << "Agarro" << std::endl;
				bird->setXo(bird->getPosition().x + (bird->getWidth() / 2));
				bird->setYo(bird->getPosition().y + (bird->getHeight() / 2));
				cout << "x0: " << bird->getXo() << std::endl;
				cout << "y0: " << bird->getYo() << std::endl;
			
				cout << "theta: " << bird->getTheta() << std::endl;
				
			}
		}
		else if(!_game->_inputManager.isKeyDown(SDL_BUTTON_LEFT)){
			if (bird->getClicked()) {
				
				cout << "Solto" << std::endl;
				

				bird->setX(bird->getPosition().x + (bird->getWidth() / 2));
				bird->setY(bird->getPosition().y + (bird->getHeight() / 2));

				cout << "x: " << bird->getX() << std::endl;
				cout << "y: " << bird->getY() << std::endl;

				bird->setTheta((((-atan(fabs(bird->getYo()  - bird->getY()) / fabs(bird->getXo() - bird->getX()))) * 180 )/ Pi) * Pi / 180.0);
				bird->setS(sqrt(pow(fabs(bird->getXo() - bird->getX()), 2) + pow(fabs(bird->getYo() - bird->getY()), 2)));
				
				cout << "theta: " << bird->getTheta() << std::endl;
				cout << "speed: " << bird->getS() << std::endl;
				bird->setClicked(false);
				
				if (bird->getXo() > bird->getX() && bird->getYo() > bird->getY()) {
					bird->setFly(true);
					 shots++;
				}
				else {
					bird->reset();
				}
			}
		}
	}
	else {
		bird->setColor(ColorRGBA(255, 255, 255, 255));
	}

	if (bird->getClicked()) {
		bird->update();
	}

	
	if (bird->getFly()) {
		bird->flying();
		if (bird->getT()< 3)
		{
			bird->changeTexture(mid);
		}
		else {
			bird->changeTexture(finish);
		}
	}
	
	for (size_t i = 0; i < pigs.size(); i++)
	{
		if (pigs[i]->collideWithAgent(bird))
		{
			delete pigs[i];
			pigs[i] = pigs.back();
			pigs.pop_back();
			bird->reset();
			score += 10;
		}
	}
	for (size_t i = 0; i < pigs.size(); i++) 
	{
		if (pigs[i]->getPosition().y + 35 >= 140 && !pigs[i]->getStop()) 
		{
			pigs[i]->update();
		}
	}
	for (size_t i = 0; i < boxs.size(); i++) {
		
		for (int j = 0; j < pigs.size(); j++)
		{
			if (pigs[j]->collideWithAgent(boxs[i],16)) 
			{
				pigs[j]->setStop(true);
			}

		}

	}
	for (size_t i = 0; i < boxs.size(); i++) {
		if (boxs[i]->collideWithAgent(bird)) {
			delete boxs[i];
			boxs[i] = boxs.back();
			boxs.pop_back();
			score += 5;
		}
	}
	
	checkBoundaries();
	checkInput();
	
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::checkBoundaries()
{
	
	//TRASPASO DE PANTALLA 
	glm::vec2 pPos = bird->getPosition();
	if (pPos.x > _window->getScreenWidth())
	{
		bird->reset();
	}
	else if (pPos.x < -105)
	{
		bird->reset();
	}
	else if (pPos.y < -60)//-60
	{
		bird->reset();
	}
	
}

void PlayScreen::draw() {

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();
	background->draw(_spriteBatch);

	
	bird->draw(_spriteBatch);
	for (int i = 0; i < pigs.size(); i++)
	{
		pigs[i]->draw(_spriteBatch);
	}
	for (int i = 0; i < boxs.size(); i++)
	{
		boxs[i]->draw(_spriteBatch);
	}
	
	button1->draw(_spriteBatch);
	btn_exit->draw(_spriteBatch);

	char buffer[256];
	char buffer2[256];

	sprintf(buffer, "score: %d", score);
	_spriteFont->draw(_spriteBatch, buffer,
		glm::vec2(600, 450), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 0, 255));

	sprintf(buffer2, "shots: %d", shots);
	_ShotsFont->draw(_spriteBatch, buffer2,
		glm::vec2(430, 450), glm::vec2(0.5), 0.0f,
		ColorRGBA(255, 255, 0, 255));

	slingshot->draw(_spriteBatch);
	_spriteBatch.end();
	if (pigs.size() <= 0 && !bird->getFly()) {
		_currentState = ScreenState::CHANGE_NEXT;
	}

	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();

	_hudBach.end();
	_hudBach.renderBatch();
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}
