#include "ActionAddNotes.h"
#include "Registrar.h"
#include <fstream>
#include <iostream>


ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
}

bool ActionAddNotes::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Add Note: Enter your note: ");
	string noteText = pGUI->GetSrting();
	ofstream Notes;

	Notes.open("Notes.txt", ios::app);
	Notes << noteText << endl;
	Notes.close();

	return true;
}


ActionAddNotes::~ActionAddNotes()
{
}


