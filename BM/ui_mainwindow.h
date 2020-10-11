/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QPushButton *clearTimeSerias;
    QPushButton *makeTaylorSeries;
    QPushButton *makeLagrangePolynomial;
    QDoubleSpinBox *taylorSpinBox;
    QPushButton *eraseLastTimeSeriesPoint;
    QDoubleSpinBox *polynomialDegree;
    QPushButton *approximationLS;
    QDoubleSpinBox *lsPolinomeDegree;
    QPushButton *makeTaylorSeries_2;
    QDoubleSpinBox *lsPolinomeDegree_2;
    QCustomPlot *plot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(200, 0));
        widget_2->setMaximumSize(QSize(200, 16777215));
        clearTimeSerias = new QPushButton(widget_2);
        clearTimeSerias->setObjectName(QString::fromUtf8("clearTimeSerias"));
        clearTimeSerias->setGeometry(QRect(10, 10, 181, 23));
        makeTaylorSeries = new QPushButton(widget_2);
        makeTaylorSeries->setObjectName(QString::fromUtf8("makeTaylorSeries"));
        makeTaylorSeries->setGeometry(QRect(10, 40, 111, 23));
        makeLagrangePolynomial = new QPushButton(widget_2);
        makeLagrangePolynomial->setObjectName(QString::fromUtf8("makeLagrangePolynomial"));
        makeLagrangePolynomial->setGeometry(QRect(10, 70, 111, 23));
        taylorSpinBox = new QDoubleSpinBox(widget_2);
        taylorSpinBox->setObjectName(QString::fromUtf8("taylorSpinBox"));
        taylorSpinBox->setGeometry(QRect(130, 40, 62, 22));
        taylorSpinBox->setMaximum(1000.000000000000000);
        taylorSpinBox->setValue(10.000000000000000);
        eraseLastTimeSeriesPoint = new QPushButton(widget_2);
        eraseLastTimeSeriesPoint->setObjectName(QString::fromUtf8("eraseLastTimeSeriesPoint"));
        eraseLastTimeSeriesPoint->setGeometry(QRect(10, 210, 161, 23));
        polynomialDegree = new QDoubleSpinBox(widget_2);
        polynomialDegree->setObjectName(QString::fromUtf8("polynomialDegree"));
        polynomialDegree->setGeometry(QRect(130, 70, 62, 22));
        polynomialDegree->setDecimals(0);
        polynomialDegree->setMaximum(50.000000000000000);
        polynomialDegree->setValue(1.000000000000000);
        approximationLS = new QPushButton(widget_2);
        approximationLS->setObjectName(QString::fromUtf8("approximationLS"));
        approximationLS->setGeometry(QRect(10, 100, 111, 23));
        lsPolinomeDegree = new QDoubleSpinBox(widget_2);
        lsPolinomeDegree->setObjectName(QString::fromUtf8("lsPolinomeDegree"));
        lsPolinomeDegree->setGeometry(QRect(130, 100, 62, 22));
        lsPolinomeDegree->setDecimals(0);
        lsPolinomeDegree->setMinimum(1.000000000000000);
        lsPolinomeDegree->setMaximum(30.000000000000000);
        lsPolinomeDegree->setValue(2.000000000000000);
        makeTaylorSeries_2 = new QPushButton(widget_2);
        makeTaylorSeries_2->setObjectName(QString::fromUtf8("makeTaylorSeries_2"));
        makeTaylorSeries_2->setGeometry(QRect(10, 130, 111, 23));
        lsPolinomeDegree_2 = new QDoubleSpinBox(widget_2);
        lsPolinomeDegree_2->setObjectName(QString::fromUtf8("lsPolinomeDegree_2"));
        lsPolinomeDegree_2->setGeometry(QRect(130, 130, 62, 22));
        lsPolinomeDegree_2->setDecimals(0);
        lsPolinomeDegree_2->setMaximum(5.000000000000000);
        lsPolinomeDegree_2->setValue(1.000000000000000);

        horizontalLayout->addWidget(widget_2);

        plot = new QCustomPlot(centralwidget);
        plot->setObjectName(QString::fromUtf8("plot"));

        horizontalLayout->addWidget(plot);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        clearTimeSerias->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271 \321\200\321\217\320\264", nullptr));
        makeTaylorSeries->setText(QApplication::translate("MainWindow", "\320\240\321\217\320\264 \320\242\320\265\320\271\320\273\320\276\321\200\320\260", nullptr));
        makeLagrangePolynomial->setText(QApplication::translate("MainWindow", "\320\233\320\260\320\263\321\200\320\260\320\275\320\264\320\266", nullptr));
        eraseLastTimeSeriesPoint->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\321\216\321\216 \321\202\320\276\321\207\320\272\321\203", nullptr));
        approximationLS->setText(QApplication::translate("MainWindow", "\320\234\320\235\320\232", nullptr));
        makeTaylorSeries_2->setText(QApplication::translate("MainWindow", "\320\240\321\217\320\264 \320\244\321\203\321\200\321\214\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
