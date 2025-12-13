#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPointF>
#include "PlaneGeometry/PlaneOperations.h"
#include <iostream>
#include <QPainterPath>

using namespace std;

enum class Mode {
    Default,
    VectorPoint,
    VectorVector,
    Polygon,
    Hull,
    Delone,
    Poly1,
    Poly2,
    Poly3,
    Poly4,
    Poly5,
    Orient
};

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    QVector<QPointF> m_points;
    QVector<QPointF> m_points1;
    QVector<QPointF> m_points2;
    explicit DrawWidget(QWidget *parent = nullptr);
    void clr_points();
    void paint(QPointF &point, int radius);
    void setMode(Mode m);
    void check();

signals:
    void pointsChanged(const QVector<QPointF>& points);
    void sign(bool t);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    Mode m_mode = Mode::VectorPoint;
    bool isMove;
    int pickPoint(QPoint point);
};

#endif // DRAWWIDGET_H
