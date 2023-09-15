#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <QDebug>
#define Pi 3.14159265358979323846

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QColor blue(0, 0, 250);
    QColor rayBlue(96, 10, 228);

    float radius;

    if (width() > height())
     radius = height() * 0.1;
    else radius = width() * 0.1;

    if (width() < 30 || height() < 30 || raysNumber < 4)
     return;

    std::vector<int> scalers;
    std::vector<float> angles;

    for (int i = 0; i < raysNumber; i++) {
        scalers.push_back(rand() % 6 + 1);
    }

    int scalersSum = std::accumulate(scalers.begin(), scalers.end(), 0);

    for (int i = 0; i < raysNumber; i++) {
        angles.push_back(scalers[i] * 2 * Pi / scalersSum);
    }

    QPointF center = QPointF(width() / 2, height() / 2);
    QRectF rect = QRectF(center.x() - radius, center.y() - radius, radius*2, radius*2);

    std::vector<QPointF [3]> pointsVector(raysNumber);
    int i = 0;
    float currentAngle = 0;

    for(auto & newAngle: angles) {
        pointsVector[i][0] = QPointF(center.x() + radius * cos(currentAngle), center.y() - radius * sin(currentAngle));
        pointsVector[i][2] = QPointF(center.x() + radius * cos(currentAngle + newAngle), center.y() - radius * sin(currentAngle + newAngle));
        int randomScalar = rand() % 6 + 2;
        pointsVector[i][1] = QPointF(center.x() + randomScalar * radius * cos(newAngle / 2 + currentAngle),
                                      center.y() - randomScalar * radius * sin(newAngle / 2 + currentAngle));
        currentAngle += newAngle;
        i++;
    }

    painter.setBrush( blue);
    painter.setPen( blue );

    painter.translate(center);
    painter.rotate(angle);
    painter.translate(-center);
    painter.drawEllipse(rect);

    painter.setBrush(rayBlue);
    for(auto & points: pointsVector) {
        painter.drawPolygon(points, 3);
    }

}


void MainWindow::wheelEvent(QWheelEvent* wheelevent)
{
    angle -= wheelevent->delta() / 10;
    repaint();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    MainWindow::raysNumber = arg1;
    repaint();
}
