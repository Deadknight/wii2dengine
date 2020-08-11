using System;
using System.Collections.Generic;
using System.Text;
using AgateLib.Geometry;

namespace MapEditor
{
    public struct Vector
    {
        public Int32 X;
        public Int32 Y;

        static public Vector FromPoint(Point p)
        {
            return Vector.FromPoint(p.X, p.Y);
        }

        static public Vector FromPoint(int x, int y)
        {
            return new Vector(x, y);
        }

        public Vector(Int32 x, Int32 y)
        {
            this.X = x;
            this.Y = y;
        }

        public Int32 Magnitude
        {
            get { return (Int32)Math.Sqrt(X * X + Y * Y); }
        }

        public void Normalize()
        {
            Int32 magnitude = Magnitude;
            X = X / magnitude;
            Y = Y / magnitude;
        }

        public Vector GetNormalized()
        {
            Int32 magnitude = Magnitude;

            return new Vector(X / magnitude, Y / magnitude);
        }

        public Int32 DotProduct(Vector vector)
        {
            return this.X * vector.X + this.Y * vector.Y;
        }

        public float DistanceTo(Vector vector)
        {
            return (float)Math.Sqrt(Math.Pow(vector.X - this.X, 2) + Math.Pow(vector.Y - this.Y, 2));
        }

        public static implicit operator Point(Vector p)
        {
            return new Point(p.X, p.Y);
        }

        public static implicit operator PointF(Vector p)
        {
            return new PointF(p.X, p.Y);
        }

        public static Vector operator +(Vector a, Vector b)
        {
            return new Vector(a.X + b.X, a.Y + b.Y);
        }

        public static Vector operator -(Vector a)
        {
            return new Vector(-a.X, -a.Y);
        }

        public static Vector operator -(Vector a, Vector b)
        {
            return new Vector(a.X - b.X, a.Y - b.Y);
        }

        public static Vector operator *(Vector a, float b)
        {
            return new Vector(a.X * (Int32)b, a.Y * (Int32)b);
        }

        public static Vector operator *(Vector a, int b)
        {
            return new Vector(a.X * b, a.Y * b);
        }

        public static Vector operator *(Vector a, double b)
        {
            return new Vector((a.X * (Int32)b), (a.Y * (Int32)b));
        }

        /*public override bool Equals(object obj)
        {
            Vector v;
            if (obj.GetType() is Vector)
            {
                v = (Vector)obj;
                return X == v.X && Y == v.Y;
            }
            else
                return false;
        }*/

        public bool Equals(Vector v)
        {
            return X == v.X && Y == v.Y;
        }

        public override int GetHashCode()
        {
            return X.GetHashCode() ^ Y.GetHashCode();
        }

        public static bool operator ==(Vector a, Vector b)
        {
            return a.X == b.X && a.Y == b.Y;
        }

        public static bool operator !=(Vector a, Vector b)
        {
            return a.X != b.X || a.Y != b.Y;
        }

        public override string ToString()
        {
            return X + ", " + Y;
        }

        public string ToString(bool rounded)
        {
            if (rounded)
            {
                return (int)Math.Round((float)X) + ", " + (int)Math.Round((float)Y);
            }
            else
            {
                return ToString();
            }
        }
    }
}
