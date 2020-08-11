using System;
using System.Collections.Generic;
using System.Text;

namespace MapEditor
{
    public enum SoundType
    {
        SOUND_TYPE_MP3,
        SOUND_TYPE_OGG,
        SOUND_TYPE_MOD,
        SOUND_TYPE_WAV
    };
    
    class SoundObject : BaseObject
    {
        private String file;
        private String name;
        private SoundType type;
        private bool loop;

        public String File
        {
            get { return file; }
            set { file = value; }
        }

        public String Name
        {
            get { return name; }
            set { name = value; }
        }

        public SoundType Type
        {
            get { return type; }
            set { type = value; }
        }

        public bool Loop
        {
            get { return loop; }
            set { loop = value; }
        }
    }
}
