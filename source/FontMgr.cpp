#include "Stdafx.h"

initialiseSingleton( FontMgr );

FontMgr::FontMgr()
{
	m_lastFontName = "";
	m_lastUsedFont = NULL;

	//Load fonts
	//Maybe later we can load fonts from a file but we will load them manually now
	FreeTypeGX *font = new FreeTypeGX(/*(uint8_t)GX_TF_RGBA8, (uint8_t)GX_POS_XY*/);
	font->loadFont(ageone_ttf, ageone_ttf_size, 12);
	/*freeTypeGX->drawText(10, 25, _TEXT("FreeTypeGX Rocks!"),
                     (GXColor){0xff, 0xee, 0xaa, 0xff},
                     FTGX_JUSTIFY_CENTER | FTGX_ALIGN_BOTTOM | FTGX_STYLE_UNDERLINE);*/

	m_fontMap.insert(std::make_pair("name", font));
	currentCount = 0;
}

FontMgr::~FontMgr()
{
}

FreeTypeGX* FontMgr::GetFontByName(std::string name)
{
	if(m_lastFontName != name)
	{
		std::map<std::string, FreeTypeGX*>::iterator itr = m_fontMap.find(name);
		if(itr != m_fontMap.end())
		{
			m_lastFontName = name;
			m_lastUsedFont = itr->second;
			return m_lastUsedFont;
		}
		return NULL;
	}
	else
		return m_lastUsedFont;
}

void FontMgr::DrawText(std::string text)
{
	std::wstring temp(text.length(),L' ');
	std::copy(text.begin(), text.end(), temp.begin());
	tempArr[currentCount] = temp;
	currentCount++;
	if(currentCount > 3)
		currentCount = 0;
}

void FontMgr::Update()
{
	FreeTypeGX *font = GetFontByName("name");
	for(int i = 0; i < 4; i++)
	{
		font->drawText(2, 14*(i+1), tempArr[i].c_str(), (GXColor){0xff, 0x00, 0x00, 0xff});
	}
}
