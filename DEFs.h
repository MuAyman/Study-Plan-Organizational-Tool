#pragma once

//This header file contains some defenitions to be used all over the application
#include <string>
using namespace std;
typedef string Course_Code;
typedef string CourseGradeLetter;
typedef string TrackType;


// Course Status
enum CourseStatus
{
	Done,
	InProgress,
	Pending 
};

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

	DONE,		//Check Done
	FILTER,		//Filter major, year ,semester

	EXIT,		//Exit the applicationS

	STATUS_BAR,	//A click on the status bar
	MENU_BAR,	//A click on an empty place in the menu bar
	DRAW_AREA,	//A click in the drawing area
	ADD_MINOR,	// Add minor option
	Upd_Status,		// Update year / sem status


	CANCEL,		//ESC key is pressed

	NOTES,		//Add Notes 

	LINKS,		//Draw line connection between the pre co requisite

	DRAG,		//Drag and drop action

	GPA,		//Calculate GPA

	DOUBLECONCENT,	//Double concentration

	DOUBLEMAJOR,  //Double Major
	
	ADDMINOR,	//Add Minor courses

	LEVEL,

	STATUS

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


// Course Status
enum CourseStatus
{
	Done,
	InProgress,
	Pending
};