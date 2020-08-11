#include "Stdafx.h"

initialiseSingleton( SoundMgr );

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
}

void SoundMgr::PlaySound(std::string name)
{
	/*FILE *f = fopen("/loop.mod", "rb"); // change to “SD:/loop.mod” if using r16

	if (f == NULL) {
	fclose(f);
	}
	else {
	fseek (f , 0, SEEK_END);
	mod_size = ftell (f);
	rewind(f);*/

}

void SoundMgr::PlaySoundFromWiimote(std::string name)
{
}
