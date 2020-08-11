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

namespace UnitCreator
{
    public enum LOOK_POSITION
    {
        LOOK_POSITION_N = 0x1,
        LOOK_POSITION_NE = 0x2,
        LOOK_POSITION_E = 0x4,
        LOOK_POSITION_SE = 0x8,
        LOOK_POSITION_S = 0x10,
        LOOK_POSITION_SW = 0x20,
        LOOK_POSITION_W = 0x40,
        LOOK_POSITION_NW = 0x80
    };

    public enum MOVEMENT_FLAG
    {
        MOVEMENT_FLAG_IDLE = 0x100,
        MOVEMENT_FLAG_RIGHT = 0x200,
        MOVEMENT_FLAG_LEFT = 0x400,
        MOVEMENT_FLAG_UP = 0x800,
        MOVEMENT_FLAG_DOWN = 0x800,
        MOVEMENT_FLAG_JUMP = 0x1000,
        MOVEMENT_FLAG_CROUCH = 0x2000,
        MOVEMENT_FLAG_WALK = 0x4000,
        MOVEMENT_FLAG_RUN = 0x8000,
        MOVEMENT_FLAG_SPECIAL = 0x10000
    };

    enum STATE
    {
        STATE_NONE = 0x20000,
        STATE_JUMP_START = 0x40000,
        STATE_FALLING = 0x80000,
        STATE_FALL_LAND = 0x100000,
        STATE_SWIMMING = 0x200000,
        STATE_CLIMBING = 0x400000,
        STATE_FIREING = 0x800000,
        STATE_RELOADING = 0x1000000,
        STATE_DIED = 0x2000000
    };

    public enum ENDIAN
    {
        LITTLE_ENDIAN, //Pentium
        BIG_ENDIAN, //Wii
    }

    public partial class Main : Form
    {
        private ENDIAN endianType;

        public Main()
        {
            InitializeComponent();

            endianType = ENDIAN.BIG_ENDIAN;
            
            Array values = Enum.GetValues(typeof(LOOK_POSITION));
            Int32 count = 0;
            foreach (String name in Enum.GetNames(typeof(LOOK_POSITION)))
            {
                EnumObject eo = new EnumObject();
                eo.name = name;
                eo.value = Convert.ToInt32(values.GetValue(count));
                lstBoxLookDirection.Items.Add(eo);
                count++;
            }
            values = Enum.GetValues(typeof(MOVEMENT_FLAG));
            count = 0;
            foreach (String name in Enum.GetNames(typeof(MOVEMENT_FLAG)))
            {
                EnumObject eo = new EnumObject();
                eo.name = name;
                eo.value = Convert.ToInt32(values.GetValue(count));
                lstBoxMF.Items.Add(eo);
                count++;
            }
            values = Enum.GetValues(typeof(STATE));
            count = 0;
            foreach (String name in Enum.GetNames(typeof(STATE)))
            {
                EnumObject eo = new EnumObject();
                eo.name = name;
                eo.value = Convert.ToInt32(values.GetValue(count));
                lstBoxMS.Items.Add(eo);
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
            txtPhoto.Text = "";
            lstBoxImage.Items.Clear();
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
                lstBoxLookDirection.SelectedItems.Clear();
                for (Int32 i = 0; i < lstBoxLookDirection.Items.Count; i++)
                {
                    EnumObject eo = (EnumObject)lstBoxLookDirection.Items[i];
                    if (HasFlag(eo.value, ip.flags))
                        lstBoxLookDirection.SetSelected(i, true);
                    else
                        lstBoxLookDirection.SetSelected(i, false);
                }
                lstBoxMF.SelectedItems.Clear();
                for (Int32 i = 0; i < lstBoxMF.Items.Count; i++)
                {
                    EnumObject eo = (EnumObject)lstBoxMF.Items[i];
                    if (HasFlag(eo.value, ip.flags))
                        lstBoxMF.SetSelected(i, true);
                    else
                        lstBoxMF.SetSelected(i, false);
                }
                lstBoxMS.SelectedItems.Clear();
                for (Int32 i = 0; i < lstBoxMS.Items.Count; i++)
                {
                    EnumObject eo = (EnumObject)lstBoxMS.Items[i];
                    if (HasFlag(eo.value, ip.flags))
                        lstBoxMS.SetSelected(i, true);
                    else
                        lstBoxMS.SetSelected(i, false);
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
                foreach (EnumObject eo in lstBoxLookDirection.SelectedItems)
                    ip.flags |= eo.value;
                foreach (EnumObject eo in lstBoxMF.SelectedItems)
                    ip.flags |= eo.value;
                foreach (EnumObject eo in lstBoxMS.SelectedItems)
                    ip.flags |= eo.value;
                ip.flipX = Convert.ToByte(cBoxFlipX.Checked);
                ip.flipY = Convert.ToByte(cBoxFlipY.Checked);
            }
        }

        private void butLoadUnit_Click(object sender, EventArgs e)
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
                UInt32 photoLength = br.ReadUInt32();
                if (photoLength > 0)
                {
                    txtPhoto.Text = Encoding.ASCII.GetString(br.ReadBytes((Int32)photoLength));
                    //txtPhoto.Text = new String(br.ReadChars((Int32)photoLength));
                }
                cBoxDual.Checked = Convert.ToBoolean(br.ReadUInt32());
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

        private void butSaveUnit_Click(object sender, EventArgs e)
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
                bw.Write((UInt32)txtPhoto.Text.Length);
                bw.Write(txtPhoto.Text.ToCharArray());
                bw.Write(Convert.ToUInt32(cBoxDual.Checked));
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

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (lstBoxImage.SelectedItem != null)
            {
                lstBoxImage.Items.Remove(lstBoxImage.SelectedItem);
            }
        }
    }
}