#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
#include <fstream>
#include <vector>

//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;

	ActionData actData;

public:

	//Major getMajortype();

	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	vector <ActionType> Memory;
	bool RulesReset(Rules& R);
	Rules getRules();
	bool catalogRead(ifstream& File, string name, Rules& R);
	bool RulesRead(ifstream& File, string name, Rules& R1);
	bool ExecuteOfferings();
	bool ExecuteRules();
	Rules R = this->getRules();

	void Run();

	~Registrar();
};

