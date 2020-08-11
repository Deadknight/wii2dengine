#ifndef GUIITEM_H
#define GUIITEM_H

class GUIItem
{
public:
	GUIItem(std::string nameP);
	~GUIItem();

	virtual void Collide(int32 x, int32 y) { }

	virtual void SetPosition(int32 xP, int32 yP) { x = xP; y = yP; }
	virtual void SetSize(int32 x, int32 y) { sizeX = x; sizeY = y;}

	virtual void Update(int32 duration) { }
	virtual void Draw(int32 duration);

protected:
	std::string name;
	int32 x;
	int32 y;
	int32 sizeX;
	int32 sizeY;
	ML_Sprite *spr;
};

#endif
