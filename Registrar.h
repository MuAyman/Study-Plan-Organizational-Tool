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
	
	Rules RegRules;	//Registration rules
	
	Rules RegRules2;
	Rules RegRulesDoubleMajor;
	bool doubleConcentbool = false;
	bool AddMinorbool = false;
	int doubleConcint = -1;
	bool doubleMajorbool = false;
public:


	string major, major2;
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	vector <ActionType> Memory;
	bool RulesReset(Rules& R);
	void checkType(Course* pC);
	bool catalogRead(ifstream& File, string name, Rules& R);
	bool RulesRead(ifstream& File, string name, Rules& R1);
	Rules getRules();
	bool ExecuteRules();
	bool ExecuteOfferings();
	bool PreCoCourse(Rules& R);
	Rules getRules2() const;
	Rules getRulesDoubleMajor() const;
	bool ExecuteDoubleMajor();
	void setMinorbool(bool);
	bool getMinorbool();
	void setConcentbool(bool);
	bool getConcentbool();

	void setdoubleConcint(int);
	int  getdoubleConcint();

	void setdoubleMajor(bool);
	bool getdoubleMajor();
	void Run();
	
	~Registrar();
};

