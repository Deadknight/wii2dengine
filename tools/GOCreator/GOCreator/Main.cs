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

namespace GOCreator
{
    public partial class Main : Form
    {
        enum GAMEOBJECT_STATE
        {
            GO_STATE_CLOSED = 0x1,
            GO_STATE_OPENED = 0x2,
            GO_STATE_DESTROYED = 0x8,
            GO_STATE_MASK = 0xFF
        };

        enum GAMEOBJECT_FLAG
        {
            GO_FLAG_CAN_BE_OPENED = 0x100,
            GO_FLAG_LOCKED = 0x200
        };

        public Main()
        {
            InitializeComponent();

            Array values = Enum.GetValues(typeof(GAMEOBJECT_STATE));
            Int32 count = 0;
            foreach (String name in Enum.GetNames(typeof(GAMEOBJECT_STATE)))
            {
                EnumObject eo = new EnumObject();
                eo.name = name;
                eo.value = Convert.ToInt32(values.GetValue(count));
                lstBoxGS.Items.Add(eo);
                count++;
            }
            values = Enum.GetValues(typeof(GAMEOBJECT_FLAG));
            count = 0;
            foreach (String name in Enum.GetNames(typeof(GAMEOBJECT_FLAG)))
            {
                EnumObject eo = new EnumObject();
                eo.name = name;
                eo.value = Convert.ToInt32(values.GetValue(count));
                lstBoxGF.Items.Add(eo);
                count++;
            }
        }

        public bool HasFlag(Int32 content, Object flag)
        {
            if ((content & (Int32)flag) > 0)
                return true;
            return false;
        }

        private void butNew_Click(object sender, EventArgs e)
        {
            txtName.Text = "";
            txtDir.Text = "";
            cBoxFlipX.Checked = false;
            cBoxFlipY.Checked = false;
        }

        private void butAdd_Click(object sender, EventArgs e)
        {
            DialogResult dr = openFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ImagePath img = new ImagePath();
                img.name = Path.GetFileNameWithoutExtension(openFileDialog.FileName);
                img.fullPath = openFileDialog.FileName;
                img.flags = 0;
                img.flipX = 0;
                img.flipY = 0;
                lstBoxImage.Items.Add(img);
            }            
        }

        private void lstBoxImage_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstBoxImage.SelectedItem != null)
            {
                ImagePath ip = (ImagePath)lstBoxImage.SelectedItem;
                lstBoxGS.SelectedItems.Clear();
                for (Int32 i = 0; i < lstBoxGS.Items.Count; i++)
                {
                    EnumObject eo = (EnumObject)lstBoxGF.Items[i];
                    if (HasFlag(eo.value, ip.flags))
                        lstBoxGS.SetSelected(i, true);
                    else
                        lstBoxGS.SetSelected(i, false);
                }
                lstBoxGF.SelectedItems.Clear();
                for (Int32 i = 0; i < lstBoxGF.Items.Count; i++)
                {
                    EnumObject eo = (EnumObject)lstBoxGF.Items[i];
                    if (HasFlag(eo.value, ip.flags))
                        lstBoxGF.SetSelected(i, true);
                    else
                        lstBoxGF.SetSelected(i, false);
                }
                if (ip.flipX == 1)
                    cBoxFlipX.Checked = true;
                else
                    cBoxFlipX.Checked = false;

                if (ip.flipY == 1)
                    cBoxFlipY.Checked = true;
                else
                    cBoxFlipY.Checked = false;            
            }
        }

        private void butSave_Click(object sender, EventArgs e)
        {
            if (lstBoxImage.SelectedItem != null)
            {
                ImagePath ip = (ImagePath)lstBoxImage.SelectedItem;
                ip.flags = 0;
                foreach (EnumObject eo in lstBoxGS.SelectedItems)
                    ip.flags |= eo.value;
                foreach (EnumObject eo in lstBoxGF.SelectedItems)
                    ip.flags |= eo.value;
                ip.flipX = Convert.ToByte(cBoxFlipX.Checked);
                ip.flipY = Convert.ToByte(cBoxFlipY.Checked);
            }
        }

        private void butLoadGO_Click(object sender, EventArgs e)
        {
            DialogResult dr = openFileDialogLoad.ShowDialog();
            if (dr == DialogResult.OK)
            {
                FileStream fs = new FileStream(openFileDialogLoad.FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
                EndianBinaryReader br = new EndianBinaryReader(BigEndianBitConverter.Big, fs, Encoding.ASCII);
                //BinaryReader br = new BinaryReader(fs, Encoding.ASCII);
                UInt32 uniqueNameLength = br.ReadUInt32();
                txtName.Text = Encoding.ASCII.GetString(br.ReadBytes((Int32)uniqueNameLength));
                //txtName.Text = new String(br.ReadChars((Int32)uniqueNameLength));
                UInt32 virtualDirLength = br.ReadUInt32();
                if (virtualDirLength > 0)
                {
                    txtDir.Text = Encoding.ASCII.GetString(br.ReadBytes((Int32)virtualDirLength));
                    //txtDir.Text = new String(br.ReadChars((Int32)virtualDirLength));
                }
                Int32 fileArrayLength = (Int32)br.ReadUInt32();
                for (Int32 i = 0; i < fileArrayLength; i++)
                {
                    ImagePath ip = new ImagePath();
                    ip.flags = (Int32)br.ReadUInt32();
                    ip.flipX = br.ReadByte();
                    ip.flipY = br.ReadByte();
                    Int32 fileNameShortLength = (Int32)br.ReadUInt32();
                    ip.name = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameShortLength));
                    //ip.name = new String(br.ReadChars(fileNameShortLength));
                    Int32 fileNameFullLength = (Int32)br.ReadUInt32();
                    ip.fullPath = Encoding.ASCII.GetString(br.ReadBytes((Int32)fileNameFullLength));
                    //ip.fullPath = new String(br.ReadChars(fileNameFullLength));
                    lstBoxImage.Items.Add(ip);
                }

                br.Close();
                fs.Close();
            }
        }

        private void butSaveGO_Click(object sender, EventArgs e)
        {
            DialogResult dr = saveFileDialogSave.ShowDialog();
            if (dr == DialogResult.OK)
            {
                FileStream fs = new FileStream(saveFileDialogSave.FileName, FileMode.Create, FileAccess.Write, FileShare.Write);
                EndianBinaryWriter bw = new EndianBinaryWriter(BigEndianBitConverter.Big, fs, Encoding.ASCII);
                //BinaryWriter bw = new BinaryWriter(fs, Encoding.ASCII);

                bw.Write((UInt32)txtName.Text.Length);
                bw.Write(txtName.Text.ToCharArray());
                bw.Write((UInt32)txtDir.Text.Length);
                bw.Write(txtDir.Text.ToCharArray());
                bw.Write((UInt32)lstBoxImage.Items.Count);
                foreach (ImagePath ip in lstBoxImage.Items)
                {
                    bw.Write((UInt32)ip.flags);
                    bw.Write(ip.flipX);
                    bw.Write(ip.flipY);
                    bw.Write((UInt32)ip.name.Length);
                    bw.Write(ip.name.ToCharArray());
                    bw.Write((UInt32)ip.fullPath.Length);
                    bw.Write(ip.fullPath.ToCharArray());
                }

                bw.Flush();
                fs.Flush();
                bw.Close();
                fs.Close();
            }
        }
    }
}