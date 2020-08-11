//#define THUMBNAIL

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using AgateLib;
using System.IO;
using AgateLib.DisplayLib;
using AgateLib.Sprites;
using AgateLib.InputLib;

namespace MapEditor
{
    public partial class Main : Form
    {
        //Render
        DisplayWindow window;
        Int32 currentX;
        Int32 currentY;
        Int32 sizeX;
        Int32 sizeY;
        SurfaceObject lastSurface;
        AgateLib.Geometry.Color lastSurfaceColor;
        StaticObject lastStaticObject;
        AgateLib.Geometry.Color lastStaticObjectColor;
        public String relativePath;

        //Forms
        BoundaryForm formBoundary;
        StaticObjectBoundaryForm formStaticBoundary;
        TextureBox formTextureBox;
        ImageFileView formImageFileView;
        SoundFileView formSoundFileView;
        EventView formEventView;

        //List
        public List<Vector> lstBound;

        //Drag and drop
        protected int lastX = 0;
        protected int lastY = 0;
        protected string lastFilename = String.Empty;
        protected DragDropEffects effect;
        protected bool validData;
        protected bool validSoundData;
        protected bool validEventData;
        protected Image image;
        protected Image nextImage;
        protected Thread getImageThread;
        protected ListViewObject lvo;
        protected SoundFile sf;
        protected EventFile ef;

        public Main()
        {
            InitializeComponent();

            lastSurface = null;
            lastStaticObject = null;

            currentX = pictBoxRender.Width / 2;
            currentY = pictBoxRender.Height / 2;
            txtVX.Text = currentX.ToString();
            txtVY.Text = currentY.ToString();
            sizeX = currentX;
            sizeY = currentY;

            lstBound = new List<Vector>();

            formBoundary = new BoundaryForm(this);
            formStaticBoundary = new StaticObjectBoundaryForm(this);
            formTextureBox = new TextureBox(this);
            //formTextureBox.Show();
            formImageFileView = new ImageFileView(formTextureBox);
            formImageFileView.Show();
            formSoundFileView = new SoundFileView();
            formSoundFileView.Show();
            formEventView = new EventView();
            formEventView.Show();

#if !THUMBNAIL
            thumbnail.Visible = false;
#endif
        }

        private void Main_Load(object sender, EventArgs e)
        {
            //Sprite.UseSpriteCache = false;

            // This will create a display "window" that renders to the graphics
            // control on this form
            // It doesn't matter if this goes out of scope, because a reference
            // will be maintained by the Display object.
            CreateWindowParams cwp = new CreateWindowParams();
            cwp.RenderToControl = true;
            cwp.RenderTarget = pictBoxRender;
            cwp.IsFullScreen = false;
            window = new DisplayWindow(cwp);

            //Init Input
            Keyboard.KeyDown += new InputEventHandler(Keyboard_KeyDown);
            Keyboard.KeyUp += new InputEventHandler(Keyboard_KeyUp);

            Mouse.MouseMove += new InputEventHandler(Mouse_MouseMove);
            Mouse.MouseDown += new InputEventHandler(Mouse_MouseDown);
            Mouse.MouseUp += new InputEventHandler(Mouse_MouseUp);
            Mouse.MouseDoubleClick += new InputEventHandler(Mouse_MouseDoubleClick);
        }

        bool CheckInView(Int32 x, Int32 y, out Int32 xO, out Int32 yO)
        {
            Int32 minX = currentX - sizeX;
            Int32 maxX = currentX + sizeX;
            Int32 minY = currentY - sizeY;
            Int32 maxY = currentY + sizeY;
            if ((x > minX || x < maxX) && (y > minY || y < maxY))
            {
                xO = x - minX;
                yO = y - minY;
                return true;
            }
            xO = 0;
            yO = 0;
            return false;
        }

        Vector ConvertToVirtualCoordinates(Int32 x, Int32 y)
        {
            Int32 minX = currentX - sizeX;
            Int32 minY = currentY - sizeY;

            return new Vector(x + minX, y + minY);
        }

        internal void UpdateDisplay()
        {
            if (this.Visible == false || this.WindowState == FormWindowState.Minimized)
            {
                Thread.Sleep(10);
                Keyboard.ReleaseAllKeys(false);
                return;
            }

            HandleKeys();

            Display.BeginFrame();
            Display.Clear(AgateLib.Geometry.Color.Black);
            
            Int32 xO = 0;
            Int32 yO = 0;
            foreach (SurfaceObject so in listBoxSurface.Items)
            {
                if (CheckInView(so.GetX(), so.GetY(), out xO, out yO))
                    so.Draw(xO, yO);
            }

            List<StaticObject> tempList = new List<StaticObject>();
            foreach (StaticObject so in listBoxSO.Items)
            {
                if(so.type == ObjectType.TYPE_SCRIPT || so.type == ObjectType.TYPE_SOUND || so.type == ObjectType.TYPE_EVENT)
                    tempList.Add(so);
                else
                {
                    Vector v = so.GetPosition();
                    if(CheckInView(v.X, v.Y, out xO, out yO))
                        so.Draw(xO, yO);
                }
            }

            foreach (StaticObject so in tempList)
            {
                Vector v = so.GetPosition();
                if (CheckInView(v.X, v.Y, out xO, out yO))
                    so.Draw(xO, yO);
            }
            tempList.Clear();

            if (GetDisplayPhyicsChecked())
            {
                foreach (Object o in listBoxPO.Items)
                {
                    try
                    {
                        PhysicObject po = (PhysicObject)o;
                        if (!CheckInView(po.rect.X, po.rect.Y, out xO, out yO))
                            continue;
                        PhysicObjectType pot = (PhysicObjectType)po.type;
                        switch (pot)
                        {
                            case PhysicObjectType.TYPE_BOX:
                                if (po.rot != 0)
                                {
                                    Double rotRadian = Math.PI * po.rot / 180.0;
                                    Point pCenter = new Point(Convert.ToInt32((xO + xO + po.rect.Width) / 2), Convert.ToInt32((yO + yO + po.rect.Height) / 2));
                                    Point UL = new Point(xO, yO);
                                    Point UR = new Point(xO + po.rect.Width, yO);
                                    Point LR = new Point(xO + po.rect.Width, yO + po.rect.Height);
                                    Point LL = new Point(xO, yO + po.rect.Height);
                                    Int32 X1 = Convert.ToInt32((UL.X - pCenter.X) * Math.Cos(rotRadian) - (UL.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y1 = Convert.ToInt32((UL.Y - pCenter.Y) * Math.Cos(rotRadian) + (UL.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X2 = Convert.ToInt32((UR.X - pCenter.X) * Math.Cos(rotRadian) - (UR.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y2 = Convert.ToInt32((UR.Y - pCenter.Y) * Math.Cos(rotRadian) + (UR.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X3 = Convert.ToInt32((LR.X - pCenter.X) * Math.Cos(rotRadian) - (LR.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y3 = Convert.ToInt32((LR.Y - pCenter.Y) * Math.Cos(rotRadian) + (LR.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X4 = Convert.ToInt32((LL.X - pCenter.X) * Math.Cos(rotRadian) - (LL.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y4 = Convert.ToInt32((LL.Y - pCenter.Y) * Math.Cos(rotRadian) + (LL.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Display.DrawLine(X1, Y1, X2, Y2, AgateLib.Geometry.Color.Green);
                                    Display.DrawLine(X2, Y2, X3, Y3, AgateLib.Geometry.Color.Green);
                                    Display.DrawLine(X3, Y3, X4, Y4, AgateLib.Geometry.Color.Green);
                                    Display.DrawLine(X4, Y4, X1, Y1, AgateLib.Geometry.Color.Green);
                                }
                                else
                                    Display.DrawRect(new AgateLib.Geometry.Rectangle(xO, yO, po.rect.Width, po.rect.Height), AgateLib.Geometry.Color.Green);
                                break;
                            case PhysicObjectType.TYPE_CIRCLE:
                                Int32 width = po.rect.Width;
                                Int32 height = po.rect.Height;
                                Int32 bigger = (width >= height) ? width : height;
                                Display.DrawEllipse(new AgateLib.Geometry.Rectangle(xO, yO, bigger, bigger), AgateLib.Geometry.Color.Green);
                                break;
                            case PhysicObjectType.TYPE_PLANE:
                                //Display.DrawRect(po.rect.X, po.rect.Y, po.rect.Width, 2);
                                break;
                        }
                    }
                    catch
                    {
                    }
                }
            }
            if (GetBoundaryDrawChecked())
            {
                if (lstBound.Count != 0)
                {
                    AgateLib.Geometry.Point lastpoint = new AgateLib.Geometry.Point(-1, -1);
                    AgateLib.Geometry.Point point = new AgateLib.Geometry.Point(-1, -1);
                    AgateLib.Geometry.Point firstpoint = new AgateLib.Geometry.Point(-1, -1);
                    foreach (Vector v in lstBound)
                    {
                        if (CheckInView(v.X, v.Y, out xO, out yO))
                        {
                            if (lastpoint.X == -1 && lastpoint.Y == -1)
                            {
                                lastpoint.X = xO;
                                lastpoint.Y = yO;
                                firstpoint = lastpoint;
                                if (lstBound.Count == 1)
                                    Display.DrawRect(xO, yO, 2, 2, AgateLib.Geometry.Color.Red);
                            }
                            else
                            {
                                point.X = xO;
                                point.Y = yO;
                                Display.DrawLine(lastpoint, point, AgateLib.Geometry.Color.Red);
                                lastpoint = point;
                            }
                        }
                    }
                    if (lstBound.Count > 2)
                    {
                        Display.DrawLine(lastpoint, firstpoint, AgateLib.Geometry.Color.Red);
                    }
                    GC.Collect();
                }
            }
            else if(GetObjectBoundaryDrawChecked())
            {
                if (listBoxSO.SelectedItem != null)
                {
                    StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                    if(so.HasBoundary())
                    { 
                        Polygon p = so.GetBoundary();
                        AgateLib.Geometry.Point lastpoint = new AgateLib.Geometry.Point(-1, -1);
                        AgateLib.Geometry.Point point = new AgateLib.Geometry.Point(-1, -1);
                        AgateLib.Geometry.Point firstpoint = new AgateLib.Geometry.Point(-1, -1);
                        foreach (Vector v in p.Points)
                        {
                            if (CheckInView(v.X, v.Y, out xO, out yO))
                            {
                                if (lastpoint.X == -1 && lastpoint.Y == -1)
                                {
                                    lastpoint.X = xO;
                                    lastpoint.Y = yO;
                                    firstpoint = lastpoint;
                                    if (p.Points.Count == 1)
                                        Display.DrawRect(xO, yO, 2, 2, AgateLib.Geometry.Color.Red);
                                }
                                else
                                {
                                    point.X = xO;
                                    point.Y = yO;
                                    Display.DrawLine(lastpoint, point, AgateLib.Geometry.Color.Red);
                                    lastpoint = point;
                                }
                            }
                        }
                        if (formStaticBoundary.GetVectorList().Items.Count > 2)
                        {
                            Display.DrawLine(lastpoint, firstpoint, AgateLib.Geometry.Color.Red);
                        }
                        Vector vsel = formStaticBoundary.GetSelectedVector();
                        if (CheckInView(vsel.X, vsel.Y, out xO, out yO))
                            Display.DrawRect(xO, yO, 2, 2, AgateLib.Geometry.Color.Blue);
                        GC.Collect();
                    }

                    if (!formStaticBoundary.IsSaved())
                    {
                        AgateLib.Geometry.Point lastpointa = new AgateLib.Geometry.Point(-1, -1);
                        AgateLib.Geometry.Point pointa = new AgateLib.Geometry.Point(-1, -1);
                        AgateLib.Geometry.Point firstpointa = new AgateLib.Geometry.Point(-1, -1);
                        foreach (Vector v in formStaticBoundary.GetVectorList().Items)
                        {
                            if (CheckInView(v.X, v.Y, out xO, out yO))
                            {
                                if (lastpointa.X == -1 && lastpointa.Y == -1)
                                {
                                    lastpointa.X = xO;
                                    lastpointa.Y = yO;
                                    firstpointa = lastpointa;
                                    if (formStaticBoundary.GetVectorList().Items.Count == 1)
                                        Display.DrawRect(xO, yO, 2, 2, AgateLib.Geometry.Color.Green);
                                }
                                else
                                {
                                    pointa.X = xO;
                                    pointa.Y = yO;
                                    Display.DrawLine(lastpointa, pointa, AgateLib.Geometry.Color.Green);
                                    lastpointa = pointa;
                                }
                            }
                        }
                        if (formStaticBoundary.GetVectorList().Items.Count > 2)
                        {
                            Display.DrawLine(lastpointa, firstpointa, AgateLib.Geometry.Color.Green);
                        }
                        Vector vsela = formStaticBoundary.GetSelectedVector();
                        if (CheckInView(vsela.X, vsela.Y, out xO, out yO))
                            Display.DrawRect(xO, yO, 2, 2, AgateLib.Geometry.Color.Blue);
                    }
                }
            }
            else if (GetPhysicObjectDrawChecked())
            {
                try
                {
                    PhysicObject po = (PhysicObject)listBoxPO.SelectedItem;
                    if (po != null)
                    {
                        PhysicObjectType pot = (PhysicObjectType)po.type;
                        switch (pot)
                        {
                            case PhysicObjectType.TYPE_BOX:
                                if (po.rot != 0)
                                {
                                    Double rotRadian = Math.PI * po.rot / 180.0;
                                    Point pCenter = new Point(Convert.ToInt32((po.rect.X + po.rect.X + po.rect.Width) / 2), Convert.ToInt32((po.rect.Y + po.rect.Y + po.rect.Height) / 2));
                                    Point UL = new Point(po.rect.X, po.rect.Y);
                                    Point UR = new Point(po.rect.X + po.rect.Width, po.rect.Y);
                                    Point LR = new Point(po.rect.X + po.rect.Width, po.rect.Y + po.rect.Height);
                                    Point LL = new Point(po.rect.X, po.rect.Y + po.rect.Height);
                                    Int32 X1 = Convert.ToInt32((UL.X - pCenter.X) * Math.Cos(rotRadian) - (UL.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y1 = Convert.ToInt32((UL.Y - pCenter.Y) * Math.Cos(rotRadian) + (UL.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X2 = Convert.ToInt32((UR.X - pCenter.X) * Math.Cos(rotRadian) - (UR.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y2 = Convert.ToInt32((UR.Y - pCenter.Y) * Math.Cos(rotRadian) + (UR.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X3 = Convert.ToInt32((LR.X - pCenter.X) * Math.Cos(rotRadian) - (LR.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y3 = Convert.ToInt32((LR.Y - pCenter.Y) * Math.Cos(rotRadian) + (LR.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X4 = Convert.ToInt32((LL.X - pCenter.X) * Math.Cos(rotRadian) - (LL.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y4 = Convert.ToInt32((LL.Y - pCenter.Y) * Math.Cos(rotRadian) + (LL.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Display.DrawLine(X1, Y1, X2, Y2, AgateLib.Geometry.Color.Blue);
                                    Display.DrawLine(X2, Y2, X3, Y3, AgateLib.Geometry.Color.Blue);
                                    Display.DrawLine(X3, Y3, X4, Y4, AgateLib.Geometry.Color.Blue);
                                    Display.DrawLine(X4, Y4, X1, Y1, AgateLib.Geometry.Color.Blue);
                                }
                                else
                                    Display.DrawRect(po.rect, AgateLib.Geometry.Color.Blue);
                                break;
                            case PhysicObjectType.TYPE_CIRCLE:
                                Int32 width = po.rect.Width;
                                Int32 height = po.rect.Height;
                                Int32 bigger = (width >= height) ? width : height;
                                Display.DrawEllipse(new AgateLib.Geometry.Rectangle(po.rect.X, po.rect.Y, bigger, bigger), AgateLib.Geometry.Color.Blue);
                                break;
                            case PhysicObjectType.TYPE_PLANE:
                                //Display.DrawRect(po.rect.X, po.rect.Y, po.rect.Width, 2);
                                break;
                        }
                    }
                    else
                    {
                        PhysicObjectType pot = (PhysicObjectType)cBoxType.SelectedIndex;
                        switch (pot)
                        {
                            case PhysicObjectType.TYPE_BOX:
                                if (txtRot.Text != "0")
                                {
                                    Double rotRadian = Math.PI * Convert.ToInt32(txtRot.Text) / 180.0;
                                    Point pCenter = new Point(Convert.ToInt32((current.X + first.X) / 2), Convert.ToInt32((current.Y + first.Y) / 2));
                                    Point UL = new Point(first.X, first.Y);
                                    Point UR = new Point(current.X, first.Y);
                                    Point LR = new Point(current.X, current.Y);
                                    Point LL = new Point(first.X, current.Y);
                                    Int32 X1 = Convert.ToInt32((UL.X - pCenter.X) * Math.Cos(rotRadian) - (UL.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y1 = Convert.ToInt32((UL.Y - pCenter.Y) * Math.Cos(rotRadian) + (UL.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X2 = Convert.ToInt32((UR.X - pCenter.X) * Math.Cos(rotRadian) - (UR.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y2 = Convert.ToInt32((UR.Y - pCenter.Y) * Math.Cos(rotRadian) + (UR.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X3 = Convert.ToInt32((LR.X - pCenter.X) * Math.Cos(rotRadian) - (LR.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y3 = Convert.ToInt32((LR.Y - pCenter.Y) * Math.Cos(rotRadian) + (LR.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Int32 X4 = Convert.ToInt32((LL.X - pCenter.X) * Math.Cos(rotRadian) - (LL.Y - pCenter.Y) * Math.Sin(rotRadian)) + pCenter.X;
                                    Int32 Y4 = Convert.ToInt32((LL.Y - pCenter.Y) * Math.Cos(rotRadian) + (LL.X - pCenter.X) * Math.Sin(rotRadian)) + pCenter.Y;
                                    Display.DrawLine(X1, Y1, X2, Y2, AgateLib.Geometry.Color.Red);
                                    Display.DrawLine(X2, Y2, X3, Y3, AgateLib.Geometry.Color.Red);
                                    Display.DrawLine(X3, Y3, X4, Y4, AgateLib.Geometry.Color.Red);
                                    Display.DrawLine(X4, Y4, X1, Y1, AgateLib.Geometry.Color.Red);
                                }
                                else
                                    Display.DrawRect(new AgateLib.Geometry.Rectangle(first.X, first.Y, current.X - first.X, current.Y - first.Y), AgateLib.Geometry.Color.Red);
                                break;
                            case PhysicObjectType.TYPE_CIRCLE:
                                Int32 width = current.X - first.X;
                                Int32 height = current.Y - first.Y;
                                Int32 bigger = (width >= height) ? width : height;
                                Display.DrawEllipse(new AgateLib.Geometry.Rectangle(first.X, first.Y, bigger, bigger), AgateLib.Geometry.Color.Red);
                                break;
                            case PhysicObjectType.TYPE_PLANE:
                                //Display.DrawRect(po.rect.X, po.rect.Y, po.rect.Width, 2);
                                break;
                        }
                    }
                }
                catch
                {
                }
            }

            if (lastStaticObject != null)
            {
                Vector v = lastStaticObject.GetPosition();
                if (CheckInView(v.X, v.Y, out xO, out yO))
                    lastStaticObject.Draw(xO, yO);
            }
            if (lastSurface != null)
            {
                if (CheckInView(lastSurface.GetX(), lastSurface.GetY(), out xO, out yO))
                    lastSurface.Draw(xO, yO);
            }

            Display.EndFrame();

            Thread.Sleep(10);
        }

        private void Main_DragDrop(object sender, DragEventArgs e)
        {
            if (validData)
            {
#if THUMBNAIL
                while (getImageThread.IsAlive)
                {
                    Application.DoEvents();
                    Thread.Sleep(0);
                }
#endif
                if (GetStaticObjectChecked())
                {
                    StaticObject so = new StaticObject(((PathType)lvo.itm.Tag).filePath);
                    //so.CreateSprite(lvo.sizeX, lvo.sizeY);
                    so.Load(lvo.sizeX, lvo.sizeY);
                    Point p = PointToClient(new Point(e.X, e.Y));
                    //so.SetPosition(new Vector(p.X, p.Y));
                    so.SetPosition(ConvertToVirtualCoordinates(Mouse.Position.X, Mouse.Position.Y));
                    if (formImageFileView.IsMapObject())
                    {
                        so.obj = new MapObject();
                        so.type = ObjectType.TYPE_MAP;
                    }
                    listBoxSO.Items.Add(so);
                }
                else
                {
                    SurfaceObject so = new SurfaceObject(((PathType)lvo.itm.Tag).filePath);
                    Point p = PointToClient(new Point(e.X, e.Y));
                    //so.SetPosition(p.X, p.Y);
                    Vector v = ConvertToVirtualCoordinates(Mouse.Position.X, Mouse.Position.Y);
                    so.SetPosition(v.X, v.Y);
                    so.SetSize(lvo.sizeX, lvo.sizeY);
                    listBoxSurface.Items.Add(so);
                }
#if THUMBNAIL
                thumbnail.Visible = false;
                thumbnail.Image.Dispose();
#endif
                /*image = nextImage;
                AdjustView();
                if ((thumbnail.Image != null) && (thumbnail.Image != nextImage))
                {
                    thumbnail.Image.Dispose();
                }
                thumbnail.Image = image;*/

            }
            else if (validSoundData)
            {
                StaticObject so = new StaticObject("sound.png");
                Point p = PointToClient(new Point(e.X, e.Y));
                so.SetPosition(ConvertToVirtualCoordinates(Mouse.Position.X, Mouse.Position.Y));
                so.type = ObjectType.TYPE_SOUND;
                SoundObject sound = new SoundObject();
                sound.Name = sf.name;
                sound.File = sf.file;
                sound.Type = sf.type;
                so.obj = sound;
                so.CreateSpriteFromResource("Sound", 40, 32);
                
                listBoxSO.Items.Add(so);
            }
            else if (validEventData)
            {
                if (ef.type > MapEventType.MAP_EVENT_LEVEL_END)
                {
                    StaticObject so = new StaticObject("script.png");
                    Point p = PointToClient(new Point(e.X, e.Y));
                    so.SetPosition(ConvertToVirtualCoordinates(Mouse.Position.X, Mouse.Position.Y));
                    so.type = ObjectType.TYPE_SCRIPT;
                    EventObject eo = new EventObject();
                    eo.Type = ef.type;
                    so.obj = eo;
                    so.CreateSpriteFromResource("Script", 32, 32);

                    listBoxSO.Items.Add(so);
                }
                else
                {
                    StaticObject so = new StaticObject("event.png");
                    Point p = PointToClient(new Point(e.X, e.Y));
                    so.SetPosition(ConvertToVirtualCoordinates(Mouse.Position.X, Mouse.Position.Y));
                    so.type = ObjectType.TYPE_EVENT;
                    EventObject eo = new EventObject();
                    eo.Type = ef.type;
                    so.obj = eo;
                    so.CreateSpriteFromResource("Event", 32, 32);

                    listBoxSO.Items.Add(so);
                }
            }
        }

        private void Main_DragEnter(object sender, DragEventArgs e)
        {
            String filename;
            validData = GetFilename(out lvo, e);
            if (!validData)
            {
                validSoundData = GetSoundFilename(out sf, e);
                if (!validSoundData)
                    validEventData = GetEventFilename(out ef, e);
            }
            if (validData)
            {
                filename = ((PathType)lvo.itm.Tag).filePath;
#if THUMBNAIL
                if (lastFilename != filename)
                {
                    thumbnail.Image = null;
                    thumbnail.Visible = false;
                    lastFilename = filename;
                    //thumbnail.Size = new Size(lvo.sizeX, lvo.sizeY);
                    if (getImageThread != null)
                        getImageThread.Abort();
                    getImageThread = new Thread(new ThreadStart(LoadImage));
                    getImageThread.Start();
                }
                else
                {
                    thumbnail.Visible = true;
                }
#endif
                e.Effect = DragDropEffects.Copy;
            }
            else if(validSoundData)
            {
                filename = sf.file;
                e.Effect = DragDropEffects.Copy;
            }
            else if (validEventData)
            {
                filename = "event";
                e.Effect = DragDropEffects.Copy;
            }
            else
            {
                e.Effect = DragDropEffects.None;
            }
        }

        private void Main_DragLeave(object sender, EventArgs e)
        {
#if THUMBNAIL
            if(validData)
                thumbnail.Visible = false;
#endif
        }

        private void Main_DragOver(object sender, DragEventArgs e)
        {
#if THUMBNAIL
            if (validData)
            {
                if ((e.X != lastX) || (e.Y != lastY))
                {
                    SetThumbnailLocation(this.PointToClient(new Point(e.X, e.Y)));
                }
            }
#endif
        }

        protected bool GetFilename(out ListViewObject lvo, DragEventArgs e)
        {
            bool ret = false;
            lvo = null;

            if ((e.AllowedEffect & DragDropEffects.Copy) == DragDropEffects.Copy)
            {
                lvo = ((IDataObject)e.Data).GetData(typeof(ListViewObject)) as ListViewObject;
                if (lvo != null)
                {
                    if (lvo.itm != null)
                    {
                        /*if (data.itm.Tag != null)
                        {
                            filename = (String)data.Tag;
                            string ext = Path.GetExtension(filename).ToLower();
                            ret = true;
                        }*/
                        ret = true;
                    }
                }
            }
            return ret;
        }

        protected bool GetSoundFilename(out SoundFile sf, DragEventArgs e)
        {
            bool ret = false;
            sf = null;

            if ((e.AllowedEffect & DragDropEffects.Copy) == DragDropEffects.Copy)
            {
                sf = ((IDataObject)e.Data).GetData(typeof(SoundFile)) as SoundFile;
                if (sf != null)
                {
                    ret = true;
                }
            }
            return ret;
        }

        protected bool GetEventFilename(out EventFile ef, DragEventArgs e)
        {
            bool ret = false;
            ef = null;

            if ((e.AllowedEffect & DragDropEffects.Copy) == DragDropEffects.Copy)
            {
                ef = ((IDataObject)e.Data).GetData(typeof(EventFile)) as EventFile;
                if (ef != null)
                {
                    ret = true;
                }
            }
            return ret;
        }

        protected void SetThumbnailLocation(Point p)
        {
            if (thumbnail.Image == null)
            {
                thumbnail.Visible = false;
            }
            else
            {
                /*p.X -= thumbnail.Width;// / 2;
                p.Y -= thumbnail.Height;// / 2;*/
                thumbnail.Location = p;
                thumbnail.Visible = true;
            }
        }

        protected void AdjustView()
        {
            float fw = this.ClientSize.Width;
            float fh = this.ClientSize.Height;
            float iw = image.Width;
            float ih = image.Height;

            // iw/fw > ih/fh, then iw/fw controls ih

            float rw = fw / iw;			// ratio of width
            float rh = fh / ih;			// ratio of height

            if (rw < rh)
            {
                thumbnail.Width = (int)fw;
                thumbnail.Height = (int)(ih * rw);
                thumbnail.Left = 0;
                thumbnail.Top = (int)((fh - thumbnail.Height) / 2);
            }
            else
            {
                thumbnail.Width = (int)(iw * rh);
                thumbnail.Height = (int)fh;
                thumbnail.Left = (int)((fw - thumbnail.Width) / 2);
                thumbnail.Top = 0;
            }
        }

		protected override void OnLayout(LayoutEventArgs levent)
		{
			if (image != null)
			{
				AdjustView();
			}
            base.OnLayout(levent);
		}

		public delegate void AssignImageDlgt();

		protected void LoadImage()
		{
            try
            {
                nextImage = new Bitmap(lastFilename);
                this.Invoke(new AssignImageDlgt(AssignImage));
            }
            catch
            {
            }
		}

		protected void AssignImage()
		{
			/*thumbnail.Width=100;
			// 100    iWidth
			// ---- = ------
			// tHeight  iHeight
			thumbnail.Height=nextImage.Height * 100 / nextImage.Width;*/
            thumbnail.Width = lvo.sizeX;
            thumbnail.Height = lvo.sizeY;
			SetThumbnailLocation(this.PointToClient(new Point(lastX, lastY)));
            thumbnail.Image = nextImage;
            thumbnail.Focus();
            thumbnail.Visible = true;
		}

        public StaticObject GetSelectedStaticObject()
        {
            return (StaticObject)listBoxSO.SelectedItem;
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBoxSurface.SelectedItem == null)
                return;
            SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
            so.Delete();
            listBoxSurface.Items.Remove(so);
        }

        private void deleteToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (listBoxSO.SelectedItem == null)
                return;
            StaticObject so = (StaticObject)listBoxSO.SelectedItem;
            so.Delete();
            listBoxSO.Items.Remove(so);
        }


        private void deleteToolStripMenuItemPO_Click(object sender, EventArgs e)
        {
            if (listBoxPO.SelectedItem == null)
                return;
            PhysicObject po = (PhysicObject)listBoxPO.SelectedItem;
            //po.Delete();
            listBoxPO.Items.Remove(po);
        }

        private void listBoxSurface_SelectedIndexChanged(object sender, EventArgs e)
        {
            listBoxSO.SelectedItem = null;
            listBoxPO.SelectedItem = null;
            if(lastSurface != null)
                lastSurface.GetSurface().Color = lastSurfaceColor;
            if (listBoxSurface.SelectedItem != null)
            {
                SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                txtX.Text = so.GetX().ToString();
                txtY.Text = so.GetY().ToString();
                txtSX.Text = so.GetSizeX().ToString();
                txtSY.Text = so.GetSizeY().ToString();
                txtRot.Text = so.GetSurface().RotationAngleDegrees.ToString();
                lastSurface = so;
                lastSurfaceColor = lastSurface.GetSurface().Color;
                lastSurface.GetSurface().Color = AgateLib.Geometry.Color.Red;
                cBoxType.Enabled = false;
            }
            else
                lastSurface = null;
        }

        private void listBoxSO_SelectedIndexChanged(object sender, EventArgs e)
        {
            listBoxSurface.SelectedItem = null;
            listBoxPO.SelectedItem = null;
            if (lastStaticObject != null)
            {
                lastStaticObject.GetSprite().Color = lastStaticObjectColor;
            }
            if (listBoxSO.SelectedItem != null)
            {
                StaticObject so = ((StaticObject)listBoxSO.SelectedItem);
                Vector v = so.GetPosition();
                txtX.Text = v.X.ToString();
                txtY.Text = v.Y.ToString();
                Sprite s = so.GetSprite();
                txtSX.Text = s.SpriteWidth.ToString();
                txtSY.Text = s.SpriteHeight.ToString();
                txtRot.Text = s.RotationAngleDegrees.ToString();
                tBarFrame.Maximum = s.Frames.Count;
                tBarFrame.Value = s.CurrentFrameIndex;
                if (s.IsAnimating)
                    chkBoxAnimated.Checked = true;
                lastStaticObject = so;
                lastStaticObjectColor = lastStaticObject.GetSprite().Color;
                s.Color = AgateLib.Geometry.Color.Red;
                if(so.HasBoundary())
                    formStaticBoundary.SetPolygon(so.GetBoundary());
                cBoxType.Enabled = true;
                cBoxType.Items.Clear();
                cBoxType.Items.AddRange(Enum.GetNames(typeof(ObjectType)));
                cBoxType.SelectedIndex = Convert.ToInt32(so.type);
                if (so.type != ObjectType.TYPE_NONE)
                {
                    switch (so.type)
                    {
                        case ObjectType.TYPE_PLAYER:
                            pGrid.SelectedObject = (Player)so.obj;
                            break;
                        case ObjectType.TYPE_UNIT:
                            pGrid.SelectedObject = (Creature)so.obj;
                            break;
                        case ObjectType.TYPE_GAMEOBJECT:
                            pGrid.SelectedObject = (Gameobject)so.obj;
                            break;
                        case ObjectType.TYPE_EVENT:
                            pGrid.SelectedObject = (EventObject)so.obj;
                            break;
                        case ObjectType.TYPE_SCRIPT:
                            pGrid.SelectedObject = so.obj;
                            break;
                        case ObjectType.TYPE_MAP:
                            pGrid.SelectedObject = (MapObject)so.obj;
                            break;
                        case ObjectType.TYPE_SOUND:
                            pGrid.SelectedObject = (SoundObject)so.obj;
                            break;
                        default:
                            pGrid.SelectedObject = null;
                            break;
                    }
                }
            }
            else
                lastStaticObject = null;
        }

        private void listBoxPO_SelectedIndexChanged(object sender, EventArgs e)
        {
            listBoxSurface.SelectedItem = null;
            listBoxSO.SelectedItem = null;
            if (listBoxPO.SelectedItem != null)
            {
                PhysicObject po = ((PhysicObject)listBoxPO.SelectedItem);
                txtX.Text = po.rect.X.ToString();
                txtY.Text = po.rect.Y.ToString();
                txtSX.Text = po.rect.Width.ToString();
                txtSY.Text = po.rect.Height.ToString();
                cBoxType.Enabled = true;
                cBoxType.Items.Clear();
                cBoxType.Items.AddRange(Enum.GetNames(typeof(PhysicObjectType)));
                cBoxType.SelectedIndex = Convert.ToInt32(po.type);
                pGrid.SelectedObject = po;
            }
        }

        private void tBarFrame_ValueChanged(object sender, EventArgs e)
        {
            if(lastStaticObject != null)
                lastStaticObject.SetFrameIndex(tBarFrame.Value);
        }

        private void butSave_Click(object sender, EventArgs e)
        {
            /*if (GetStaticObjectChecked())
            {
                if(lastStaticObject != null)
                {
                    //lastStaticObject.SetPosition(new Vector(Convert.ToInt32(txtX.Text), Convert.ToInt32(txtY.Text)));
                    String FileName = lastStaticObject.GetFilename();
                    listBoxSO.Items.Remove(lastStaticObject);
                    lastStaticObject = new StaticObject(FileName);
                    lastStaticObject.CreateSprite(Convert.ToInt32(txtX.Text), Convert.ToInt32(txtY.Text));
                    lastStaticObject.SetPosition(new Vector(Convert.ToInt32(txtX.Text), Convert.ToInt32(txtY.Text)));
                    if (chkBoxAnimated.Checked)
                        lastStaticObject.SetFrameIndex(-1);
                    listBoxSO.Items.Add(lastStaticObject);
                }
            }*/
            /*else
            {
                if (lastSurface.Surf != null)
                {
                    String FileName = lastSurface.FileName;

                }
            }*/

            if (GetStaticObjectChecked())
            {
                if (lastStaticObject != null)
                {
                    lastStaticObject.SetPosition(new Vector(Convert.ToInt32(txtX.Text), Convert.ToInt32(txtY.Text)));
                    lastStaticObject.GetSprite().DisplaySize = new AgateLib.Geometry.Size(Convert.ToInt32(txtSX.Text), Convert.ToInt32(txtSY.Text));
                    switch (lastStaticObject.type)
                    {
                        case ObjectType.TYPE_PLAYER:
                            lastStaticObject.obj = (Player)pGrid.SelectedObject;
                            break;
                        case ObjectType.TYPE_UNIT:
                            lastStaticObject.obj = (Creature)pGrid.SelectedObject;
                            break;
                        case ObjectType.TYPE_GAMEOBJECT:
                            lastStaticObject.obj = (Gameobject)pGrid.SelectedObject;
                            break;
                        case ObjectType.TYPE_EVENT:
                            lastStaticObject.obj = (EventObject)pGrid.SelectedObject;
                            break;
                        case ObjectType.TYPE_SCRIPT:
                            lastStaticObject.obj = (BaseObject)pGrid.SelectedObject;
                            break;
                        case ObjectType.TYPE_MAP:
                            lastStaticObject.obj = (MapObject)pGrid.SelectedObject;
                            break;
                        case ObjectType.TYPE_SOUND:
                            lastStaticObject.obj = (SoundObject)pGrid.SelectedObject;
                            break;
                    };
                }
            }
            if (GetPhysicObjectDrawChecked())
            {
                if (cBoxType.SelectedIndex == -1)
                    return;

                PhysicObject po = new PhysicObject();
                po.type = (PhysicObjectType)cBoxType.SelectedIndex;
                Vector pos = ConvertToVirtualCoordinates(first.X, first.Y);
                po.rect = new AgateLib.Geometry.Rectangle(pos.X, pos.Y, current.X - first.X, current.Y - first.Y);
                po.rot = Convert.ToInt32(txtRot.Text);
                listBoxPO.Items.Add(po);
            }
        }

        private void butUnselect_Click(object sender, EventArgs e)
        {
            listBoxSurface.SelectedItem = null;
            listBoxSO.SelectedItem = null;
            listBoxPO.SelectedItem = null;
        }

        private void cBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (toolStripButStaticObject.Checked)
            {
                ObjectType type = (ObjectType)cBoxType.SelectedIndex;
                if (lastStaticObject.type != type)
                {
                    lastStaticObject.type = type;
                    switch (lastStaticObject.type)
                    {
                        case ObjectType.TYPE_PLAYER:
                            lastStaticObject.obj = new Player();
                            pGrid.SelectedObject = (Player)lastStaticObject.obj;
                            break;
                        case ObjectType.TYPE_UNIT:
                            lastStaticObject.obj = new Creature();
                            pGrid.SelectedObject = (Creature)lastStaticObject.obj;
                            break;
                        case ObjectType.TYPE_GAMEOBJECT:
                            lastStaticObject.obj = new Gameobject();
                            pGrid.SelectedObject = (Gameobject)lastStaticObject.obj;
                            break;
                        case ObjectType.TYPE_EVENT:
                            lastStaticObject.obj = new EventObject();
                            pGrid.SelectedObject = (EventObject)lastStaticObject.obj;
                            break;
                        case ObjectType.TYPE_SCRIPT:
                            lastStaticObject.obj = new BaseObject();
                            pGrid.SelectedObject = lastStaticObject.obj;
                            break;
                        case ObjectType.TYPE_MAP:
                            lastStaticObject.obj = new MapObject();
                            pGrid.SelectedObject = (MapObject)lastStaticObject.obj;
                            break;
                        case ObjectType.TYPE_SOUND:
                            lastStaticObject.obj = new SoundObject();
                            pGrid.SelectedObject = (SoundObject)lastStaticObject.obj;
                            break;
                    }
                    ((RListBox)listBoxSO).RefreshAll();
                }
            }
            if (listBoxPO.SelectedItem != null)
            {
                PhysicObject po = (PhysicObject)listBoxPO.SelectedItem;
                po.type = (PhysicObjectType)cBoxType.SelectedIndex;
            }
        }

        private void txtVX_TextChanged(object sender, EventArgs e)
        {
            if (mousePosUpdate)
                return;
            try
            {
                currentX = Convert.ToInt32(txtVX.Text);
            }
            catch
            {
            }
        }

        private void txtVY_TextChanged(object sender, EventArgs e)
        {
            if (mousePosUpdate)
                return;
            try
            {
                currentY = Convert.ToInt32(txtVY.Text);
            }
            catch
            {
            }
        }

        private void txtX_TextChanged(object sender, EventArgs e)
        {
            if (mousePosUpdate)
                return;
            try
            {
                if (toolStripButMoveSurface.Checked)
                {
                    if (lastSurface != null)
                    {
                        lastSurface.SetPosition(Convert.ToInt32(txtX.Text), lastSurface.GetY());
                    }
                }
                else if (toolStripButDisplayPhysics.Checked)
                {
                    if (lastStaticObject != null)
                    {
                        lastStaticObject.SetPosition(new Vector(Convert.ToInt32(txtX.Text), lastStaticObject.GetPosition().Y));
                    }
                }
            }
            catch
            {
            	
            }
        }

        private void txtY_TextChanged(object sender, EventArgs e)
        {
            if (mousePosUpdate)
                return;
            try
            {
                if (toolStripButMoveSurface.Checked)
                {
                    if (lastSurface != null)
                    {
                        lastSurface.SetPosition(lastSurface.GetX(), Convert.ToInt32(txtY.Text));
                    }
                }
                else if (toolStripButDisplayPhysics.Checked)
                {
                    if (lastStaticObject != null)
                    {
                        lastStaticObject.SetPosition(new Vector(lastStaticObject.GetPosition().X, Convert.ToInt32(txtY.Text)));
                    }
                }
            }
            catch
            {
            }
        }

        private void txtSX_TextChanged(object sender, EventArgs e)
        {
            if (mousePosUpdate)
                return;
            try
            {
                if (toolStripButMoveSurface.Checked)
                {
                    if (lastSurface != null)
                    {
                        lastSurface.SetSize(Convert.ToInt32(txtSX.Text), lastSurface.GetSizeY());
                    }
                }
                else if (toolStripButDisplayPhysics.Checked)
                {
                    if (lastStaticObject != null)
                    {
                        lastStaticObject.GetSprite().DisplayWidth = Convert.ToInt32(txtSX.Text);
                    }
                }
            }
            catch
            {
            }
        }

        private void txtSY_TextChanged(object sender, EventArgs e)
        {
            if (mousePosUpdate)
                return;
            try
            {
                if (toolStripButMoveSurface.Checked)
                {
                    if (lastSurface != null)
                    {
                        lastSurface.SetSize(lastSurface.GetSizeX(), Convert.ToInt32(txtSY.Text));
                    }
                }
                else if (toolStripButDisplayPhysics.Checked)
                {
                    if (lastStaticObject != null)
                    {
                        lastStaticObject.GetSprite().DisplayWidth = Convert.ToInt32(txtSY.Text);
                    }
                }
            }
            catch
            {
            }
        }

        private void butRelPath_Click(object sender, EventArgs e)
        {
            DialogResult dr = folderBrowserDialogRelative.ShowDialog();
            if (dr == DialogResult.OK)
            {
                relativePath = folderBrowserDialogRelative.SelectedPath;
                toolStripStatusLabelRelPath.Text = relativePath;
            }
        }

        private void imageViewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (formImageFileView == null || formImageFileView.IsDisposed)
                formImageFileView = new ImageFileView(formTextureBox);
            formImageFileView.Show();
        }

        private void soundViewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (formSoundFileView == null || formSoundFileView.IsDisposed)
                formSoundFileView = new SoundFileView();
            formSoundFileView.Show();
        }

        private void eventViewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (formEventView == null || formEventView.IsDisposed)
                formEventView = new EventView();
            formEventView.Show();
        }
    }
}