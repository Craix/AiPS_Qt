#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QPainter>

#define MX 40
#define MY 20

class Plot : public QWidget
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = nullptr);
    QVector<double> plotData;
    int gridNumX=10, gridNumY=10;
    int minValueX=-0, maxValueX=100;
    int minValueY=-100, maxValueY=100;
    QColor backgroundColor=Qt::black;
    QColor gridColor=Qt::gray;
    QColor textColor=Qt::white;
    QColor plotColor=Qt::red;

private:
    void paintEvent(QPaintEvent *event);
    void drawLinearGrid();
    void drawLinearData();
    double dx, dy, dvx, dvy;
    int gx=MX, gy=MY, gw=0, gh=0, gmy=0;
signals:
};

#endif // PLOT_H
