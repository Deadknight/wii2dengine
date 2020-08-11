#ifndef GUILABEL_H
#define GUILABEL_H

/*FTGX_JUSTIFY_LEFT
FTGX_JUSTIFY_CENTER
FTGX_JUSTIFY_RIGHT
FTGX_ALIGN_TOP
FTGX_ALIGN_MIDDLE
FTGX_ALIGN_BOTTOM
FTGX_STYLE_UNDERLINE
FTGX_STYLE_STRIKE*/


class GUILabel : public GUIItem
{
public:
	GUILabel(std::string nameP);
	~GUILabel();
	
	void Load(std::string fontName);

	void SetText(std::wstring val) { text = val; }
	void SetText(std::string val);
	void SetBold(bool val) { bold = val; }
	void SetItalic(bool val) { italic = val; }
	void SetUnderscore(bool val) { underscore = val; }
	void SetColor(uint8 r, uint8 g, uint8 b, uint8 a) { color = (GXColor){r, g, b, a}; }
	void SetTextStyle(uint16 style) { textStyle = style; }

	virtual void Draw(int32 duration);
protected:
	std::wstring text;
	bool bold;
	bool italic;
	bool underscore;
	uint16 textStyle;
	GXColor color;
	FreeTypeGX *font;
};

#endif
