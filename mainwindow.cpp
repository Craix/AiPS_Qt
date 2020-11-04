#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath> //extra libray
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget()->layout()->setContentsMargins(0,0,0,0);
    centralWidget()->layout()->setSpacing(0);

    connect(ui->actionRun, &QAction::triggered, this, &MainWindow::sendCommand);
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(&serial, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)));

    ui->plot->plotData.resize(DSIZE2);
    ui->plot->plotData.fill(0);

    ui->plot2->plotData.resize(DSIZE2);
    ui->plot2->plotData.fill(0);

    ui->statusbar->showMessage("No device");

    QString portname;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if (info.description()=="VCOM_MEAS")
        {
            portname=info.portName();
            serial.setPortName(portname);
            if (serial.open(QIODevice::ReadWrite))
            {
                ui->statusbar->showMessage(tr("Device: %1").arg(info.description()));
                serial.clear();
                ui->statusbar->setEnabled(true);
            }
            else
            {
                ui->statusbar->showMessage(tr("Can't open %1, error code %2") .arg(serial.portName()).arg(serial.error()));
                qDebug() << "Hello world!";
                return;
            }

            break;
        }
    }
}

void MainWindow::sendCommand()
{
    senddata.clear();
    senddata.resize(1);
    senddata[0]=static_cast<uint8_t>(ui->actionRun->isChecked() << 7); // Run/Stop
    serial.write(senddata);
}

void MainWindow::readData()
{
    if (serial.size() >= DSIZE) {

        readdata=serial.read(DSIZE);
        qDebug()<<readdata.size();

        uint16_t *sample=reinterpret_cast<uint16_t*>(readdata.data());
        for (int n=0; n<ui->plot->plotData.size(); n++) {
            ui->plot->plotData[n]=(sample[n]-32768)/32768.0;
            ui->plot2->plotData[n]= -1 * (sample[n] - 32768)/32768.0;
        }

        ui->plot->update();
    }
}

void MainWindow::error(QSerialPort::SerialPortError error)
{
    qDebug()<<error;
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}
