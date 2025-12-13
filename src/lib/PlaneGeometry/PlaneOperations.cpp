#include "PlaneOperations.h"

double crossProduct(const QPointF& p, const QPointF& q, const QPointF& r) {
    return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x());
}

// Вспомогательная функция для вычисления квадрата расстояния между точками
double distanceSquared(const QPointF& p1, const QPointF& p2) {
    double dx = p1.x() - p2.x();
    double dy = p1.y() - p2.y();
    return dx * dx + dy * dy;
}

// Функция сравнения для сортировки точек по полярному углу относительно начальной точки
bool comparePoints(const QPointF& p1, const QPointF& p2, const QPointF& pivot) {
    // Если угол одинаковый, сортируем по расстоянию от pivot (ближайшие первыми)
    double cross = crossProduct(pivot, p1, p2);
    if (std::abs(cross) < 1e-10) {
        return distanceSquared(pivot, p1) < distanceSquared(pivot, p2);
    }
    return cross > 0;
}

void swap(QPointF& a, QPointF& b) {
    QPointF c = a;
    a = b;
    b = c;
}

QVector<QPointF> convexHull(QVector<QPointF>& points) {
    if (points.size() < 3) {
        return points;
    }
    int minIdx = 0;
    for (int i = 1; i < points.size(); ++i) {
        if (points[i].y() < points[minIdx].y() ||
            (std::abs(points[i].y() - points[minIdx].y()) < 1e-10 &&
             points[i].x() < points[minIdx].x())) {
            minIdx = i;
        }
    }
    swap(points[0], points[minIdx]);
    QPointF pivot = points[0];

    std::sort(points.begin() + 1, points.end(),
              [&pivot](QPointF& a, QPointF& b) {
                  return comparePoints(a, b, pivot);
              });

    QVector<QPointF> hull;
    hull.reserve(points.size());

    hull.append(points[0]);
    hull.append(points[1]);
    hull.append(points[2]);

    for (int i = 3; i < points.size(); ++i) {
        while (hull.size() >= 2) {
            QPointF top = hull.last();
            hull.removeLast();
            QPointF nextToTop = hull.last();

            if (crossProduct(nextToTop, top, points[i]) > 1e-10) {
                hull.append(top);
                break;
            }
        }
        hull.append(points[i]);
    }
    return hull;
}

bool isPointInCircumcircle(const QPointF& a, const QPointF& b, const QPointF& c, const QPointF& d) {
    qreal ax = a.x() - d.x();
    qreal ay = a.y() - d.y();
    qreal bx = b.x() - d.x();
    qreal by = b.y() - d.y();
    qreal cx = c.x() - d.x();
    qreal cy = c.y() - d.y();

    qreal det = (ax * ax + ay * ay) * (bx * cy - by * cx)
                - (bx * bx + by * by) * (ax * cy - ay * cx)
                + (cx * cx + cy * cy) * (ax * by - ay * bx);

    return det > 0;
}

bool areCollinear(const QPointF& a, const QPointF& b, const QPointF& c) {
    return qFabs((b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x())) < 1e-10;
}

Triangle::Triangle(const QPointF& a, const QPointF& b, const QPointF& c) : a(a), b(b), c(c) {}

bool Triangle::containsEdge(const QPointF& p1, const QPointF& p2) const {
    return ((a == p1 && b == p2) || (b == p1 && c == p2) || (c == p1 && a == p2) ||
            (a == p2 && b == p1) || (b == p2 && c == p1) || (c == p2 && a == p1));
}

void Delone(QVector<QPointF>& m_points, QVector<QPointF>& left, QVector<QPointF>& right) {
    left.clear();
    right.clear();

    if (m_points.size() < 3) return;

    qreal minX = m_points[0].x(), maxX = m_points[0].x();
    qreal minY = m_points[0].y(), maxY = m_points[0].y();

    for (const QPointF& p : m_points) {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }

    qreal dx = maxX - minX;
    qreal dy = maxY - minY;
    qreal delta = qMax(dx, dy) * 2;

    QPointF superA(minX - delta, minY - delta);
    QPointF superB(minX + 2 * delta, minY - delta);
    QPointF superC(minX + dx / 2, minY + 2 * delta);

    QVector<Triangle> triangles;
    triangles.append(Triangle(superA, superB, superC));

    for (const QPointF& point : m_points) {
        QVector<QPair<QPointF, QPointF>> edges;

        for (int i = triangles.size() - 1; i >= 0; i--) {
            Triangle& tri = triangles[i];

            if (isPointInCircumcircle(tri.a, tri.b, tri.c, point)) {
                edges.append({tri.a, tri.b});
                edges.append({tri.b, tri.c});
                edges.append({tri.c, tri.a});

                triangles.remove(i);
            }
        }

        for (int i = edges.size() - 1; i >= 0; i--) {
            bool duplicate = false;
            for (int j = i - 1; j >= 0; j--) {
                if ((edges[i].first == edges[j].first && edges[i].second == edges[j].second) ||
                    (edges[i].first == edges[j].second && edges[i].second == edges[j].first)) {
                    edges.remove(j);
                    i--;
                    duplicate = true;
                }
            }
            if (duplicate) {
                edges.remove(i);
            }
        }

        for (const auto& edge : edges) {
            if (!areCollinear(edge.first, edge.second, point)) {
                triangles.append(Triangle(edge.first, edge.second, point));
            }
        }
    }

    for (int i = triangles.size() - 1; i >= 0; i--) {
        const Triangle& tri = triangles[i];
        if (tri.a == superA || tri.a == superB || tri.a == superC ||
            tri.b == superA || tri.b == superB || tri.b == superC ||
            tri.c == superA || tri.c == superB || tri.c == superC) {
            triangles.remove(i);
        }
    }

    QVector<QPair<QPointF, QPointF>> allEdges;
    for (const Triangle& tri : triangles) {
        QPair<QPointF, QPointF> edges[3] = {
            {tri.a, tri.b}, {tri.b, tri.c}, {tri.c, tri.a}
        };

        for (const auto& edge : edges) {
            bool exists = false;
            for (const auto& existingEdge : allEdges) {
                if ((edge.first == existingEdge.first && edge.second == existingEdge.second) ||
                    (edge.first == existingEdge.second && edge.second == existingEdge.first)) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                allEdges.append(edge);
            }
        }
    }

    for (const auto& edge : allEdges) {
        left.append(edge.first);
        right.append(edge.second);
    }
}

bool isPointInPolygon(const QPointF& point, const QVector<QPointF>& polygon)
{
    if (polygon.size() < 3) {
        return false; // Многоугольник должен иметь как минимум 3 вершины
    }

    bool result = false;
    int j = polygon.size() - 1; // Последняя вершина

    for (int i = 0; i < polygon.size(); i++) {
        const QPointF& p1 = polygon[i];
        const QPointF& p2 = polygon[j];

        // Проверяем, лежит ли точка на горизонтальной грани
        if ((p1.y() == p2.y()) && (p1.y() == point.y()) &&
            (point.x() > std::min(p1.x(), p2.x())) &&
            (point.x() < std::max(p1.x(), p2.x()))) {
            return true; // Точка лежит прямо на горизонтальном ребре
        }

        // Проверяем пересечение луча, идущего вправо от точки, с ребром многоугольника
        if (((p1.y() > point.y()) != (p2.y() > point.y())) &&
            (point.x() < (p2.x() - p1.x()) * (point.y() - p1.y()) / (p2.y() - p1.y()) + p1.x())) {
            result = !result;
        }

        j = i; // Переходим к следующему ребру
    }

    return result;
}






