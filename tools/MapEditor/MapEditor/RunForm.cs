using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using AgateLib;

namespace MapEditor
{
    public partial class RunForm : Form
    {
        public RunForm()
        {
            InitializeComponent();
            butRun_Click(null, null);
        }

        private void butRun_Click(object sender, EventArgs e)
        {
            Main form = new Main();

            using (AgateSetup displaySetup = new AgateSetup("asd"))
            {
                displaySetup.AskUser = false;
                //displaySetup.Initialize(true, false, false);
                displaySetup.InitializeDisplay();
                if (displaySetup.WasCanceled)
                    return;

                form.Show();

                while (form.Visible)
                {
                    form.UpdateDisplay();

                    //System.Threading.Thread.Sleep(10);
                    Core.KeepAlive();
                }
            }
        }
    }
}