#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include "PlaneGeometry/PlaneOperations.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widget, &DrawWidget::pointsChanged, this, &MainWindow::updatePoints);

}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <iostream>
void MainWindow::updatePoints(const QVector<QPointF>& points)
{
    // Здесь код для обработки точек
    std::cout << "Точки получены" << std::endl;
    ui->widget->check();
}





