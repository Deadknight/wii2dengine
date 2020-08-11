#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

enum RESOURCE_MEMORY
{
	MEMORY_PERMANENT,
	MEMORY_MAP
};

struct SpriteProp
{
	int32 animated;
	int32 sizeX;
	int32 sizeY;
	int32 centerX;
	int32 centerY;
	int32 physicsObjectType;
	int32 x;
	int32 y;
	int32 physicsWidth;
	int32 physicsHeight;
};

struct SpriteImage
{
	union
	{
		ML_Sprite *spr;
		ML_Background *back;
	};
	ML_Image *img;
	uint8 flag;
	int32 animated;
	int32 sizeX;
	int32 sizeY;
	int32 centerX;
	int32 centerY;
	int32 physicsObjectType;
	int32 x;
	int32 y;
	int32 physicsWidth;
	int32 physicsHeight;
};

struct SpriteInfo
{
	int32 centerX;
	int32 centerY;
	ML_Sprite *spr;
};


class ResourceMgr : public Singleton< ResourceMgr >
{
public:
	ResourceMgr();
	~ResourceMgr();
	
	//Inits resourcemanager from file
	void Init();

	std::string GetReadFS() { return readFS; }
	void SetReadFS(std::string val) { readFS = val; }
	std::string GetResourceDir(std::string val) { return dir; }
	void SetResourceDir(std::string val) { dir = val; }
	std::string GetResourceDefaultDir() { return defaultDir; }
	void SetResourceDefualtDir(std::string val) { defaultDir = val; }
	ML_Sprite *GetSpriteByName(std::string name, SpriteProp *prop, uint8 flag);
	ML_Background *GetBackgroundByName(std::string name, SpriteProp *prop, uint8 flag);
	void DestroyFlag(uint8 flag);
	void DestroyAll();

	typedef std::map<std::string, SpriteImage*> ImageMap;
private:
	std::string dir;
	std::string defaultDir;
	std::string readFS;
	ImageMap images;
};

#define sResourceMgr ResourceMgr::getSingleton()

#endif
