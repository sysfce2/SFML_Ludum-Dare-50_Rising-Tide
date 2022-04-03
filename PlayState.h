#pragma once

#include "State.h"
#include "Entity.h"
#include "Grid.h"
#include "Water.h"
#include "BitmapText.h"
#include <SFML/Audio.hpp>

const int GRID_LEFT = 70;

class PlayState : public State {
public:
	virtual void init() override;
	virtual void gotEvent(sf::Event event) override;
	virtual void update(sf::Time elapsed) override;
	virtual void render(sf::RenderWindow &window) override;

	void initEntity(Entity &entity);

	enum {
		menu,
		playing
	} phase = menu;

private:
	void adjustMusicVolume(sf::Music &music, float desiredVolume, float factor);

	void loadLevel(int level);

	float cameraY = -25;

	int level = 0;
	int jellies = 0;
	int flags = 0;

	std::string levelName = "";

	Grid grid;
	Water water;

	sf::Sprite leftPane;
	sf::Sprite rightPane;

	sf::Sprite sun;
	sf::Sprite clouds;
	sf::Sprite dunes;
	sf::Sprite camp;

	sf::Sound soundDig;
	sf::Sound soundClear1;
	sf::Sound soundClear2;
	sf::Sound soundClear3;

	sf::Music musicBase;
	sf::Music musicActive;
	sf::Music musicBeat;
	sf::Music musicWarning;
};
