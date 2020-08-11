using System;
using System.Collections.Generic;
using System.Text;

namespace GOCreator
{
    class ImagePath
    {
        public String name;
        public String fullPath;
        public Int32 flags;
        public Byte flipX;
        public Byte flipY;

        public override string ToString()
        {
            return name;
        }
    }
}
