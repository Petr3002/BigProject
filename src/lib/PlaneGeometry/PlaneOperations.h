#pragma once

#include <QPointF>
#include <QVector>
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <set>

struct Triangle {
    QPointF a, b, c;

    Triangle(const QPointF& a, const QPointF& b, const QPointF& c);

    bool containsEdge(const QPointF& p1, const QPointF& p2) const;
};

double crossProduct(const QPointF& p, const QPointF& q, const QPointF& r);
double distanceSquared(const QPointF& p1, const QPointF& p2);
bool comparePoints(const QPointF& p1, const QPointF& p2, const QPointF& pivot);
QVector<QPointF> convexHull(QVector<QPointF>& points);
void swap(const QPointF& a, const QPointF& b);
bool areCollinear(const QPointF& a, const QPointF& b, const QPointF& c);
bool isPointInCircumcircle(const QPointF& a, const QPointF& b, const QPointF& c, const QPointF& d);
void Delone(QVector<QPointF>& m_points, QVector<QPointF>& left, QVector<QPointF>& right);
bool isPointInPolygon(const QPointF& point, const QVector<QPointF>& polygon);
