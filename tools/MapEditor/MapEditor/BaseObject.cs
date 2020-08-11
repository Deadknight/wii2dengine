using System;
using System.Collections.Generic;
using System.Text;

namespace MapEditor
{
    public class BaseObject
    {
        public BaseObject()
        {
            inverseMass = -1;
        }

        private UInt32 entry;
        private Int32 mass;
        private Int32 inverseMass;

        public UInt32 Entry
        {
            get { return entry; }
            set { entry = value; }
        }

        public Int32 Mass
        {
            get { return mass; }
            set { mass = value; }
        }

        public Int32 InverseMass
        {
            get { return inverseMass; }
            set { inverseMass = value; }
        }
    }
}
