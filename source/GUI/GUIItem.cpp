#include "Stdafx.h"

GUIItem::GUIItem(std::string nameP)
{
	name = nameP;
	x = 0;
	y = 0;
	sizeX = 0;
	sizeY = 0;
}

GUIItem::~GUIItem()
{
}

void GUIItem::Draw(int32 duration)
{
	ML_DrawSpriteXY(spr, x, y);
}
