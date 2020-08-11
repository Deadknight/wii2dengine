using System;
using System.Collections.Generic;
using System.Text;
using AgateLib.Geometry;

namespace MapEditor
{
    public enum PhysicObjectType
    {
        TYPE_POINT,
        TYPE_BOX,
        TYPE_CIRCLE,
        TYPE_PLANE
    };

    class PhysicObject
    {
        public PhysicObject()
        {
            inverseMass = -1;
        }

        public PhysicObjectType type;
        public Rectangle rect;
        public Int32 rot;
        private Int32 mass;
        private Int32 inverseMass;

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
