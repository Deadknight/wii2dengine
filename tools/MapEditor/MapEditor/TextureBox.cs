using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using AgateLib;
using System.Threading;
using AgateLib.DisplayLib;
using AgateLib.Sprites;
using AgateLib.InputLib;

namespace MapEditor
{
    public partial class TextureBox : Form
    {
        private Main pForm;
        DisplayWindow window;
        bool IsSurface;
        Surface surf;
        Sprite spr;
        bool exit;

        public TextureBox(Main pForm)
        {
            InitializeComponent();

            surf = null;
            spr = null;
            IsSurface = true;
            exit = false;
            this.pForm = pForm;
            /*t = new Thread(new ThreadStart(Run));
            t.Start();*/
        }

        public void Run()
        {
            using (AgateSetup displaySetup = new AgateSetup())
            {
                displaySetup.AskUser = false;
                displaySetup.Initialize(true, false, false);
                /*if (displaySetup.Cancel)
                    return;*/

                //Sprite.UseSpriteCache = false;
                CreateWindowParams cwp = new CreateWindowParams();
                cwp.RenderToControl = true;
                cwp.RenderTarget = pictBoxTexture;
                cwp.IsFullScreen = false;
                window = new DisplayWindow(cwp);

                while (!exit)
                {
                    if (this.Visible == false || this.WindowState == FormWindowState.Minimized)
                    {
                        Thread.Sleep(10);
                        Keyboard.ReleaseAllKeys(false);
                        continue;
                    }

                    Display.BeginFrame();
                    Display.Clear(AgateLib.Geometry.Color.Black);

                    if (IsSurface)
                    {
                        if (surf != null)
                        {
                            surf.Draw(0, 0);
                        }
                    }
                    else
                    {
                        if (spr != null)
                        {
                            spr.Draw(0, 0);
                        }
                    }

                    Display.EndFrame();

                    Thread.Sleep(100);

                    Core.KeepAlive();
                }
            }
        }

        public void LoadImageFromFile(String s, Int32 sizeX, Int32 sizeY)
        {
            /*IsSurface = !pForm.GetStaticObjectChecked();
                
            Image b = Bitmap.FromFile(s);

            if (IsSurface)
            {
                if (surf != null)
                    surf.Dispose();
                surf = new Surface(s);
            }
            else
            {
                if (spr != null)
                    spr.Dispose();
                spr = new Sprite(s, sizeX, sizeY);
            }*/
        }

        private void TextureBox_Load(object sender, EventArgs e)
        {

        }
    }
}