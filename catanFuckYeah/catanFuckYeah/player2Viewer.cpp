#include "player2Viewer.h"
#include <allegro5/allegro_ttf.h>


player2Viewer::player2Viewer(catanPlayerModel * player2)
{
	initOk = false;
	player = player2;
	if ((fontForVictoryPoints = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 55, 0)) != NULL)
	{
		if ((fontForName = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 59, 0)) != NULL)
		{
			if ((fontForAmountOfCards = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 40, 0)) != NULL)
			{
				if ((fontForLongestRoad = al_load_ttf_font("graficoCatan\\font\\scribish.ttf", 30, 0)) != NULL)
				{
					initOk = true;
				}
			}
		}
	}
}

void player2Viewer::update()
{
	if (initOk)
	{
		viewAmountOfCards();
		viewLongestRoad();
		viewNameIs();
		viewVictoryPoints();
	}
	else
	{
		cout << "error player2" << endl;
	}

}

bool player2Viewer::getInitOk()
{
	return initOk;
}

void player2Viewer::viewNameIs()
{
	string name = player->getName();
	if (name.size() == 0)
	{
		al_draw_text(fontForName, al_color_name("black"), 27, 689, 0, "Player2");
	}
	else
	{
		al_draw_text(fontForName, al_color_name("black"), 27, 689, 0, (name.substr(0,6)).c_str());
	}
}

void player2Viewer::viewLongestRoad()
{
	al_draw_text(fontForLongestRoad, al_color_name("black"), 74, 798, 0, to_string(player->getLongestRoad()).c_str());
}

void player2Viewer::viewAmountOfCards()
{
	unsigned char amountOfCards = player->getAmountOfCards();
	al_draw_text(fontForAmountOfCards, al_color_name("black"), 250, 784, 0, to_string(amountOfCards).c_str());
}

void player2Viewer::viewVictoryPoints()
{
	unsigned char victoryPoints = player->getVictoryPoints();
	string points = to_string(victoryPoints);
	al_draw_text(fontForVictoryPoints, al_color_name("black"), 148, 905, 0, points.c_str());
}

player2Viewer::~player2Viewer()
{
	al_destroy_font(fontForVictoryPoints);
	al_destroy_font(fontForName);
	al_destroy_font(fontForAmountOfCards);
	al_destroy_font(fontForLongestRoad);
}

