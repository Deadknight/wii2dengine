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
    public struct PathType
    {
        public String dirPath;
        public String filePath;
        public bool Directory;
    }

    public partial class ImageFileView : Form
    {
        public TextureBox tBox;
        public ImageFileView(TextureBox tBox)
        {
            InitializeComponent();
            this.tBox = tBox;
        }

        private String lastPath = "";
        private String extensionToSearch = ".png";
        private String lastExtensionToSearch = ".png";

        private Int32 count = 0;
        private Int32 limit = 5;
        private bool SearchDirectory(String dirPath, String dirOriginal, ref List<PathType> lst, ref ImageList il)
        {
            String[] dirs = Directory.GetDirectories(dirPath);
            foreach (String dir in dirs)
            {
                String[] files = Directory.GetFiles(dir);
                if (files.Length == 0)
                {
                    if (count <= limit)
                    {
                        count++;
                        if(SearchDirectory(dir, dirOriginal, ref lst, ref il))
                            return true;
                    }
                }
                else
                {
                    foreach (String file in files)
                    {
                        String ext = Path.GetExtension(file);
                        if (extensionToSearch.Contains(ext))
                        {
                            PathType pt = new PathType();
                            pt.Directory = true;
                            pt.dirPath = dir;
                            pt.filePath = file;
                            lst.Add(pt);
                            il.Images.Add(Bitmap.FromFile(file));
                            return true;
                        }
                    }
                }
            }
            return true;
        }

        private String GetUnitFilePath(String filePath)
        {
            String shortPath = "";
            String fullpath = "";
            FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read);
            EndianBinaryReader br = new EndianBinaryReader(BigEndianBitConverter.Big, fs, Encoding.ASCII);
            UInt32 uniqueNameLength = br.ReadUInt32();
            br.ReadBytes((Int32)uniqueNameLength);
            UInt32 virtualDirLength = br.ReadUInt32();
            String virDir = "";
            if(virtualDirLength > 0)
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
                shortPath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameShortLength));
                Int32 fileNameFullLength = (Int32)br.ReadUInt32();
                fullpath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameFullLength));
                if ((flags & 0x20100) > 0)
                {
                    break;
                }
            }

            br.Close();
            fs.Close();

            String path = Path.GetDirectoryName(filePath);

            return path + "\\" + virDir + shortPath + Path.GetExtension(fullpath);
        }

        private String GetGoFilePath(String filePath)
        {
            String shortPath = "";
            String fullpath = "";
            FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read);
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
            shortPath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameShortLength));
            Int32 fileNameFullLength = (Int32)br.ReadUInt32();
            fullpath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameFullLength));

            br.Close();
            fs.Close();

            String path = Path.GetDirectoryName(filePath);

            return path + "\\" + virDir + shortPath + Path.GetExtension(fullpath);
        }

        public void Reload()
        {
            if (lastPath == "")
                return;

            listViewImages.Items.Clear();
            if (listViewImages.LargeImageList != null)
            {
                foreach (Image i in listViewImages.LargeImageList.Images)
                {
                    i.Dispose();
                }
                listViewImages.LargeImageList.Images.Clear();
                listViewImages.LargeImageList.Dispose();
            }

            ImageList il = new ImageList();
            il.ImageSize = new Size(64, 64);
            List<PathType> lst = new List<PathType>();

            String[] files = Directory.GetFiles(lastPath);
            foreach (String file in files)
            {
                String ext = Path.GetExtension(file);
                if (extensionToSearch.Contains(ext))
                {
                    PathType pt = new PathType();
                    pt.Directory = false;
                    pt.filePath = file;
                    lst.Add(pt);

                    if (ext == ".unit")
                        il.Images.Add(Bitmap.FromFile(GetUnitFilePath(file)));
                    else if(ext == ".go")
                        il.Images.Add(Bitmap.FromFile(GetGoFilePath(file)));
                    else
                        il.Images.Add(Bitmap.FromFile(file));
                }
            }

            listViewImages.LargeImageList = il;

            Int32 countIn = 0;
            foreach (PathType pt in lst)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Tag = pt;
                lvi.ImageIndex = countIn;
                listViewImages.Items.Add(lvi);
                countIn++;
            }
        }

        private void butBrowse_Click(object sender, EventArgs e)
        {
            listViewImages.Items.Clear();
            if (listViewImages.LargeImageList != null)
            {
                foreach (Image i in listViewImages.LargeImageList.Images)
                {
                    i.Dispose();
                }
                listViewImages.LargeImageList.Images.Clear();
                listViewImages.LargeImageList.Dispose();
            }

            DialogResult dr = folderBrowserDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ImageList il = new ImageList();
                il.ImageSize = new Size(64, 64);
                List<PathType> lst = new List<PathType>();
                lastPath = folderBrowserDialog.SelectedPath;

                String [] files = Directory.GetFiles(folderBrowserDialog.SelectedPath);
                foreach (String file in files)
                {
                    String ext = Path.GetExtension(file);
                    if (extensionToSearch == ext)
                    {
                        PathType pt = new PathType();
                        pt.Directory = false;
                        pt.filePath = file;
                        lst.Add(pt);

                        if (ext == ".unit")
                            il.Images.Add(Bitmap.FromFile(GetUnitFilePath(file)));
                        else if (ext == ".go")
                            il.Images.Add(Bitmap.FromFile(GetGoFilePath(file)));
                        else
                            il.Images.Add(Bitmap.FromFile(file));
                    }
                }

                /*String[] dirs = Directory.GetDirectories(folderBrowserDialog.SelectedPath);
                foreach (String dir in dirs)
                {
                    String[] filesIn = Directory.GetFiles(dir);
                    if (filesIn.Length == 0)
                    {
                        SearchDirectory(dir, folderBrowserDialog.SelectedPath, ref lst, ref il);
                        count = 0;
                    }
                    else
                    {
                        foreach (String file in filesIn)
                        {
                            String ext = Path.GetExtension(file);
                            if (ext == ".png" || ext == ".jpg" || ext == ".bmp" || ext == ".gif")
                            {
                                PathType pt = new PathType();
                                pt.Directory = true;
                                pt.dirPath = dir;
                                lst.Add(pt);
                                il.Images.Add(Bitmap.FromFile(file));
                            }
                        }
                    }
                }*/

                listViewImages.LargeImageList = il;

                Int32 countIn = 0;
                foreach (PathType pt in lst)
                {
                    ListViewItem lvi = new ListViewItem();
                    lvi.Tag = pt;
                    lvi.ImageIndex = countIn;
                    listViewImages.Items.Add(lvi);
                    countIn++;
                }
            }
        }

        public void SetExtension(String ext)
        {
            extensionToSearch = ext;
            lastExtensionToSearch = ext;
            cBoxMapObject.Checked = false;
        }

        public bool IsMapObject()
        {
            return cBoxMapObject.Checked;
        }

        private void listViewImages_MouseDown(object sender, MouseEventArgs e)
        {
            ListViewItem lvi = listViewImages.GetItemAt(e.X, e.Y);

            if (lvi == null)
            {
                return;
            }

            if (e.Button == MouseButtons.Left)
            {
                PathType pt = (PathType)lvi.Tag;
                //tBox.LoadImageFromFile(s, Convert.ToInt32(txtSizeX.Text), Convert.ToInt32(txtSizeY.Text));

                ListViewObject lvo = new ListViewObject();
                lvo.itm = lvi;
                lvo.sizeX = Convert.ToInt32(txtSizeX.Text);
                lvo.sizeY = Convert.ToInt32(txtSizeY.Text);
                listViewImages.DoDragDrop(lvo, DragDropEffects.All);
            }
        }

        private void listViewImages_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listViewImages.SelectedItems.Count > 0)
            {
                PathType pt = (PathType)listViewImages.SelectedItems[0].Tag;
                if (pt.filePath == null)
                    return;
                String fname = Path.GetDirectoryName(pt.filePath) + "\\" + Path.GetFileNameWithoutExtension(pt.filePath) + ".prop";
                if (File.Exists(fname))
                {
                    String[] lines = File.ReadAllLines(fname);
                    String line = lines[0];
                    String[] spl = line.Split(',');
                    txtSizeX.Text = spl[1];
                    txtSizeY.Text = spl[2];
                    /*Bitmap bmp = new Bitmap(Convert.ToInt32(spl[1]), Convert.ToInt32(spl[2]));
                    Graphics g = Graphics.FromImage(bmp);
                    Image loaded = Bitmap.FromFile(pt.filePath);
                    g.DrawImageUnscaledAndClipped(loaded, new Rectangle(0, 0, bmp.Size.Width, bmp.Size.Height));
                    txtSizeX.Text = bmp.Size.Width.ToString();
                    txtSizeY.Text = bmp.Size.Height.ToString();
                    bmp.Dispose();
                    g.Dispose();
                    bmp.Dispose();*/
                }
                else
                {
                    Image bmp = Bitmap.FromFile(pt.filePath);
                    txtSizeX.Text = bmp.Size.Width.ToString();
                    txtSizeY.Text = bmp.Size.Height.ToString();
                    bmp.Dispose();
                }
            }
        }

        private void cBoxMapObject_CheckedChanged(object sender, EventArgs e)
        {
            if (cBoxMapObject.Checked)
            {
                lastExtensionToSearch = extensionToSearch;
                extensionToSearch = ".png";
            }
            else
            {
                extensionToSearch = lastExtensionToSearch;
            }
            Reload();
        }
    }
}