using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SunClock
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        double dy(double angle,double x,double y,double a,double b)
        {
            double R =Math.Sqrt( (x - a) * (x - a) + (y - b) * (y - b));
            double value= (x - a)+ (y - b) - R * Math.Cos(angle) - R * Math.Sin(angle);

            return value;
        }
        int sX = 0;
        int sY = 0;

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            double x=e.X;
            double y = e.Y;
            chart1.Series[1].Points.Clear();

            double a = pictureBox1.Width / 2.0;
            double b = pictureBox1.Height / 2.0;

            double angleStart = -Math.PI;
            double angleEnd = Math.PI;

            double eps = Math.PI / 60;

            if (x > a && y < b )
            {
                angleStart = (-134) * Math.PI / 180;
                angleEnd = (44) * Math.PI / 180 ;

                while (Math.Abs(angleStart - angleEnd) > eps)
                {
                    if (dy((angleStart + angleEnd) / 2, x, y, a, b) * dy((angleEnd) , x, y, a, b) < 0)
                    {
                        angleStart = (angleStart + angleEnd) / 2;
                    }
                    else
                    {
                        angleEnd = (angleStart + angleEnd) / 2;
                    }
                }

                angleEnd = (angleEnd + angleStart) / 2;

                chart1.Series[1].Points.AddXY(angleEnd * 180 / Math.PI, dy((angleEnd), x, y, a, b));
            }
            else
            {
                if (x < a && y > b)
                {

                    angleStart = (44) * Math.PI / 180;
                    angleEnd = (225) * Math.PI / 180;


                    while (Math.Abs(angleStart - angleEnd) > eps)
                    {
                        if (dy((angleStart + angleEnd) / 2, x, y, a, b) * dy((angleEnd) , x, y, a, b) < 0)
                        {
                            angleStart = (angleStart + angleEnd) / 2;
                        }
                        else
                        {
                            angleEnd = (angleStart + angleEnd) / 2;
                        }
                    }
                    angleEnd = (angleEnd + angleStart) / 2;

                    chart1.Series[1].Points.AddXY(angleEnd * 180 / Math.PI, dy((angleEnd), x, y, a, b));
                }
                else
                {
                    angleStart = (-134) * Math.PI / 180;
                    angleEnd = (44) * Math.PI / 180;

                    while (Math.Abs(angleStart - angleEnd) > eps)
                    {
                        if (dy((angleStart + angleEnd) / 2, x, y, a, b) * dy((angleEnd), x, y, a, b) < 0)
                        {
                            angleStart = (angleStart + angleEnd) / 2;
                        }
                        else
                        {
                            angleEnd = (angleStart + angleEnd) / 2;
                        }
                    }

                    double angleStart1 = angleStart;
                    double angleEnd1 = angleEnd;

                    angleStart = (44) * Math.PI / 180;
                    angleEnd = (225) * Math.PI / 180;

                    while (Math.Abs(angleStart - angleEnd) > eps)
                    {
                        if (dy((angleStart + angleEnd) / 2, x, y, a, b) * dy((angleEnd) , x, y, a, b) < 0)
                        {
                            angleStart = (angleStart + angleEnd) / 2;
                        }
                        else
                        {
                            angleEnd = (angleStart + angleEnd) / 2;
                        }
                    }
                    angleEnd = (angleEnd + angleStart) / 2;
                    angleEnd1 = (angleEnd1 + angleStart1) / 2;

                    chart1.Series[1].Points.AddXY(angleEnd * 180 / Math.PI, dy((angleEnd), x, y, a, b));
                    chart1.Series[1].Points.AddXY(angleEnd1 * 180 / Math.PI, dy((angleEnd1), x, y, a, b));

                    double R = Math.Sqrt((x - a) * (x - a) + (y - b) * (y - b));
                    if ((Math.Abs(R * Math.Cos(angleEnd) - (x-a)) + Math.Abs(R * Math.Sin(angleEnd) - (y-b)) )> 
                        (Math.Abs(R * Math.Cos(angleEnd1) - (x-a))+ Math.Abs(R * Math.Cos(angleEnd1) - (y-b))))
                    {
                        angleEnd = angleEnd1;
                    }
                }
               
            }

            

            chart1.Series[0].Points.Clear();
           
            for (double i = -2 * Math.PI; i<= 2*Math.PI; i+= eps)
            {
                double value = dy(i, x, y, a, b);
                chart1.Series[0].Points.AddXY((i)*180/Math.PI, value);                
            }

            

            sX =(int) x;
            sY = (int)y;

            result=(angleEnd) * 180 / (Math.PI) + 90;
            if (result < 0) result = 315+(45+result);
         
            pictureBox1.Invalidate();
        }
        double result = 0;
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            
            label1.Text = (result).ToString() +" Время:" + (result * 12 / 360).ToString();
            var g=e.Graphics;
            g.Clear(Color.Azure);
            int r = pictureBox1.Width > pictureBox1.Height ? pictureBox1.Height : pictureBox1.Width;
            g.DrawEllipse(Pens.Black, new Rectangle((pictureBox1.Width-r)/2, (pictureBox1.Height - r)/2, r, r));

            g.DrawLine(Pens.Black, pictureBox1.Width/2, pictureBox1.Height/2 , sX, sY);
            

        }
    }
}
