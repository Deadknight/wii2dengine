using System;
using System.Collections.Generic;
using System.Text;

namespace MapEditor
{
    public enum MapEventType
    {
        MAP_EVENT_LEVEL_START,
        MAP_EVENT_LEVEL_END,
        MAP_EVENT_SCRIPT
    };

    public class EventFile
    {
        public MapEventType type;

        public override string ToString()
        {
            return type.ToString();
        }
    }
}
