#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                              QCP::iSelectLegend | QCP::iSelectPlottables);

    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect( ui->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel(QWheelEvent*)));
    connect( ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect( ui->plot, SIGNAL(mouseRelease(QMouseEvent *)), this, SLOT(mouseReleaseEvent(QMouseEvent *)));

    ui->plot->addGraph();
    ui->plot->graph(0)->setName("Ряд");
    ui->plot->graph(0)->setPen(QColor(0, 0, 128));

    ui->plot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle );

    ui->plot->replot();

    ui->plot->addGraph();
    ui->plot->graph(1)->setName("Результат");
    ui->plot->graph(1)->setPen(QColor(255, 0, 0));
    ui->plot->yAxis->setRange(-100,100);
    ui->plot->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Redraw()
{
    ui->plot->clearGraphs();

    ui->plot->addGraph();
    ui->plot->graph(0)->setName("Ряд");
    ui->plot->graph(0)->setPen(QColor(0, 0, 128));
    ui->plot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle );

    ui->plot->addGraph();
    ui->plot->graph(1)->setName("Результат");
    ui->plot->graph(1)->setPen(QColor(255, 0, 0));


    if(xPlot.size()>0&&yPlot.size()>0)
    {
        ui->plot->graph(0)->setData(xPlot,yPlot, false);

//        double min = *std::min_element(xPlot.constBegin(), xPlot.constEnd())-10;
//        double max = *std::max_element(xPlot.constBegin(), xPlot.constEnd())+10;

//        ui->plot->xAxis->setRange(min,max);

//        min = *std::min_element(yPlot.constBegin(), yPlot.constEnd())-1;
//        max = *std::max_element(yPlot.constBegin(), yPlot.constEnd())+1;

//        ui->plot->yAxis->setRange(min,max);
    }

    if(xResPlot.size()>0&&yResPlot.size()>0)
    {
        ui->plot->graph(1)->setData(xResPlot,yResPlot, false);
    }


    ui->plot->replot();
}

double *MainWindow::SolveSLAU(double **matrix, int rowCount, int columnCount)
{
    if (columnCount != rowCount + 1)
    {
        return NULL;
    }
    double ** matrixCopy = new double*[rowCount];
    double* result = new double[rowCount];


    for (int i = 0; i < rowCount; i++)
    {
        matrixCopy[i] = new double[columnCount];

        for (int j = 0; j < columnCount; j++)
        {
            matrixCopy[i][j] = matrix[i][j];
        }

        result[i]=0;
    }

    double reverseBuffer = 0;
    double determinant = 1;
    for (int i = 0, j = 0; i < (rowCount - 1) && j < (columnCount - 1); i++, j++)
    {
        for (int k = i + 1; k < rowCount; k++)
        {
            if (0 == matrixCopy[i][j])
            {
                for (int l = j; l < columnCount; l++)
                {
                    reverseBuffer = matrixCopy[i][l];
                    matrixCopy[i][l] = matrixCopy[k][l];
                    matrixCopy[k][l] = reverseBuffer;
                }
                determinant *= -1;
            }
            else
            {
                break;
            }
        }

        for (int k = i+1; k < rowCount; k++)
        {
            if (0==matrixCopy[i][j])
            {
                for (i = 0; i < rowCount; i++)
                {
                    delete matrixCopy[i];
                }

                delete matrixCopy;

                return NULL;
            }

            reverseBuffer = -matrixCopy[k][j] / matrixCopy[i][j];

            for (int l = j; l < columnCount; l++)
            {
                matrixCopy[k][l] += matrixCopy[i][l] * reverseBuffer;
            }


        }

    }

    for (int i = 0; i < rowCount; i++)
    {
        determinant *= (double)matrixCopy[i][i];
    }

    if (0 == determinant)
    {
        for (int i = 0; i < rowCount; i++)
        {
            delete matrixCopy[i];
        }

        delete matrixCopy;

        return NULL;
    }



    for (int i = rowCount - 1; i >= 0; i--)
    {
        result[i] = matrixCopy[i][columnCount - 1] / matrixCopy[i][i];
        if (i != (rowCount - 1))
        {
            for (int j = i + 1; j <= (columnCount - 2); j++)
            {
                result[i] -= matrixCopy[i][j] * result[j] / matrixCopy[i][i];

            }
        }


    }

    for (int i = 0; i < rowCount; i++)
    {
        delete matrixCopy[i];
    }

    delete matrixCopy;

    return result;
}



void MainWindow::mousePress(QMouseEvent* event)
{
    if(event->button()== Qt::MouseButton::RightButton)
    {
        x=event->x();
        y=event->y();

        return;
    }

    QCustomPlot* plot=qobject_cast<QCustomPlot*>(this->sender());

    if (plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        plot->axisRect()->setRangeDrag(plot->xAxis->orientation());
    else if (plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        plot->axisRect()->setRangeDrag(plot->yAxis->orientation());
    else
        plot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);

    ui->plot->replot();
}

void MainWindow::mouseWheel(QWheelEvent*)
{
    QCustomPlot* plot=qobject_cast<QCustomPlot*>(this->sender());

    if (plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        plot->axisRect()->setRangeZoom(plot->xAxis->orientation());
    else if (plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        plot->axisRect()->setRangeZoom(plot->yAxis->orientation());
    else
        plot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);

    ui->plot->replot();
}

void MainWindow::mouseMove(QMouseEvent*)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button()== Qt::MouseButton::RightButton)
    {
        x=ui->plot->xAxis->pixelToCoord(x);
        y=ui->plot->yAxis->pixelToCoord(y);

        xPlot.push_back(x);
        yPlot.push_back(y);

        Redraw();
    }
}


void MainWindow::on_clearTimeSerias_clicked()
{
    xPlot.clear();
    yPlot.clear();
    xResPlot.clear();
    yResPlot.clear();

    Redraw();
}

void MainWindow::on_makeTaylorSeries_clicked()
{
    xPlot.clear();
    yPlot.clear();
    xResPlot.clear();
    yResPlot.clear();

//    for(double i=-3;i<=3;i+=0.1)
//    {
//        xPlot.push_back(i);
//        yPlot.push_back(exp(i));

//        xResPlot.push_back(i);

//        double expValue=0.0;
//        double factorial=1.0;
//        int eps=(int)ui->taylorSpinBox->value();

//        for(int j=0;j<=eps;j++)
//        {
//            if(j!=0)
//            {
//                factorial*=j;
//            }

//            expValue+=pow(i,j)/factorial;
//        }

//        yResPlot.push_back(expValue);
//    }


       for(double i=-25;i<=25;i+=0.1)
       {
           xPlot.push_back(i);
           yPlot.push_back(cos(i));

           xResPlot.push_back(i);

           double expValue=0.0;
           int eps=(int)ui->taylorSpinBox->value();

           for(int j=0;j<=eps;j++)
           {
               double factorial=1.0;

               for(int k=1;k<=2*j;k++)
               {
                   factorial*=k;
               }


               expValue+=pow(-1,j)*pow(i,2*j)/factorial;
           }

           yResPlot.push_back(expValue);
       }



    Redraw();

}


void MainWindow::on_makeLagrangePolynomial_clicked()
{
    std::map<double, double> series;

    QVector<double> sortedXPlot=xPlot;
    qSort(sortedXPlot.begin(), sortedXPlot.end());

    for(int i=0;i<xPlot.size();i++)
    {
        series[xPlot[i]]=yPlot[i];
    }

    xResPlot.clear();
    yResPlot.clear();

    int n=(int)ui->polynomialDegree->value();

    if(sortedXPlot.size()<(n+1))
    {
        return;
    }


    for(double k=sortedXPlot[0];k<=sortedXPlot[sortedXPlot.size()-1];k+=0.01)
    {        
        int start=0;
        int end=sortedXPlot.size()-1;

        for(int i=0;i<sortedXPlot.size()-1;i++)
        {
            if(k>=sortedXPlot[i]&&k<=sortedXPlot[i+1])
            {
                start=i;
                end=i+1;

                while((end-start+1)<(n+1))
                {
                    start--;
                    end++;

                    if(start<0)
                    {
                        start=0;
                    }

                    if(end>=sortedXPlot.size())
                    {
                        end=sortedXPlot.size()-1;
                    }
                }

                break;
            }
        }

        double lagrangePol = 0.0;

        for(int i=start;i<=end;i++)
        {
            double basicsPol = 1.0;

            for(int j=start;j<=end;j++)
            {
                if (j != i)
                {
                    basicsPol*= (k - sortedXPlot[j])/(sortedXPlot[i] - sortedXPlot[j]);
                }
            }

            lagrangePol += basicsPol * series[sortedXPlot[i]];
        }

        xResPlot.push_back(k);
        yResPlot.push_back(lagrangePol);
    }

    Redraw();
}

void MainWindow::on_eraseLastTimeSeriesPoint_clicked()
{
    if(xPlot.size()>0&&yPlot.size()>0)
    {
        xPlot.erase(xPlot.begin()+(xPlot.size()-1));
        yPlot.erase(yPlot.begin()+(yPlot.size()-1));

        Redraw();
    }
}

void MainWindow::on_approximationLS_clicked()
{
    int columns=ui->lsPolinomeDegree->value()+2;
    int rows=ui->lsPolinomeDegree->value()+1;

    if(xPlot.size()<=0||yPlot.size()<=0)
    {
        return;
    }

    std::map<double, double> series;

    QVector<double> sortedXPlot=xPlot;
    qSort(sortedXPlot.begin(), sortedXPlot.end());

    for(int i=0;i<xPlot.size();i++)
    {
        series[xPlot[i]]=yPlot[i];
    }

    xResPlot.clear();
    yResPlot.clear();

    double** matrixPoint = new double*[rows];

    for (int i = 0; i < rows; i++)
    {
        matrixPoint[i] = new double[columns];
        memset(matrixPoint[i],0,sizeof(double)*columns);

        for (int j = 0; j < columns-1; j++)
        {
            for(int k=0;k<sortedXPlot.size();k++)
            {
               matrixPoint[i][j] += pow(sortedXPlot[k],i)*pow(sortedXPlot[k],j);
            }


        }

        for(int k=0;k<sortedXPlot.size();k++)
        {
            matrixPoint[i][columns-1] += series[sortedXPlot[k]]*pow(sortedXPlot[k],i);
        }

    }



    double * result = SolveSLAU(matrixPoint, rows, columns);

    for(double i=sortedXPlot[0];i<=sortedXPlot[sortedXPlot.size()-1];i+=0.1)
    {
        xResPlot.push_back(i);

        double value=0.0;

        for(int k=0;k<rows;k++)
        {
          value+=result[k]*pow(i,k);
        }

        yResPlot.push_back(value);
    }

    qDebug()<<"y=";
    for (int i = 0; i < rows; i++)
    {
        qDebug()<<result[i]<<"x^"<<i<<"+\r\n";
    }


    Redraw();
}

double func(double w,double x,double f, double a1,double a2)
{
    return pow(fabs(a1*sin(w*x))-fabs(a2*sin(w*(x+f))),2);
}

void MainWindow::on_makeTaylorSeries_2_clicked()
{
    xPlot.clear();
    yPlot.clear();
    xResPlot.clear();
    yResPlot.clear();

    QVector<double> a={10, 5, 2.5, 1,  0.5};
    QVector<double> w={0.5,1, 3,   5,  10};
    QVector<double> q={1,  4, 0,   0.5,1};

    int n=ui->lsPolinomeDegree_2->value();

    for(double i=-30;i<=30;i+=0.1)
    {
        xResPlot.push_back(i);
        double value=0.0;
        for(int j=0;j<n;j++)
        {
          value+=a[j]*cos(w[j]*i+q[j]);
        }

        yResPlot.push_back(value);
    }



    Redraw();
}
