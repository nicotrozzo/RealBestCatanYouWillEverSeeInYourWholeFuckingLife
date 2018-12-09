#include "startMenu.h"
using namespace std;

startMenu::startMenu()
{
	initOk = false;
	if ((menuBitmap = al_load_bitmap("graficoCatan\\menues\\mainmenu.png")) != NULL || (playBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonplay1.png")) != NULL || (exitBitmap = al_load_bitmap("graficoCatan\\buttons\\buttonexit1.png")) != NULL)
	{
		initOk = true;
		al_draw_bitmap(menuBitmap, 0, 0, 0);
		al_draw_bitmap(playBitmap, 410, 500, 0);
		al_draw_bitmap(exitBitmap, 820, 500, 0);
	}
}


void startMenu::refresh()
{
		al_flip_display();
}

bool startMenu::getInitOk()
{
	return initOk;
}

startMenu::~startMenu()
{
	al_destroy_bitmap(menuBitmap);
	al_destroy_bitmap(playBitmap);
	al_destroy_bitmap(exitBitmap);
}
