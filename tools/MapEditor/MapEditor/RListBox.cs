using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    class RListBox : ListBox
    {
        public void RefreshAll()
        {
            base.RefreshItems();
        }
    }
}
