using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Design;
using System.ComponentModel;
using System.Windows.Forms.Design;
using System.Windows.Forms;

namespace HitBox_Editor
{
  public class FileProperty : FileNameEditor
  {

    public FileProperty()
    {

    }


    private string _customFilter = "Character Files (*.chr)|*.chr";

    [DefaultValue("Character Files (*.chr)|*.chr")]
    public string CustomFilter
    {
      get { return _customFilter; }
      set { _customFilter = value; }
    }


    public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
    {
      // We'll show modal dialog (OpenFileDialog)
      return UITypeEditorEditStyle.Modal;
    }


    public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value)
    {
      using (OpenFileDialog dialog = new OpenFileDialog()){
        dialog.Filter = this.CustomFilter;

        if (dialog.ShowDialog() == DialogResult.OK)
          value = dialog.FileName;
      }
      return value;
    }


  }
}
