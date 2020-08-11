#ifndef GUIMGR_H
#define GUIMGR_H

class GUIMgr : public Singleton < GUIMgr >
{
public:
	GUIMgr();
	~GUIMgr();

	void Add(std::string name, GUIItem *item) { m_guiMap.insert(std::make_pair(name, item)); }
	void Update(int32 duration);
	void Draw(int32 duration);
private:
	std::map<std::string, GUIItem*> m_guiMap;
};

#define sGUIMgr GUIMgr::getSingleton()

#endif
