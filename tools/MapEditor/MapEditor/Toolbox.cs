using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using MiscUtil.IO;
using MiscUtil.Conversion;

namespace MapEditor
{
    public partial class Main
    {
        private void toolStripButStaticObject_Click(object sender, EventArgs e)
        {
            toolStripButStaticObject.Checked = !toolStripButStaticObject.Checked;
            if (formImageFileView != null && toolStripButStaticObject.Checked)
            {
                formImageFileView.SetExtension(".unit.go");
                formImageFileView.Reload();
            }
            else
            {
                formImageFileView.SetExtension(".png");
                formImageFileView.Reload();
            }
        }

        private void toolStripButDrawBoundary_Click(object sender, EventArgs e)
        {
            if (toolStripButDrawBoundary.Checked)
                formBoundary.Hide();
            else
            {
                if (toolStripButDrawObjectBoundary.Checked)
                    toolStripButDrawObjectBoundary.Checked = false;
                formStaticBoundary.Hide();
                formBoundary.Show();
                formBoundary.Focus();
            }
            toolStripButDrawBoundary.Checked = !toolStripButDrawBoundary.Checked;
        }

        private void toolStripButDrawObjectBoundary_Click(object sender, EventArgs e)
        {
            if (toolStripButDrawObjectBoundary.Checked)
                formStaticBoundary.Hide();
            else
            {
                if (toolStripButDrawBoundary.Checked)
                    toolStripButDrawBoundary.Checked = false;
                formBoundary.Hide();
                formStaticBoundary.Show();
                formStaticBoundary.Focus();
            }
            toolStripButDrawObjectBoundary.Checked = !toolStripButDrawObjectBoundary.Checked;
        }

        public bool GetStaticObjectChecked()
        {
            return toolStripButStaticObject.Checked;
        }

        public bool GetBoundaryDrawChecked()
        {
            return toolStripButDrawBoundary.Checked;
        }

        public bool GetObjectBoundaryDrawChecked()
        {
            return toolStripButDrawObjectBoundary.Checked;
        }

        public bool GetPhysicObjectDrawChecked()
        {
            return toolStripButDrawStandalonePhysicObject.Checked;
        }

        public bool GetDisplayPhyicsChecked()
        {
            return toolStripButDisplayPhysics.Checked;
        }

        private void toolStripButOpen_Click(object sender, EventArgs e)
        {
            if (relativePath == null)
            {
                MessageBox.Show("Relative path error! Please set relative path");
                return;
            }
            DialogResult dr = openFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                listBoxSurface.Items.Clear();
                listBoxSO.Items.Clear();
                listBoxPO.Items.Clear();

                FileStream fs = new FileStream(openFileDialog.FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
                EndianBinaryReader br = new EndianBinaryReader(BigEndianBitConverter.Big, fs, Encoding.ASCII);

                progressBarStatus.Maximum = (Int32)br.ReadUInt32();
                progressBarStatus.Value = 0;

                //Surface object
                UInt32 count = br.ReadUInt32();
                for (UInt32 i = 0; i < count; i++)
                {
                    progressBarStatus.Value++;
                    Int32 strLen = (Int32)br.ReadUInt32();
                    //br.ReadByte();
                    String surfaceFile = Encoding.ASCII.GetString(br.ReadBytes(strLen));
                    surfaceFile = relativePath + "\\" + surfaceFile;
                    Int32 x = br.ReadInt32();
                    Int32 y = br.ReadInt32();
                    Int32 rot = br.ReadInt32();
                    SurfaceObject so = new SurfaceObject(surfaceFile + ".png");
                    so.SetPosition(x, y);
                    so.GetSurface().RotationAngleDegrees = rot;
                    listBoxSurface.Items.Add(so);
                }

                //Static object
                count = br.ReadUInt32();
                for (UInt32 i = 0; i < count; i++)
                {
                    progressBarStatus.Value++;
                    UInt32 entry = br.ReadUInt32();
                    Int32 mass = br.ReadInt32();
                    Int32 inverseMass = br.ReadInt32();
                    ObjectType type = (ObjectType)br.ReadInt32();
                    Int32 strLen = br.ReadInt32();
                    //br.ReadByte();
                    String staticObjectFile = Encoding.ASCII.GetString(br.ReadBytes(strLen));
                    staticObjectFile = relativePath + "\\" + staticObjectFile;
                    StaticObject so = null;
                    switch (type)
                    {
                        case ObjectType.TYPE_PLAYER:
                            {
                                so = new StaticObject(staticObjectFile + ".unit");
                                so.obj = new Player();
                            } break;
                        case ObjectType.TYPE_UNIT:
                            {
                                so = new StaticObject(staticObjectFile + ".unit");
                                Creature cr = new Creature();
                                Int32 nameLen = (Int32)br.ReadUInt32();
                                if (nameLen > 0)
                                    cr.Name = Encoding.ASCII.GetString(br.ReadBytes(nameLen));
                                else
                                    cr.Name = "";
                                cr.Faction = (FactionTypes)br.ReadUInt32();
                                so.obj = cr;
                            } break;
                        case ObjectType.TYPE_GAMEOBJECT:
                            {
                                so = new StaticObject(staticObjectFile + ".go");
                                Gameobject go = new Gameobject();
                                Int32 nameLen = (Int32)br.ReadUInt32();
                                if (nameLen > 0)
                                    go.Name = Encoding.ASCII.GetString(br.ReadBytes(nameLen));
                                else
                                    go.Name = "";

                                so.obj = go;
                            } break;
                        case ObjectType.TYPE_EVENT:
                            {
                                so = new StaticObject("event");
                                EventObject eo = new EventObject();
                                eo.Type = (MapEventType)br.ReadUInt32();
                                so.obj = eo;
                            } break;
                        case ObjectType.TYPE_SCRIPT:
                            {
                                so = new StaticObject("script");
                                EventObject eo = new EventObject();
                                eo.Type = (MapEventType)br.ReadUInt32();
                                so.obj = eo;
                            } break;
                        case ObjectType.TYPE_MAP:
                            {
                                so = new StaticObject(staticObjectFile + ".png");
                                MapObject mo = new MapObject();
                                mo.Repeat = Convert.ToBoolean(br.ReadByte());
                                mo.Breakable = Convert.ToBoolean(br.ReadByte());
                                so.obj = mo;
                            } break;
                        case ObjectType.TYPE_SOUND:
                            {
                                so = new StaticObject(staticObjectFile + ".png");
                                SoundObject sound = new SoundObject();
                                Int32 nameLen = (Int32)br.ReadUInt32();
                                //br.ReadByte();
                                sound.Name = Encoding.ASCII.GetString(br.ReadBytes(nameLen));
                                Int32 fileLen = (Int32)br.ReadUInt32();
                                //br.ReadByte();
                                sound.File = Encoding.ASCII.GetString(br.ReadBytes(fileLen));
                                sound.Type = (SoundType)br.ReadUInt32();
                                sound.Loop = Convert.ToBoolean(br.ReadByte());
                                so.obj = sound;
                            } break;
                    };
                    if (so == null)
                        continue;

                    so.type = type;
                    so.obj.Entry = entry;
                    so.obj.Mass = mass;
                    so.obj.InverseMass = inverseMass;

                    Int32 x = br.ReadInt32();
                    //br.ReadByte();
                    Int32 y = br.ReadInt32();
                    //br.ReadByte();
                    Int32 Width = (Int32)br.ReadUInt32();
                    Int32 Height = (Int32)br.ReadUInt32();
                    Int32 DisplayWidth = (Int32)br.ReadUInt32();
                    Int32 DisplayHeight = (Int32)br.ReadUInt32();

                    if (so.type == ObjectType.TYPE_EVENT)
                        so.CreateSpriteFromResource("Event", Width, Height);
                    else if (so.type == ObjectType.TYPE_SCRIPT)
                        so.CreateSpriteFromResource("Script", Width, Height);
                    else if (so.type == ObjectType.TYPE_SOUND)
                        so.CreateSpriteFromResource("Sound", Width, Height);
                    else
                        so.Load(Width, Height);

                    Int32 rot = (Int32)br.ReadUInt32();

                    so.SetPosition(new Vector(x, y));
                    so.GetSprite().DisplaySize = new AgateLib.Geometry.Size(DisplayWidth, DisplayHeight);
                    so.GetSprite().RotationAngleDegrees = rot;
                    listBoxSO.Items.Add(so);
                }

                //Physics
                count = br.ReadUInt32();
                for (UInt32 i = 0; i < count; i++)
                {
                    progressBarStatus.Value++;
                    PhysicObject po = new PhysicObject();
                    po.type = (PhysicObjectType)br.ReadUInt32();
                    po.Mass = br.ReadInt32();
                    po.InverseMass = br.ReadInt32();
                    Int32 x = br.ReadInt32();
                    Int32 y = br.ReadInt32();
                    Int32 width = (Int32)br.ReadUInt32();
                    Int32 height = (Int32)br.ReadUInt32();
                    Int32 rot = (Int32)br.ReadUInt32();

                    po.rect = new AgateLib.Geometry.Rectangle(x, y, width, height);
                    po.rot = rot;
                    listBoxPO.Items.Add(po);
                }

                progressBarStatus.Maximum = 100;
                progressBarStatus.Value = 100;

                br.Close();
                fs.Close();
            }
        }

        private void toolStripButSave_Click(object sender, EventArgs e)
        {
            DialogResult dr = saveFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                try
                {
                    FileStream fs = new FileStream(saveFileDialog.FileName, FileMode.Create, FileAccess.Write, FileShare.Write);
                    EndianBinaryWriter bw = new EndianBinaryWriter(BigEndianBitConverter.Big, fs, Encoding.ASCII);

                    progressBarStatus.Maximum = listBoxSO.Items.Count + listBoxSurface.Items.Count + listBoxPO.Items.Count;
                    progressBarStatus.Value = 0;

                    bw.Write((UInt32)progressBarStatus.Maximum);
                    bw.Write((UInt32)listBoxSurface.Items.Count);
                    foreach (SurfaceObject so in listBoxSurface.Items)
                    {
                        progressBarStatus.Value++;

                        String filename = so.GetFilename();
                        filename = filename.Substring(relativePath.Length + 1);
                        String[] arr = filename.Split('.');
                        filename = arr[0];

                        bw.Write((UInt32)filename.Length);
                        bw.Write(filename.ToCharArray());
                        bw.Write(so.GetX());
                        bw.Write(so.GetY());
                        bw.Write((Int32)so.GetSurface().RotationAngleDegrees);
                    }

                    bw.Write((UInt32)listBoxSO.Items.Count);
                    foreach (StaticObject so in listBoxSO.Items)
                    {
                        progressBarStatus.Value++;
                        if (so.obj == null)
                            throw new Exception("No type set on object " + so.GetFilename());
                        bw.Write(so.obj.Entry);
                        bw.Write(so.obj.Mass);
                        bw.Write(so.obj.InverseMass);
                        bw.Write((Int32)so.type);

                        String filename = so.GetFilename();
                        if (relativePath.Length < filename.Length)
                        {
                            filename = filename.Substring(relativePath.Length + 1);
                            String[] arr = filename.Split('.');
                            filename = arr[0];

                            bw.Write((UInt32)filename.Length);
                            bw.Write(filename.ToCharArray());
                        }
                        else
                        {
                            bw.Write((UInt32)so.GetFilename().Length);
                            bw.Write(so.GetFilename().ToCharArray());
                        }
 
                        switch (so.type)
                        {
                            case ObjectType.TYPE_PLAYER:
                                {
                                    Player pl = (Player)so.obj;
                                } break;
                            case ObjectType.TYPE_UNIT:
                                {
                                    Creature cr = (Creature)so.obj;
                                    bw.Write((UInt32)cr.Name.Length);
                                    if(cr.Name.Length > 0)
                                        bw.Write(cr.Name.ToCharArray());
                                    bw.Write((UInt32)cr.Faction);
                                } break;
                            case ObjectType.TYPE_GAMEOBJECT:
                                {
                                    Gameobject go = (Gameobject)so.obj;
                                    bw.Write((UInt32)go.Name.Length);
                                    if (go.Name.Length > 0)
                                        bw.Write(go.Name.ToCharArray());
                                } break;
                            case ObjectType.TYPE_EVENT:
                            case ObjectType.TYPE_SCRIPT:
                                {
                                    EventObject eo = (EventObject)so.obj;
                                    bw.Write((UInt32)eo.Type);
                                } break;
                            case ObjectType.TYPE_MAP:
                                {
                                    MapObject mo = (MapObject)so.obj;
                                    bw.Write(Convert.ToByte(mo.Repeat));
                                    bw.Write(Convert.ToByte(mo.Breakable));
                                } break;
                            case ObjectType.TYPE_SOUND:
                                {
                                    SoundObject sound = (SoundObject)so.obj;
                                    bw.Write((UInt32)sound.Name.Length);
                                    if(sound.Name.Length > 0)
                                        bw.Write(sound.Name.ToCharArray());
                                    bw.Write((UInt32)sound.File.Length);
                                    if(sound.File.Length > 0)
                                        bw.Write(sound.File.ToCharArray());
                                    bw.Write((UInt32)sound.Type);
                                    bw.Write(Convert.ToByte(sound.Loop));
                                } break;
                        };
                        bw.Write(so.GetPosition().X);
                        bw.Write(so.GetPosition().Y);
                        bw.Write((UInt32)so.GetSprite().SpriteWidth);
                        bw.Write((UInt32)so.GetSprite().SpriteHeight);
                        bw.Write((UInt32)so.GetSprite().DisplayWidth);
                        bw.Write((UInt32)so.GetSprite().DisplayHeight);
                        bw.Write((UInt32)so.GetSprite().RotationAngleDegrees);
                    }

                    bw.Write(listBoxPO.Items.Count);
                    foreach (PhysicObject po in listBoxPO.Items)
                    {
                        progressBarStatus.Value++;
                        bw.Write((UInt32)po.type);
                        bw.Write(po.Mass);
                        bw.Write(po.InverseMass);
                        bw.Write(po.rect.X);
                        bw.Write(po.rect.Y);
                        bw.Write((UInt32)po.rect.Width);
                        bw.Write((UInt32)po.rect.Height);
                        bw.Write((UInt32)po.rot);
                    }

                    progressBarStatus.Maximum = 100;
                    progressBarStatus.Value = 100;

                    bw.Close();
                    fs.Close();
                }
                catch(Exception ex)
                {
                    if (ex.Message.StartsWith("No ty"))
                        MessageBox.Show(ex.Message);
                    else
                        MessageBox.Show("Cannot save relative path is not set");
                }
            }
        }

        private void toolStripButMoveSurface_Click(object sender, EventArgs e)
        {
            if (!toolStripButMoveSurface.Checked)
                toolStripButDisplayPhysics.Checked = false;

            toolStripButMoveSurface.Checked = !toolStripButMoveSurface.Checked;
        }

        private void toolStripButMoveStatic_Click(object sender, EventArgs e)
        {
            if (!toolStripButMoveSurface.Checked)
                toolStripButMoveSurface.Checked = false;

            toolStripButMoveStatic.Checked = !toolStripButMoveStatic.Checked;
        }

        private void toolStripButDrawStandalonePhysicObject_Click(object sender, EventArgs e)
        {
            if (!toolStripButStaticObject.Checked)
                toolStripButStaticObject.Checked = false;

            toolStripButDrawStandalonePhysicObject.Checked = !toolStripButDrawStandalonePhysicObject.Checked;

            if (toolStripButDrawStandalonePhysicObject.Checked)
            {
                cBoxType.Items.Clear();
                cBoxType.Items.AddRange(Enum.GetNames(typeof(PhysicObjectType)));
                cBoxType.Enabled = true;
            }
            else
            {
                cBoxType.Items.Clear();
                cBoxType.Enabled = false;
            }
        }

        private void toolStripButDisplayPhysics_Click(object sender, EventArgs e)
        {
            toolStripButDisplayPhysics.Checked = !toolStripButDisplayPhysics.Checked;
        }
    }
}