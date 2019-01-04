#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "bossFSM.h"
#include "inputEventGenerator.h"
#include "timerEventGenerator.h"
#include "quitButtonController.h"
#include "connectionEstablisher.h"
#include "handShakingFSM.h"
#include "netwEvGenerator.h"
#include "gameCoords.h"

#define TIMEOUT_SECS 150
#define IP_STR "25.79.16.128"

void deleteFrontEnd(void * display);
void * initFrontEnd();


int main(int argc,char * argv[])
{
	void * info = initFrontEnd();
	if (info != nullptr)
	{
		string name = "Nicogil";
		inputEventGenerator inputEvGen(static_cast<ALLEGRO_DISPLAY *>(info));	//mouse, teclado y refresh de pantalla
		timerEventGenerator timeout(TIMEOUT_SECS);
		quitButtonController quitButton;
		connectionEstablisher establisher(IP_STR);
		netwEventGenerator netwReceiver;
		mainEventGenerator eventGen;	//generador de eventos de TODO el programa
		eventGen.attach(&inputEvGen);	//registro fuente de eventos
		eventGen.attach(&timeout);
		eventGen.attach(&quitButton);
		eventGen.attach(&netwReceiver);
		eventGen.attach(&establisher);
		bossFSM fsm(&quitButton,&establisher,&eventGen,&netwReceiver,name,&timeout);
		do
		{
			genericEvent * ev;
			ev = eventGen.getNextEvent();
			if (ev != nullptr)
			{
				fsm.cycle(ev);
				delete ev;
			}
		} while (!fsm.getEvent());
		delete fsm.getEvent();
		deleteFrontEnd(info);
	}
	else
	{
		cout << "No se pudo inicializar correctamente el juego" << endl;
	}
	return 0;
}

void * initFrontEnd()
{
	void * ret = nullptr;
	srand(time(NULL));
	if (al_init())
	{
		if (al_init_font_addon())
		{
			if (al_init_ttf_addon())
			{
				if (al_init_image_addon())
				{
					ALLEGRO_DISPLAY * display = al_create_display(MY_DIS_W, MY_DIS_H);
					if (display != NULL)
					{
						ret = display;
					}
				}
			}
		}
	}
	return ret;
}

void deleteFrontEnd(void * display)
{
	if (display != nullptr)
	{
		al_destroy_display(static_cast<ALLEGRO_DISPLAY *>(display));
	}
}