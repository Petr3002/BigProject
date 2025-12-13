#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include "PlaneGeometry/PlaneOperations.h"
#include <QMessageBox>
#include "drawwidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include "longdouble.h"
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_2->setMode(Mode::Hull);
    ui->widget_3->setMode(Mode::Delone);
    ui->widget_4->setMode(Mode::Poly1);
    ui->widget_5->setMode(Mode::Poly1);
    ui->widget_6->setMode(Mode::Poly1);
    ui->widget_7->setMode(Mode::Poly1);
    connect(ui->widget, &DrawWidget::pointsChanged, this, &MainWindow::updatePoints);
    connect(ui->RadioVectorPoint, &QRadioButton::toggled, this, [this](bool on){if (on) ui->widget->setMode(Mode::VectorPoint);});
    connect(ui->RadioVectorVector, &QRadioButton::toggled, this, [this](bool on){if (on) ui->widget->setMode(Mode::VectorVector);});
    connect(ui->RadioPolygon, &QRadioButton::toggled, this, [this](bool on){if (on) ui->widget->setMode(Mode::Polygon);});
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_3, &QRadioButton::clicked, this, [this](bool on){ui->widget_4->setMode(Mode::Poly2);});
    connect(ui->pushButton_4, &QRadioButton::clicked, this, [this](bool on){ui->widget_4->setMode(Mode::Poly3);});
    connect(ui->pushButton_5, &QRadioButton::clicked, this, [this](bool on){ui->widget_5->setMode(Mode::Poly2);});
    connect(ui->pushButton_6, &QRadioButton::clicked, this, [this](bool on){ui->widget_5->setMode(Mode::Poly4);});
    connect(ui->pushButton_7, &QRadioButton::clicked, this, [this](bool on){ui->widget_6->setMode(Mode::Poly2);});
    connect(ui->pushButton_8, &QRadioButton::clicked, this, [this](bool on){ui->widget_6->setMode(Mode::Poly5);});
    connect(ui->pushButton_9, &QRadioButton::clicked, this, [this](bool on){ui->widget_7->setMode(Mode::Orient);});
    connect(ui->widget_7, &DrawWidget::sign, this, &MainWindow::IsInside);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int p(LongDouble x1, LongDouble y1, LongDouble x2, LongDouble y2, LongDouble x3, LongDouble y3) {
    LongDouble a1 = x3 - x1;
    LongDouble b1 = y3 - y1;
    LongDouble a2 = x2 - x1;
    LongDouble b2 = y2 - y1;
    LongDouble v = a1 * b2 - a2 * b1;
    if (v > LongDouble(0.0)) return 1;
    if (v < LongDouble(0.0)) return -1;
    return 0;
}


void MainWindow::updatePoints(const QVector<QPointF>& points) {

}

void MainWindow::IsInside(bool t) {
    if (t) {
        ui->lineEdit_2->setText(QString("Внутри"));
    } else {
        ui->lineEdit_2->setText(QString("Снаружи"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    bool ok1, ok2, ok3, ok4, ok5, ok6;
    LongDouble x1, x2, x3, y1, y2, y3;

    x1 = LongDouble(ui->x_1->text().toStdString(), &ok1);
    y1 = LongDouble(ui->y_1->text().toStdString(), &ok2);
    x2 = LongDouble(ui->x_2->text().toStdString(), &ok3);
    y2 = LongDouble(ui->y_2->text().toStdString(), &ok4);
    x3 = LongDouble(ui->x_3->text().toStdString(), &ok5);
    y3 = LongDouble(ui->y_3->text().toStdString(), &ok6);


    if (!ok1 || !ok2 || !ok3 || !ok4 || !ok5 || !ok6) {
        QMessageBox::warning(nullptr, "Ошибка", "Введите корректные значения координат");
    } else {

        ui->lineEdit->setText(QString("%1").arg(p(x1, y1, x2, y2, x3, y3)));
    }
}




