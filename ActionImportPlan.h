
#pragma once
#include "Registrar.h"
#include "Actions/Action.h"
#include <iostream>
using namespace std;

class ActionImportPlan : public  Action
{

public:
	ActionImportPlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportPlan();
	bool FileRead(ifstream& File, string name);
	vector<string> Years;
	vector<string> Semester;
	vector<string> courses;
};
/*ActionImportPlan();
~ActionImportPlan();
*/





