#pragma once
#include "catanPlayerModel.h"
#include "observer.h"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>

class player1Viewer : public observer
{
public:
	player1Viewer(catanPlayerModel * player1);
	void update();
	bool getInitOk();
	~player1Viewer();
private:
	catanPlayerModel * player;
	ALLEGRO_FONT * fontForVictoryPoints;
	ALLEGRO_FONT * fontForName;
	ALLEGRO_FONT * fontForResources;
	ALLEGRO_FONT * fontForAmountOfCards;
	ALLEGRO_FONT * fontForLongestRoad;
	bool initOk;
	void viewVictoryPoints();
	void viewNameIs();
	void viewResources();
	void viewLongestRoads();
	void viewAmountOfCards();
};
