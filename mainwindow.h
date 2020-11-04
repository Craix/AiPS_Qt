#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#define DSIZE 8192
#define DSIZE2 (DSIZE/2)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void sendCommand();
    void readData();
    void error(QSerialPort::SerialPortError error);
private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
};

#endif // MAINWINDOW_H
