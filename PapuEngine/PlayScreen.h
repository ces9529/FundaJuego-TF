#pragma once
#include "IGameScreen.h"
#include "Camera2D.h"
#include "GLS_Program.h"
#include "Window.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "GLTexture.h"
#include "Bird.h"
#include "Pig.h"
#include "Background.h"
#include "Button.h"
#include "Box.h"
#include "Slingshot.h"
#include "Game.h"
#include "EndScreen.h"
#include <random>
#include <ctime>


class PlayScreen: public IGameScreen
{
private:
	std::string init;
	std::string mid;
	std::string finish;
	Background* background = nullptr;
	GLS_Program _program;
	Button* button1 = nullptr;
	Button* btn_exit = nullptr;
	Camera2D _camera2D;
	Window* _window = nullptr;
	SpriteBatch _spriteBatch;
	SpriteBatch _hudBach;
	Camera2D _hudCamera;
	SpriteFont* _spriteFont;
	SpriteFont* _ShotsFont;
	Bird* bird;
	Slingshot* slingshot;
	vector<Pig*> pigs;
	vector <Box*> boxs;
	vector <glm::vec2> posBox;
	int shots;
	int score;
	void drawHUD();

public:
	PlayScreen(Window* window);
	virtual void build() override;
	virtual void destroy() override;
	virtual void onExit() override;
	virtual void onEntry() override;
	virtual void initGUI() override;
	virtual void draw() override;
	virtual void update()override;
	virtual void initSystem()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
	virtual void checkInput() override;
	void checkBoundaries();
	~PlayScreen();
};

