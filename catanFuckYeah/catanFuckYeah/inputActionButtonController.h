#pragma once
#include "EDAInputController.h"
#include "catanGameModel.h"

/*Controller de botones de PASS, OFFER_TRADE Y BANK_TRADE*/
class inputActionButtonController : public EDAInputController
{
public:
	inputActionButtonController(catanGameModel * game);
	virtual void parseMouseEvent(mouseEvent * ev);
	virtual void parseKeyboardEvent(keyboardEvent * ev);
	inputControllerTypes getType() { return CTRL_ACTION_BUTTON; }
	~inputActionButtonController();

private:
	catanGameModel * gameModel;
};

