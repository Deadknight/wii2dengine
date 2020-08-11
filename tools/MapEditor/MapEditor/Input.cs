using System;
using System.Collections.Generic;
using System.Text;
using AgateLib;
using System.Drawing;
using System.Windows.Forms;
using AgateLib.InputLib;

namespace MapEditor
{
    partial class Main
    {
        //InputState<KeyCode> keyStates = new InputState<KeyCode>();
        List<KeyCode> pressedKeys = new List<KeyCode>();
        //Keyboard Input
        void Keyboard_KeyUp(InputEventArgs e)
        {
            if (pressedKeys.Contains(e.KeyCode))
                pressedKeys.Remove(e.KeyCode);
        }

        void Keyboard_KeyDown(InputEventArgs e)
        {
            if (!pressedKeys.Contains(e.KeyCode))
                pressedKeys.Add(e.KeyCode);
        }

        private void HandleKeys()
        {
            if (pressedKeys.Count == 0)
                return;

            /*foreach (KeyCode kc in pressedKeys)
            {
                if (kc == KeyCode.Right)
                {
                    if(toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if(so != null)
                        {
                            Int32 x = so.GetX();
                            x++;
                            so.SetPosition(x, so.GetY());
                        }
                    }
                    else if(toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if(so != null)
                        {
                            Vector v = so.GetPosition();
                            v.X++;
                            so.SetPosition(v);
                        }
                    }
                    else
                        currentX++;
                }
                else if (kc == KeyCode.Left)
                {
                    if (toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if (so != null)
                        {
                            Int32 x = so.GetX();
                            x--;
                            if (x < 0)
                                x = 0;
                            so.SetPosition(x, so.GetY());
                        }
                    }
                    else if (toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if (so != null)
                        {
                            Vector v = so.GetPosition();
                            v.X--;
                            if (v.X < 0)
                                v.X = 0;
                            so.SetPosition(v);
                        }
                    }
                    else
                    {
                        currentX--;
                        if (sizeX > currentX)
                            currentX = sizeX;
                    }
                }
                else if (kc == KeyCode.Up)
                {
                    if (toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if (so != null)
                        {
                            Int32 y = so.GetY();
                            y--;
                            if (y < 0)
                                y = 0;
                            so.SetPosition(so.GetX(), y);
                        }
                    }
                    else if (toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if (so != null)
                        {
                            Vector v = so.GetPosition();
                            v.Y--;
                            if (v.Y < 0)
                                v.Y = 0;
                            so.SetPosition(v);
                        }
                    }
                    else
                    {
                        currentY--;
                        if (sizeY > currentY)
                            currentY = sizeY;
                    }
                }
                else if (kc == KeyCode.Down)
                {
                    if (toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if (so != null)
                        {
                            Int32 y = so.GetY();
                            y++;
                            so.SetPosition(so.GetX(), y);
                        }
                    }
                    else if (toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if (so != null)
                        {
                            Vector v = so.GetPosition();
                            v.Y++;
                            so.SetPosition(v);
                        }
                    }
                    else
                        currentY++;
                }
            } */         
        }

        //Mouse input
        void Mouse_MouseDoubleClick(InputEventArgs e)
        {
            //throw new Exception("The method or operation is not implemented.");
        }

        void Mouse_MouseUp(InputEventArgs e)
        {
            //throw new Exception("The method or operation is not implemented.");
        }

        void Mouse_MouseDown(InputEventArgs e)
        {
            if (GetBoundaryDrawChecked())
            {
                if (e.MouseButtons.ToString() == "Primary")
                {
                    lstBound.Add(ConvertToVirtualCoordinates(e.MousePosition.X, e.MousePosition.Y));
                }
            }
            else if (GetObjectBoundaryDrawChecked())
            {
                if (e.MouseButtons.ToString() == "Primary")
                {
                    if (listBoxSO.SelectedItem != null)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        /*if (so.HasBoundary())
                        {
                            so.AddBoundary(ConvertToVirtualCoordinates(e.MousePosition.X, e.MousePosition.Y));
                        }
                        else
                        {
                            so.CreateBoundary();
                            so.AddBoundary(ConvertToVirtualCoordinates(e.MousePosition.X, e.MousePosition.Y));
                        }*/
                        formStaticBoundary.AddVector(ConvertToVirtualCoordinates(e.MousePosition.X, e.MousePosition.Y));
                    }
                }
            }
            else if (GetPhysicObjectDrawChecked())
            {
                if (e.MouseButtons.ToString() == "Primary")
                {
                    if (listBoxPO.SelectedItem != null)
                    {

                    }
                }
            }
        }

        void Mouse_MouseMove(InputEventArgs e)
        {
            //throw new Exception("The method or operation is not implemented.");
        }

        Int32 mouseButtonPressed = 0;
        Point down;
        Point first;
        Point current;
        Point downR;
        Point firstR;
        Point currentR;
        bool mousePosUpdate = false;
        bool mouseRotate = false;
        bool mouseSize = false;
        bool mouseMove = false;
        public bool HasFlag(Int32 content, Object flag)
        {
            if ((content & (Int32)flag) > 0)
                return true;
            return false;
        }

        private void pictBoxRender_MouseDown(object sender, MouseEventArgs e)
        {
            mouseButtonPressed |= (Int32)e.Button;
            if (HasFlag(mouseButtonPressed, MouseButtons.Left))
            {
                //New Rot
                if(!toolStripButMoveSurface.Checked && !toolStripButMoveStatic.Checked && listBoxPO.SelectedItem == null)
                    txtRot.Text = "0";
                down = e.Location;
                first = e.Location;
                current = e.Location;
                mousePosUpdate = true;
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.Right))
            {
                downR = e.Location;
                firstR = e.Location;
                currentR = e.Location;
                mouseRotate = true;
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.XButton2))
            {
                downR = e.Location;
                firstR = e.Location;
                currentR = e.Location;
                mouseSize = true;
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.XButton1))
            {
                downR = e.Location;
                firstR = e.Location;
                currentR = e.Location;
                mouseMove = true;
            }
        }

        private void pictBoxRender_MouseMove(object sender, MouseEventArgs e)
        {
            Int32 xO = 0;
            Int32 yO = 0;
            if(CheckInView(e.Location.X, e.Location.Y, out xO, out yO))
            {
                toolStripStatusLabX.Text = xO.ToString();
                toolStripStatusLabY.Text = yO.ToString(); ;
            }
            if (HasFlag(mouseButtonPressed, MouseButtons.Left))
            {
                if (mousePosUpdate)
                {
                    current = e.Location;
                    Int32 newX = e.Location.X - down.X;
                    Int32 newY = e.Location.Y - down.Y;
                    if (toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if (so != null)
                        {
                            Int32 x = so.GetX();
                            Int32 y = so.GetY();

                            so.SetPosition(x + newX, y + newY);
                            txtX.Text = x.ToString();
                            txtY.Text = y.ToString();
                        }
                    }
                    else if (toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if (so != null)
                        {
                            Vector v = so.GetPosition();

                            v.X += newX;
                            v.Y += newY;

                            so.SetPosition(v);
                            txtX.Text = v.X.ToString();
                            txtY.Text = v.Y.ToString();
                        }
                    }
                    else if (toolStripButDrawStandalonePhysicObject.Checked)
                    {
                        PhysicObject po = (PhysicObject)listBoxPO.SelectedItem;
                        if (po != null)
                        {
                            po.rect.X += newX;
                            po.rect.Y += newY;
                            txtSX.Text = po.rect.X.ToString();
                            txtSY.Text = po.rect.Y.ToString();
                        }
                        else
                        {
                            txtX.Text = first.X.ToString();
                            txtY.Text = first.Y.ToString();
                            txtSX.Text = Math.Abs((current.X - first.X)).ToString();
                            txtSY.Text = Math.Abs((current.Y - first.Y)).ToString();
                        }
                    }
                    else
                    {
                        currentX -= newX;
                        currentY -= newY;
                        txtVX.Text = currentX.ToString();
                        txtVY.Text = currentY.ToString();
                    }

                    down = new Point(down.X + newX, down.Y + newY);
                }
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.Right))
            {
                if (mouseRotate)
                {
                    Int32 newX = e.Location.X - downR.X;
                    Int32 newY = e.Location.Y - downR.Y;
                    currentR = e.Location;
                    if (toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if (so != null)
                        {
                            Int32 val = Convert.ToInt32(txtRot.Text) + currentR.Y - downR.Y;
                            if (val < 0)
                                val += 360;
                            if (val > 360)
                                val -= 360;
                            so.GetSurface().RotationAngleDegrees = val;
                            txtRot.Text = val.ToString();
                        }
                    }
                    else if (toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if (so != null)
                        {
                            Int32 val = Convert.ToInt32(txtRot.Text) + currentR.Y - downR.Y;
                            if (val < 0)
                                val += 360;
                            if (val > 360)
                                val -= 360;
                            so.GetSprite().RotationAngleDegrees = val;
                            txtRot.Text = val.ToString();
                        }
                    }
                    else if (toolStripButDrawStandalonePhysicObject.Checked)
                    {
                        PhysicObject po = (PhysicObject)listBoxPO.SelectedItem;
                        if (po != null)
                        {
                            Int32 val = Convert.ToInt32(txtRot.Text) + currentR.Y - downR.Y;
                            if (val < 0)
                                val += 360;
                            if (val > 360)
                                val -= 360;
                            po.rot = val;
                            txtRot.Text = val.ToString();
                        }
                        else
                        {
                            Int32 val = Convert.ToInt32(txtRot.Text) + currentR.Y - downR.Y;
                            if (val < 0)
                                val += 360;
                            if (val > 360)
                                val -= 360;
                            txtRot.Text = val.ToString();
                        }
                    }

                    downR = new Point(downR.X + newX, downR.Y + newY);
                }
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.XButton2))
            {
                if (mouseSize)
                {
                    Int32 newX = e.Location.X - downR.X;
                    Int32 newY = e.Location.Y - downR.Y;
                    currentR = e.Location;
                    if (toolStripButMoveSurface.Checked)
                    {
                        SurfaceObject so = (SurfaceObject)listBoxSurface.SelectedItem;
                        if (so != null)
                        {
                            so.GetSurface().DisplaySize = new AgateLib.Geometry.Size(so.GetSurface().DisplayWidth + (currentR.X - downR.X), so.GetSurface().DisplayHeight + (currentR.Y - downR.Y));

                            txtSX.Text = so.GetSurface().DisplayWidth.ToString();
                            txtSY.Text = so.GetSurface().DisplayHeight.ToString();
                        }
                    }
                    else if (toolStripButMoveStatic.Checked)
                    {
                        StaticObject so = (StaticObject)listBoxSO.SelectedItem;
                        if (so != null)
                        {
                            so.GetSprite().DisplaySize = new AgateLib.Geometry.Size(so.GetSprite().DisplayWidth + (currentR.X - downR.X), so.GetSprite().DisplayHeight + (currentR.Y - downR.Y));

                            txtSX.Text = so.GetSprite().DisplayWidth.ToString();
                            txtSY.Text = so.GetSprite().DisplayHeight.ToString();
                        }
                    }
                    else if (toolStripButDrawStandalonePhysicObject.Checked)
                    {
                        PhysicObject po = (PhysicObject)listBoxPO.SelectedItem;
                        if (po != null)
                        {
                            po.rect.Width += currentR.X - downR.X;
                            po.rect.Height += currentR.Y - downR.Y;

                            txtSX.Text = po.rect.Width.ToString();
                            txtSY.Text = po.rect.Height.ToString();
                        }
                        else
                        {
                            current.X += currentR.X - downR.X;
                            current.Y += currentR.Y - downR.Y;

                            txtSX.Text = (current.X - first.X).ToString();
                            txtSY.Text = (current.Y - first.Y).ToString();
                        }
                    }
                    downR = new Point(downR.X + newX, downR.Y + newY);
                }
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.XButton1))
            {
                if (mouseMove)
                {
                    Int32 newX = e.Location.X - downR.X;
                    Int32 newY = e.Location.Y - downR.Y;
                    currentR = e.Location;

                    first.X += newX;
                    first.Y += newY;
                    current.X = first.X + Convert.ToInt32(txtSX.Text);
                    current.Y = first.Y + Convert.ToInt32(txtSY.Text);

                    txtX.Text = (Convert.ToInt32(txtX.Text) + newX).ToString();
                    txtY.Text = (Convert.ToInt32(txtY.Text) + newY).ToString();

                    downR = new Point(downR.X + newX, downR.Y + newY);
                }
            }
        }

        private void pictBoxRender_MouseUp(object sender, MouseEventArgs e)
        {
            if (HasFlag(mouseButtonPressed, MouseButtons.Left))
            {
                current = e.Location;
                mousePosUpdate = false;
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.Right))
            {
                currentR = e.Location;
                mouseRotate = false;
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.XButton2))
            {
                currentR = e.Location;
                mouseSize = false;
            }
            else if (HasFlag(mouseButtonPressed, MouseButtons.XButton1))
            {
                currentR = e.Location;
                mouseMove = false;
            }
            mouseButtonPressed &= ~(Int32)e.Button;
        }
    }
}
