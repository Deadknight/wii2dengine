using System;
using System.Collections.Generic;
using System.Text;

namespace MapEditor
{
    class EventObject : BaseObject
    {
        private MapEventType type;

        public MapEventType Type
        {
            get { return type; }
            set { type = value; }
        }
    }
}
