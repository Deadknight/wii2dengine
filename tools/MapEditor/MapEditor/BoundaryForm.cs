using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class BoundaryForm : Form
    {
        Main pFrom;

        public BoundaryForm(Main pForm)
        {
            InitializeComponent();
            this.pFrom = pForm;
        }

        public ListBox GetBoundaryList() { return listBoxBoundary; }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(listBoxBoundary.SelectedItem != null)
                listBoxBoundary.Items.Remove(listBoxBoundary.SelectedItem);
        }

        private void butSave_Click(object sender, EventArgs e)
        {
            Polygon p = new Polygon();
            foreach (Vector v in pFrom.lstBound)
            {
                p.Points.Add(v);
            }
            listBoxBoundary.Items.Add(p);
        }

        private void butClear_Click(object sender, EventArgs e)
        {
            pFrom.lstBound.Clear();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            Hide();
        }

        private void butNew_Click(object sender, EventArgs e)
        {
            pFrom.lstBound.Clear();
        }

        private void listBoxBoundary_DoubleClick(object sender, EventArgs e)
        {
            if (listBoxBoundary.SelectedItem != null)
            {
                Polygon p = (Polygon)listBoxBoundary.SelectedItem;
                pFrom.lstBound.Clear();
                foreach (Vector v in p.Points)
                {
                    pFrom.lstBound.Add(v);
                }
            }
        }
    }
}