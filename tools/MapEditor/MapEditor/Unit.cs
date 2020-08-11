using System;
using System.Collections.Generic;
using System.Text;

namespace MapEditor
{
    public enum FactionTypes
    {
        NONE                    = 0x0,
        PLAYER					= 0x1,
        PLAYER_NPC				= 0x2,
        CREATURE				= 0x10,
        CREATURE_NPC			= 0x20
    };

    public class Unit : BaseObject
    {
        private String name;
        private FactionTypes faction;

        public String Name
        {
            get { return name; }
            set { name = value; }
        }

        public FactionTypes Faction
        {
            get { return faction; }
            set { faction = value; }
        }
    }
}
