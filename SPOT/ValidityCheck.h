#pragma once
#include "Registrar.h"
#include "Actions/Action.h"
#include <iostream>
class ValidityCheck : public Action
{
	Rules RegRules;
	window* win;
public:
	ValidityCheck(Registrar* pReg);
	bool checkUnivCred(int cr);
	bool checkTrackCred(int cr);
	bool checkMajCred(int cr);
	bool checkTotalCred(int cr);
	bool OverUnderLoadPetition();
	bool ConcenReq(string major);
	bool Execute();
	~ValidityCheck();

	

};