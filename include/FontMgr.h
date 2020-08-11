#ifndef FONTMGR_H
#define FONTMGR_H

class FontMgr : public Singleton < FontMgr >
{
public:
	FontMgr();
	~FontMgr();

	FreeTypeGX* GetFontByName(std::string name);

	void DrawText(std::string text);

	void Update();
private:
	std::map<std::string, FreeTypeGX*> m_fontMap;
	std::string m_lastFontName;
	FreeTypeGX* m_lastUsedFont;
	std::wstring tempArr[4];
	int32 currentCount;
};

#define sFontMgr FontMgr::getSingleton()

#endif
