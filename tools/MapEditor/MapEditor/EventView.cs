using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class EventView : Form
    {
        public EventView()
        {
            InitializeComponent();

            foreach (MapEventType et in Enum.GetValues(typeof(MapEventType)))
            {
                EventFile ef = new EventFile();
                ef.type = et;
                lstBoxEvents.Items.Add(ef);
            }
        }

        private void lstBoxEvents_MouseDown(object sender, MouseEventArgs e)
        {
            if (lstBoxEvents.SelectedItem != null)
            {
                if (e.Button == MouseButtons.Left)
                {
                    EventFile sf = (EventFile)lstBoxEvents.SelectedItem;

                    lstBoxEvents.DoDragDrop(sf, DragDropEffects.All);
                }
            }
        }       
    }
}