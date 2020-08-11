#ifndef SOUNDMGR_H
#define SOUNDMGR_H

struct SoundInfo
{
	char *data;
	int32 length;
};

class SoundMgr : public Singleton< SoundMgr >
{
public:
	SoundMgr();
	~SoundMgr();

	void PlaySound(std::string name);
	void PlaySoundFromWiimote(std::string name);
private:
	std::map<std::string, SoundInfo*> m_soundMap;
};

#define sSoundMgr SoundMgr::getSingleton()

#endif
