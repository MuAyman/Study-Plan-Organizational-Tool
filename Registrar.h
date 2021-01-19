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
	StudyPlan *pSPlan;
	ActionData actData;

public:
	//Major getMajortype();
	Rules RegRules;	//Registration rules
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlan() const;
	vector <ActionType> Memory;
	bool RulesReset(Rules& R);
	void checkType(Course* pC); //new
	bool catalogRead(ifstream& File, string name, Rules& R);
	bool RulesRead(ifstream& File, string name, Rules& R1);
	//bool Execute();
	bool ExecuteRules();
	bool ExecuteOfferings();

	void Run();

	~Registrar();
};

