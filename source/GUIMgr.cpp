#include "Stdafx.h"

initialiseSingleton( GUIMgr );

GUIMgr::GUIMgr()
{
}

GUIMgr::~GUIMgr()
{
}

void GUIMgr::Update(int32 duration)
{
	std::map<std::string, GUIItem*>::iterator itr = m_guiMap.begin();
	for(; itr != m_guiMap.end(); ++itr)
	{
		itr->second->Update(duration);
	}
}

void GUIMgr::Draw(int32 duration)
{
	std::map<std::string, GUIItem*>::iterator itr = m_guiMap.begin();
	for(; itr != m_guiMap.end(); ++itr)
	{
		itr->second->Draw(duration);
	}
}
