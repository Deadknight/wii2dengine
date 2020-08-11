using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Media;
using WMPLib;

namespace MapEditor
{
    public partial class SoundFileView : Form
    {
        public SoundFileView()
        {
            InitializeComponent();
        }

        SoundPlayer player = new SoundPlayer();
        WindowsMediaPlayer wmp = new WindowsMediaPlayer();
        SoundType currentType = SoundType.SOUND_TYPE_WAV;

        private void butBrowse_Click(object sender, EventArgs e)
        {
            DialogResult dr = folderBrowserDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                lstBoxSounds.Items.Clear();
                String path = folderBrowserDialog.SelectedPath;
                foreach (String file in Directory.GetFiles(path))
                {
                    String ext = Path.GetExtension(file);
                    if (ext == ".mp3" || ext == ".wav" || ext == ".mod")
                    {
                        SoundFile sf = new SoundFile(file);
                        lstBoxSounds.Items.Add(sf);
                    }
                }
            }
        }

        private void lstBoxSounds_DoubleClick(object sender, EventArgs e)
        {
            if (lstBoxSounds.SelectedItem != null)
            {
                SoundFile sf = (SoundFile)lstBoxSounds.SelectedItem;
                if (sf.type == SoundType.SOUND_TYPE_WAV)
                {
                    player.SoundLocation = sf.file;
                    player.Play();
                }
                else
                {
                    wmp.URL = sf.file;
                    wmp.controls.play();
                }
            }
        }

        private void butPlay_Click(object sender, EventArgs e)
        {
            if (lstBoxSounds.SelectedItem != null)
            {
                SoundFile sf = (SoundFile)lstBoxSounds.SelectedItem;
                if (sf.type == SoundType.SOUND_TYPE_WAV)
                {
                    player.SoundLocation = sf.file;
                    player.Play();
                }
                else
                {
                    wmp.URL = sf.file;
                    wmp.controls.play();
                }
            }
        }

        private void butStop_Click(object sender, EventArgs e)
        {
            if (currentType == SoundType.SOUND_TYPE_WAV)
            {
                player.Stop();
            }
            else
            {
                wmp.controls.stop();
            }
        }

        private void lstBoxSounds_MouseDown(object sender, MouseEventArgs e)
        {
            if (lstBoxSounds.SelectedItem != null)
            {
                if (e.Button == MouseButtons.Left)
                {
                    SoundFile sf = (SoundFile)lstBoxSounds.SelectedItem;

                    lstBoxSounds.DoDragDrop(sf, DragDropEffects.All);
                }
            }
        }
    }
}