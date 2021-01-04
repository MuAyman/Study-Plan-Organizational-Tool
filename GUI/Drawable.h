#pragma once
class GUI;

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x, y;	
};
//constants related to objects to be drawn
enum
{
	CRS_WIDTH = 60,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = 27,	//Height of course rectangle to be drawn on screen
	PLAN_YEAR_WIDTH = CRS_WIDTH * 12,	//width of plan year rectangle to be drawn on screen
	PLAN_YEAR_HEIGHT = 80,	//Height of play year rectangle to be drawn on screen
	PLAN_SEMESTER_HEIGHT = 33,
	INFO_WIDTH = 300,
	INFO_HEIGHT = PLAN_SEMESTER_HEIGHT * 6 + 8,
	SemRectWidth = 40
};

//Base class for all drawable classes
class Drawable
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	bool Selected;	//is this obj selected (to highlight when drawing)
public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	void setSelected(bool );
	bool isSelected() const;
	void virtual DrawMe(GUI*) const = 0;
	virtual ~Drawable();
};

