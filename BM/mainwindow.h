#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Redraw();

private:
    Ui::MainWindow *ui;

    double x,y;

    QVector<double> xPlot;
    QVector<double> yPlot;

    QVector<double> xResPlot;
    QVector<double> yResPlot;


    double* SolveSLAU(double** matrix, int rowCount, int columnCount);
private slots:
    void mousePress(QMouseEvent*);
    void mouseWheel(QWheelEvent*);
    void mouseMove(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void on_clearTimeSerias_clicked();
    void on_makeTaylorSeries_clicked();
    void on_makeLagrangePolynomial_clicked();
    void on_eraseLastTimeSeriesPoint_clicked();
    void on_approximationLS_clicked();
    void on_makeTaylorSeries_2_clicked();
};
#endif // MAINWINDOW_H
