using System;
using System.Collections.Generic;
using System.Text;

namespace MapEditor
{
    public class MapObject : BaseObject
    {
        public MapObject()
        {
            repeat = false;
            breakable = false;
        }

        private bool repeat;
        private bool breakable;

        public bool Repeat
        {
            get { return repeat; }
            set { repeat = value; }
        }

        public bool Breakable
        {
            get { return breakable; }
            set { breakable = value; }
        }
    }
}
