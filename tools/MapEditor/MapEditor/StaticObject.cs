using System;
using System.Collections.Generic;
using System.Text;
using AgateLib;
using System.IO;
using MiscUtil.IO;
using MiscUtil.Conversion;
using AgateLib.Sprites;
using System.Resources;
using System.Drawing;
using System.Drawing.Imaging;

namespace MapEditor
{
    public enum ObjectType
    {
	    TYPE_PLAYER,
	    TYPE_UNIT,
	    TYPE_GAMEOBJECT,
        TYPE_EVENT,
        TYPE_SCRIPT,
        TYPE_MAP,
        TYPE_SOUND,
        TYPE_NONE, //This is for debug not available on real game engine
    }

    public class StaticObject
    {
        private Sprite spr;
        private Polygon bound;
        private Vector location;
        private String FileName;
        private String DirPath;
        private Int32 centerX;
        private Int32 centerY;

        public StaticObject(String FileName)
        {
            this.FileName = FileName;
            DirPath = "";
            spr = null;
            //location = null;
            bound = null;
            type = ObjectType.TYPE_NONE;
        }


        internal void Load(Int32 sizeX, Int32 sizeY)
        {
            String ext = Path.GetExtension(FileName);
            switch (ext)
            {
                case ".unit":
                    LoadUnitFile();
                    break;
                case ".go":
                    LoadGoFile();
                    break;
                default:
                    CreateSprite(sizeX, sizeY);
                    break;
            }
        }

        public void LoadUnitFile()
        {
            FileStream fs = new FileStream(FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
            EndianBinaryReader br = new EndianBinaryReader(BigEndianBitConverter.Big, fs, Encoding.ASCII);
            UInt32 uniqueNameLength = br.ReadUInt32();
            String uniqueName = Encoding.ASCII.GetString(br.ReadBytes((Int32)uniqueNameLength));
            UInt32 virtualDirLength = br.ReadUInt32();
            String virDir = "";
            if (virtualDirLength > 0)
                virDir = Encoding.ASCII.GetString(br.ReadBytes((Int32)virtualDirLength));
            UInt32 photoLength = br.ReadUInt32();
            br.ReadBytes((Int32)photoLength);
            br.ReadUInt32();
            Int32 fileArrayLength = (Int32)br.ReadUInt32();
            for (Int32 i = 0; i < fileArrayLength; i++)
            {
                Int32 flags = (Int32)br.ReadUInt32();
                br.ReadByte();
                br.ReadByte();
                Int32 fileNameShortLength = (Int32)br.ReadUInt32();
                String shortPath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameShortLength));
                Int32 fileNameFullLength = (Int32)br.ReadUInt32();
                String fullpath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameFullLength));
                if ((flags & 0x20100) > 0)
                {
                    String path = Path.GetDirectoryName(FileName);

                    String propFile = path + "\\" + virDir + shortPath + ".prop";
                    FileStream fsProp = new FileStream(propFile, FileMode.Open, FileAccess.Read, FileShare.Read);
                    StreamReader sr = new StreamReader(fsProp);
                    String line = sr.ReadLine();
                    String[] arr = line.Split(',');                    

                    spr = new Sprite(path + "\\" + virDir + shortPath + Path.GetExtension(fullpath), Convert.ToInt32(arr[1]), Convert.ToInt32(arr[2]));

                    centerX = Convert.ToInt32(arr[4]);
                    centerY = Convert.ToInt32(arr[5]);

                    sr.Close();
                    fsProp.Close();
                    break;
                }
            }

            br.Close();
            fs.Close();
        }

        public void LoadGoFile()
        {
            FileStream fs = new FileStream(FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
            EndianBinaryReader br = new EndianBinaryReader(BigEndianBitConverter.Big, fs, Encoding.ASCII);
            UInt32 uniqueNameLength = br.ReadUInt32();
            String uniqueName = Encoding.ASCII.GetString(br.ReadBytes((Int32)uniqueNameLength));
            UInt32 virtualDirLength = br.ReadUInt32();
            String virDir = "";
            if (virtualDirLength > 0)
                virDir = Encoding.ASCII.GetString(br.ReadBytes((Int32)virtualDirLength));
            Int32 fileArrayLength = (Int32)br.ReadUInt32();

            Int32 flags = (Int32)br.ReadUInt32();
            br.ReadByte();
            br.ReadByte();
            Int32 fileNameShortLength = (Int32)br.ReadUInt32();
            String shortPath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameShortLength));
            Int32 fileNameFullLength = (Int32)br.ReadUInt32();
            String fullpath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameFullLength));

            String path = Path.GetDirectoryName(FileName);

            String propFile = path + "\\" + virDir + shortPath + ".prop";
            FileStream fsProp = new FileStream(propFile, FileMode.Open, FileAccess.Read, FileShare.Read);
            StreamReader sr = new StreamReader(fsProp);
            String line = sr.ReadLine();
            String[] arr = line.Split(',');

            spr = new Sprite(path + "\\" + virDir + shortPath + Path.GetExtension(fullpath), Convert.ToInt32(arr[1]), Convert.ToInt32(arr[2]));

            centerX = Convert.ToInt32(arr[4]);
            centerY = Convert.ToInt32(arr[5]);

            sr.Close();
            fsProp.Close();

            br.Close();
            fs.Close();
        }

        public void CreateSprite(Int32 sizeX, Int32 sizeY)
        {
            if (spr != null)
                spr.Dispose();
            spr = new Sprite(FileName, sizeX, sizeY);
        }

        public void CreateSpriteFromResource(String resourceName, Int32 sizeX, Int32 sizeY)
        {
            if (spr != null)
                spr.Dispose();
            ResourceManager rm = new ResourceManager("MapEditor.Properties.Resources", GetType().Assembly);

            Bitmap bmp = (Bitmap)rm.GetObject(resourceName);

	        MemoryStream ms = new MemoryStream();
	        // Save to memory using the Jpeg format
	        bmp.Save (ms, ImageFormat.Png);
        	
            spr = new Sprite(ms, sizeX, sizeY);

            bmp.Dispose();
            ms.Close();
        }

        //
        public void CreateBound(Int32 x, Int32 y, Int32 sizeX, Int32 sizeY)
        {
            if (bound == null)
            {
                bound = new Polygon();
                Vector v = new Vector(x, y);
                bound.Points.Add(v);
                v.X = v.X + sizeX;
                bound.Points.Add(v);
                v.Y = v.Y + sizeY;
                bound.Points.Add(v);
                v.X = v.X - sizeX;
                bound.Points.Add(v);
                bound.BuildEdges();
            }
        }

        public Vector GetPosition() { return location; }

        public Sprite GetSprite() { return spr; }

        public String GetFilename() { return FileName; }

        public String GetFilenameWithoutExtension() { return Path.GetFileNameWithoutExtension(FileName); }

        public String GetDirPath() { return DirPath; }

        public Int32 GetFrameIndex()
        {
            if (spr.IsAnimating)
                return -1;
            else
                return spr.CurrentFrameIndex;
        }

        public void SetPosition(Vector v) { location = v; }

        public void SetFrameIndex(Int32 FrameId)
        {
            if (FrameId == -1)
                spr.IsAnimating = true;
            else
                spr.CurrentFrameIndex = FrameId;
            spr.Update();
        }

        public void SetDirectory(String dir) { DirPath = dir; }

        //Boundary
        public void CreateBoundary()
        {
            if(!HasBoundary())
                bound = new Polygon();
        }

        public void AddBoundary(Int32 x, Int32 y)
        {
            bound.Points.Add(new Vector(x, y));
            bound.BuildEdges();
        }

        public void AddBoundary(Vector v)
        {
            bound.Points.Add(v);
            bound.BuildEdges();
        }

        public bool HasBoundary() { return (bound != null); }

        public Polygon GetBoundary() { return bound; }

        public void ClearBoundary() { bound.Points.Clear(); }

        //Engine
        public void Draw(Int32 x, Int32 y)
        {
            spr.Draw(x, y);
        }

        public void Delete()
        {
            if(spr != null)
                spr.Dispose();
        }

        //Properties of save
        public ObjectType type;
        public BaseObject obj;

        public override string ToString()
        {
            return type.ToString() + "-" + Path.GetFileName(FileName);
        }
    }
}
