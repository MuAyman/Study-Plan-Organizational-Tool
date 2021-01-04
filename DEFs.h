#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
using namespace std;
typedef string Course_Code;
typedef string TrackType;


//Track 
enum Track
{
	SCIENCE,
	ENGINEERING,
	NUM_TRACKS
};
// Majors
enum Major
{
	CIE,
	SPC,
	REE,
	NANENG,
	ENV,
	BMS,
	PEU,
	NANSCIE,
	MATSCI,
	NUM_Major
};

//Semesters
enum SEMESTER
{
	FALL,
	SPRING,
	SUMMER,
	SEM_CNT	//number of semesters 
};


//All possible actions
enum ActionType
{
	ADD_CRS,	//Add a course to study plan
	DEL_CRS,	//Delete a course from study plan
	REP_CRS,    //REplace a course

	SAVE,		//Save a study plan to file
	LOAD,		//Load a study plan from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	EXIT,		//Exit the application

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area

	CANCEL,		//ESC key is pressed

	NOTES,		//Add Notes 

	OFFER,		//Import the coffering courses from the user 

	DRAG,
	DROP,

	//TODO: Add more action types

};

//to sotre data related to the last action
struct ActionData
{
	
	ActionType actType;
	int x, y;
	
};

struct MajorType
{
	Major majType;
};


