#include "Stdafx.h"

GUIProgressBar::GUIProgressBar(std::string nameP) : GUIItem(nameP)
{
	value = 0;
	minValue = 0;
	maxValue = 100;
}

GUIProgressBar::~GUIProgressBar()
{
}

void GUIProgressBar::Load(uint32 barColorP, uint32 borderColorP)
{
	barColor = barColorP;
	borderColor = borderColorP;
}

void GUIProgressBar::Draw(int32 duration)
{
	Real percent = (Real)(value - minValue) / (Real)(maxValue - minValue);
	ML_FillRect(x, y, (sizeX*percent), sizeY, barColor);
	if(borderX == 1 && borderY == 1)
		ML_DrawRect(x+50, y+50, sizeX, sizeY, borderColor);
	else
	{
		ML_FillRect(x, y, sizeX, borderX, borderColor); //Left to right up
		ML_FillRect(x, y + sizeY, sizeX + borderY, borderX, borderColor); //
		ML_FillRect(x, y, borderY, sizeY, borderColor);
		ML_FillRect(x + sizeX, y, borderY, sizeY, borderColor);
	}
}
