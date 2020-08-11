#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

class SoundObject : public Object
{
public:
	SoundObject(uint64 guid);
	~SoundObject();

	virtual void Init(const char* name, uint32 entry);
	virtual void Draw(int32 x, int32 y);
	virtual void Update(Real duration);

	void SetCanUpdate(bool val) { m_canUpdate = val; }
	void SetLoop(bool val) { m_loop = val; }
	void SetType(uint8 val) { m_type = val; }
	void SetName(std::string val) { m_name = val; }
	void SetFilename(std::string val) { m_filename = val; }

private:
	bool m_triggered;
	bool m_canUpdate;
	bool m_loop;
	uint8 m_type;
	std::string m_name;
	std::string m_filename;

	uint32 _fields[BASIC_END];
};

#endif
