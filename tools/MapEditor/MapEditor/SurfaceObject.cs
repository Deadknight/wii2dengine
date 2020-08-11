using System;
using System.Collections.Generic;
using System.Text;
using AgateLib;
using System.IO;
using AgateLib.DisplayLib;

namespace MapEditor
{
    class SurfaceObject
    {
        private String FileName;
        private Surface Surf;
        private Int32 X;
        private Int32 Y;
        private Int32 SizeX;
        private Int32 SizeY;

        public SurfaceObject(String FileName)
        {
            this.FileName = FileName;
            Surf = new Surface(FileName);
        }

        public String GetFilename() { return FileName; }

        public String GetFilenameWithoutExtension() { return Path.GetFileNameWithoutExtension(FileName); }

        public Surface GetSurface() { return Surf; }

        public Int32 GetX() { return X; }
        public Int32 GetY() { return Y; }

        public Int32 GetSizeX() { return SizeX; }
        public Int32 GetSizeY() { return SizeY; }

        public void SetPosition(Int32 x, Int32 y)
        {
            X = x;
            Y = y;
        }

        public void SetSize(Int32 sizex, Int32 sizey)
        {
            SizeX = sizex;
            SizeY = sizey;
            Surf.SetScale((double)SizeX/Surf.SurfaceWidth, (double)SizeY/Surf.SurfaceHeight);
        }

        public void Draw(Int32 x, Int32 y)
        {
            Surf.Draw(x, y);
        }

        public void Delete()
        {
            if (Surf != null)
                Surf.Dispose();
        }

        public override string ToString()
        {
            return Path.GetFileName(FileName) + "-Pos:" + X + "," + Y;
        }
    }
}
