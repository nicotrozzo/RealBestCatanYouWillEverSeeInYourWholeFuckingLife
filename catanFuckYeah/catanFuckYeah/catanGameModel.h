#pragma once
#include "EDASubject.h"
#include "bossFSMEvents.h"
#include "catanMapModel.h"
#include "catanPlayerModel.h"
#include "gameDefines.h"

class catanGameModel : public EDASubject
{
public:
	catanGameModel();
	bool dicesThrown(unsigned char dice1, unsigned char dice2);	//modifica informacion del juego, cambia de turno
	bool validConstruction(networkingEventTypes type, string coords);	//devuelve true si la construccion solicitada es valida
	bool construction(networkingEventTypes type, string coords);				//devuelve false si la construccion no es valida, PUEDE MODIFICAR GAME OVER
	bool playersTrade(string currentPlayerCards, string otherPlayerCards);		//devuelve false con trueque invalido
	bool validSelectedCards(string currentPlayerCards, string otherPlayerCards);		//checkea que la transaccion solicitada sea valida, en cuyo case devuelve true
	bool bankTrade(string player, unsigned char  bankResource);		//devuelve false si la transaccion es invalida (ver lo de 2x1 y 3x1)
	bool robberMoved(unsigned char hex);	//devuelve false y no cambia nada si el lugar no es valido 
	bool discardCurrentPlayer(string cards);	//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas
	bool discardOtherPlayer(string cards);		//devuelve false si era una cantidad invalida de cartas, o no tenia esas cartas
	
	networkingEventTypes isTrading();	//devuelve 0 si no esta preparando un intercambio, OFFER_TRADE si esta preparando intercambio entre jugadores o BANK_TRADE si esta preparando intercambio con el banco
	void clearTrades();	//borra la informacion sobre intercambios pendientes que tenga el modelo MODIFICA EL MODELO
	
	/*preparePlayerTrade:
	*Recibe:
	-Primer parametro: recurso a incrementar
	-Segundo parametro: jugador cuyo recurso se quiere incrementar (1 o 2)
	*Funcionamiento: si se puede, incrementa el recurso pedido en 1 en los recursos seleccionados por el jugador solicitado para el intercambio
	Siempre incrementa el recurso del jugador 2 para que el usuario no pueda saber cuantos recursos tiene el jugador 2
	*Devuelve: false si se trato de incrementar un recurso DEL JUGADOR ACTUAL que no tenia.
	Si devuelve true, MODIFICA EL MODELO
	*/
	bool preparePlayerTrade(resourceType resource, unsigned char player);	//MODIFICA EL MODELO
	bool playerTradeReady();	//devuelve true si el intercambio con el jugador preparado esta listo
	bool playerTrade();
	
	/*prepareBankTrade:
	*Recibe:
	-Primer parametro: recurso a seleccionar
	-Segundo parametro: indica si se selecciona un recurso del banco o del jugador. True si es del jugador, false si es del banco
	*Funcionamiento: intenta seleccionar el recurso solicitado para el jugador o el banco. Si se selecciona un recurso del jugador y habia uno seleccionado del banco, este ultimo se borra
	Si se selecciona un recurso del jugador y ya habia un recurso seleccionado del jugador, pisa el anterior, lo mismo con recursos del banco.
	Si el jugador no dispone de los recursos suficientes, no hace nada.
	Si el jugador dispone de los recursos, selecciona la cantidad necesaria, segun los costos del jugador para el bank trade
	*Devuelve: true si selecciona el recurso, false si no*/
	bool prepareBankTrade(resourceType resource, bool player);	//MODIFICA EL MODELO	
	bool bankTradeReady();	//devuelve true si el intercambio con el banco preparado esta listo
	bool bankTrade();	//ejecuta el trade preparado, 

	//bool waitingAccept();
	//bool waitingCards();
	catanPlayerModel getCurrentPlayer();
	catanPlayerModel getOtherPlayer();
	unsigned char getDice1() { return dice1; }
	unsigned char getDice2() { return dice2; }
	bool gameOver();	//true si termino el juego, llamar despues de construccion!!!!!!!!(pregunta a cada jugador cuantos puntos tiene)
	~catanGameModel();
protected:
	//bool waitingCards;
	//bool waitingToAccept;
	bool player1Playing;	//true si es el turno del jugador 1, false si es el turno del jugador 2
	catanPlayerModel player1;
	catanPlayerModel player2;
	cards p1SelectedCardsForTrade;
	cards p2SelectedCardsForTrade;
	resource_t playerSelectedResource; //para el bankTrade
	resourceType bankSelectedResource;
	unsigned char dice1;
	unsigned char dice2;
	catanMapModel map;
	bool selectedResource(resourceType res, unsigned char player);
	networkingEventTypes trading;
};


/*SOLO LO TIENE FSM DE HANSHAKING*/
class catanGameModelSetup : public catanGameModel
{
public:
	void setMyName(string name) { player1.setName(name); }
	void setOppName(string name) { player2.setName(name); }
	void setMap(string map_) { map.setMap(map_); };
	string getMap() { return map.getMap(); }
	string getCircularTokens() { return map.getCircularTokens(); };
	void setStartingPlayer(char player);
};



