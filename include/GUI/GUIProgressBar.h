#ifndef GUIPROGRESSBAR_H
#define GUIPROGRESSBAR_H

class GUIProgressBar : public GUIItem
{
public:
	GUIProgressBar(std::string nameP);
	~GUIProgressBar();
	
	void Load(uint32 barColorP, uint32 borderColorP);

	void SetValue(int32 val) { value = val; }
	void SetMinValue(int32 val) { minValue = val; }
	void SetMaxValue(int32 val) { maxValue = val; }
	void SetBorderLength(int32 x, int32 y) { borderX = x; borderY = y; }

	virtual void Draw(int32 duration);
protected:
	int32 value;
	int32 minValue;
	int32 maxValue;
	int32 borderX;
	int32 borderY;
	uint32 barColor;
	uint32 borderColor;
};

#endif
