#include "Stdafx.h"

initialiseSingleton( ResourceMgr );

ResourceMgr::ResourceMgr()
{
	defaultDir = "";
	dir = "";
	readFS = "sd:/";
}

ResourceMgr::~ResourceMgr()
{
}

void ResourceMgr::Init()
{

}

ML_Sprite *ResourceMgr::GetSpriteByName(std::string name, SpriteProp *prop, uint8 flag)
{
	sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "Loading resource %s\r\n", name.c_str());
	ImageMap::iterator itr = images.find(name);
	if(itr != images.end())
	{
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "Resource found in memory\r\n");
		SpriteImage *si = itr->second;
		prop->animated = si->animated;
		prop->sizeX = si->sizeX;
		prop->sizeY = si->sizeY;
		prop->centerX = si->centerX;
		prop->centerY = si->centerY;
		prop->physicsObjectType = si->physicsObjectType;
		prop->x = si->x;
		prop->y = si->y;
		prop->physicsWidth = si->physicsWidth;
		prop->physicsHeight = si->physicsHeight;
		ML_Sprite *spr = new ML_Sprite();
		ML_CloneSprite(itr->second->spr, spr);
		return spr;
	}
	else
	{
		std::string file = readFS + dir + name + ".prop";
		std::string imageFile = readFS + dir + name + ".png";
		
		sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "Loading resource from filename %s\r\n", imageFile.c_str());

		int32 totalWidth = 100;
		int32 width = 0;
		int32 height = 100;
		int32 animatedI = 0;
		int32 centerX = 0;
		int32 centerY = 0;
		int32 physicsObjectType = 0;
		int32 x = 0;
		int32 y = 0;
		int32 physicsWidth = 0;
		int32 physicsHeight = 0;

		FILE *fp = fopen(file.c_str(), "r");
		if(fp)
		{
			fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", &totalWidth, &width, &height, &animatedI, &centerX, &centerY
				, &physicsObjectType, &x, &y, &physicsWidth, &physicsHeight);
			fclose(fp);
		}
		else
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_DEBUG, "No prop file for image %s\r\n", name.c_str());

		prop->animated = animatedI;
		prop->sizeX = width;
		prop->sizeY = height;
		prop->centerX = centerX;
		prop->centerY = centerY;
		prop->physicsObjectType = physicsObjectType;
		prop->x = x;
		prop->y = y;
		prop->physicsWidth = physicsWidth;
		prop->physicsHeight = physicsHeight;
		
		SpriteImage *si = new SpriteImage();
		si->img = new ML_Image();
		si->spr = new ML_Sprite();
		si->animated = animatedI;
		si->flag = flag;
		si->sizeX = width;
		si->sizeY = height;
		si->centerX = centerX;
		si->centerY = centerY;
		si->physicsObjectType = physicsObjectType;
		si->x = x;
		si->y = y;
		si->physicsWidth = physicsWidth;
		si->physicsHeight = physicsHeight;	
		//It is a new sprite so we have to load it
		if(!ML_LoadSpriteFromFile(si->img, si->spr, (char*)imageFile.c_str(), 0, 0))
		{
			//Omg Error happened what the fuck
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot load image %s\r\n", imageFile.c_str());
			delete si->img;
			delete si->spr;
			delete si;
			return NULL;
		}
		
		si->spr->repeat = false;

		images.insert(std::make_pair(name, si));
		return si->spr;
	}
}

ML_Background *ResourceMgr::GetBackgroundByName(std::string name, SpriteProp *prop, uint8 flag)
{
	ImageMap::iterator itr = images.find(name);
	if(itr != images.end())
	{
		//We have loaded sprite so clone it
		SpriteImage *si = new SpriteImage();
		si->img = NULL;
		si->back = new ML_Background();
		si->flag = flag;
		ML_CloneBackground(itr->second->back, si->back);
		images.insert(std::make_pair(name, si));
		return si->back;
	}
	else
	{
		std::string file = readFS + dir + name + ".prop";
		std::string imageFile = readFS + dir + name + ".png";

		int totalWidth = 100;
		int width = 0;
		int height = 100;
		int animatedI = 0;
		int centerX = 0;
		int centerY = 0;

		FILE *fp = fopen(file.c_str(), "r");
		if(fp)
		{
			fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &totalWidth, &width, &height, &animatedI, &centerX, &centerY);
			fclose(fp);
		}
		else
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_INFO, "No prop file for image %s\r\n", name.c_str());

		prop->animated = animatedI;
		prop->sizeX = width;
		prop->sizeY = height;
		prop->centerX = centerX;
		prop->centerY = centerY;

		SpriteImage *si = new SpriteImage();
		si->img = new ML_Image();
		si->back = new ML_Background();
		si->flag = flag;
		//It is a new sprite so we have to load it
		if(!ML_LoadBackgroundFromFile(si->img, si->back, (char*)imageFile.c_str(), totalWidth, height))
		{
			//Omg Error happened what the fuck
			sLog.outString(LOGTYPE_ALL, LOGLEVEL_ERROR, "Cannot load image %s\r\n", name.c_str());
			delete si->img;
			delete si->back;
			delete si;
			return NULL;
		}

		images.insert(std::make_pair(name, si));
		return si->back;
	}
}

void ResourceMgr::DestroyFlag(uint8 flag)
{
	std::set<std::string> imagesToDelete;
	ImageMap::iterator itr = images.begin();
	for(; itr != images.end();)
	{
		SpriteImage *si = itr->second;
		if(si->img && si->flag == flag)
		{
			imagesToDelete.insert(itr->first);
			ML_DeleteImage(si->img);
		}
		++itr;
	}

	//Delete Images that used
	std::set<std::string>::iterator delItr = imagesToDelete.begin();
	for(; delItr != imagesToDelete.end(); ++delItr)
	{
		images.erase((*delItr));
	}
	imagesToDelete.clear();
}

void ResourceMgr::DestroyAll()
{
	ImageMap::iterator itr = images.begin();
	for(; itr != images.end();)
	{
		SpriteImage *si = itr->second;
		if(si->img)
			ML_DeleteImage(si->img);
		++itr;
	}
	images.clear();
}
