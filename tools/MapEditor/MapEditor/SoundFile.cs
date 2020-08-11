using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MapEditor
{
    public class SoundFile
    {
        public SoundFile(String fileP)
        {
            String ext = Path.GetExtension(fileP);
            if (ext == ".mp3" || ext == ".wav" || ext == ".mod")
            {
                switch (ext)
                {
                    case ".mp3":
                        type = SoundType.SOUND_TYPE_MP3;
                        break;
                    case ".ogg":
                        type = SoundType.SOUND_TYPE_OGG;
                        break;
                    case ".mod":
                        type = SoundType.SOUND_TYPE_MOD;
                        break;
                    case ".wav":
                        type = SoundType.SOUND_TYPE_WAV;
                        break;
                    default:
                        break;
                };
            }
            name = Path.GetFileName(fileP);
            file = fileP;
        }

        public String file;
        public String name;
        public SoundType type;

        public override string ToString()
        {
            return name + " | " + type;
        }
    }
}
