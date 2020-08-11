using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class StaticObjectBoundaryForm : Form
    {
        Main pFrom;
        Vector v;
        bool saved;

        public StaticObjectBoundaryForm(Main pFrom)
        {
            InitializeComponent();

            this.pFrom = pFrom;
            v = new Vector(0, 0);
            saved = false;
        }

        public void AddVector(Vector v)
        {
            saved = false;
            listBoxPoints.Items.Add(v);
        }

        public ListBox GetVectorList() { return listBoxPoints; }

        public void SetPolygon(Polygon p)
        {
            listBoxPoints.Items.Clear();
            foreach (Vector v in p.Points)
            {
                listBoxPoints.Items.Add(v);
            }
        }

        public Vector GetSelectedVector()
        {
            return v;
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saved = false;
            if (listBoxPoints.SelectedItem != null)
                listBoxPoints.Items.Remove(listBoxPoints.SelectedItem);
        }
        
        private void listBoxPoints_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(listBoxPoints.SelectedItem != null)
                v = (Vector)listBoxPoints.SelectedItem;
        }

        private void butSave_Click(object sender, EventArgs e)
        {
            StaticObject so = pFrom.GetSelectedStaticObject();
            if (so == null)
                return;

            saved = true;

            if (so.HasBoundary())
            {
                so.ClearBoundary();
                so.CreateBoundary();
            }
            else
                so.CreateBoundary();

            foreach (Vector v in listBoxPoints.Items)
            {
                so.AddBoundary(v);
            }
        }

        public bool IsSaved()
        {
            return saved;
        }
    }
}