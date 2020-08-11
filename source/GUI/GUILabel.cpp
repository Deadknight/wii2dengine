#include "Stdafx.h"

GUILabel::GUILabel(std::string nameP) : GUIItem(nameP)
{
	bold = false;
	italic = false;
	underscore = false;
	font = NULL;
	textStyle = FTGX_JUSTIFY_CENTER;
	color = (GXColor){ 0x00, 0x00, 0x00, 0x00 };
}

GUILabel::~GUILabel()
{
}

void GUILabel::Load(std::string fontName)
{
	font = sFontMgr.GetFontByName(fontName);
	if(!font)
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot load font %s\n", fontName.c_str());
}

void GUILabel::SetText(std::string val)
{
	std::wstring temp(text.length(),L' ');
	std::copy(text.begin(), text.end(), temp.begin());
	text = temp;
}

void GUILabel::Draw(int32 duration)
{
	if(font)
		font->drawText(x, y, text.c_str(), color, textStyle);
}
