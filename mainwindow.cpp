#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath> //extra libray
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget()->layout()->setContentsMargins(0,0,0,0);
    centralWidget()->layout()->setSpacing(0);

    ui->plot->plotColor=Qt::red;
    ui->plot->plotData.resize(100);
    ui->plot->plotData.fill(0);

    for(int n=0; n<ui->plot->plotData.size(); n++)
    {
        ui->plot->plotData[n]=abs(sin(((3*M_PI*n))/static_cast<double>(ui->plot->plotData.size())));

    }

    ui->plot2->plotColor=Qt::green;
    ui->plot2->plotData.resize(100);
    ui->plot2->plotData.fill(0);

    for(int n=0; n<ui->plot2->plotData.size(); n++)
    {
        ui->plot2->plotData[n]= sin((3 * 2*M_PI*n)/static_cast<double>(ui->plot2->plotData.size()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
