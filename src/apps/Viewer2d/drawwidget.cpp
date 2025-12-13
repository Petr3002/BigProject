#include "drawwidget.h"
#include <QMessageBox>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include "PlaneGeometry/PlaneOperations.h"

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
    m_mode = Mode::Default;
}
void DrawWidget::check()
{

}

int DrawWidget::pickPoint(QPoint point) {
    if (m_mode == Mode::Poly1 || m_mode == Mode::Poly2 || m_mode == Mode::Poly3) {
        isMove = false;
        return -1;
    }
    double min = 100000.0, xx, yy, d;
    int x = point.x(), y = point.y(), indexPoint = -1;
    for (int i = 0; i < m_points.size(); i++) {
        xx = m_points[i].x();
        yy = m_points[i].y();
        d = (xx - x) * (xx - x) + (yy - y) * (yy - y);
        if (d < min * min) {
            min = d;
            indexPoint = i;
        }
    } if (min > 100) {
        isMove = false;
        return -1;
    } else {
        isMove = true;
        return indexPoint;
    }
}

void DrawWidget::clr_points(){
    m_points.clear();
    update();
}

void
DrawWidget::mousePressEvent(QMouseEvent *event)
{
    // Добавляем точку в массив каждый раз, когда кликаем на виджет
    pickPoint(event->pos());
    if (!isMove) {
        if (m_mode == Mode::Orient && m_points2.size() == 1) {
            m_points2[0] = event->pos();
            m_points[m_points.size() - 1] = event->pos();
            update();
            return;
        }
        if (m_mode == Mode::Poly3 || m_mode == Mode::Poly4 || m_mode == Mode::Poly5) {
            QMessageBox::warning(nullptr, "Ошибка", "Довольно! Хватит и этих точек!");
            return;
        }
        if (m_mode == Mode::Poly2 || m_mode == Mode::Orient) {
            m_points2.append(event->pos());
        }
        if (m_mode == Mode::Poly1) {
            m_points1.append(event->pos());
        }
        m_points.append(event->pos());
        update();

    }

    emit pointsChanged(m_points);
}

void
DrawWidget::mouseMoveEvent(QMouseEvent *event) {
        int indexPoint = pickPoint(event->pos());
        if (isMove) {
            m_points[indexPoint] = event->pos();
            update();
        }

}

void
DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);




    if (m_mode == Mode::VectorPoint) {
        if (m_points.size() > 1) {
            painter.drawLine(m_points[0], m_points[1]);
        }
    } else if (m_mode == Mode::VectorVector) {
        if (m_points.size() > 4) {
            m_points.pop_back();
            QMessageBox::warning(nullptr, "Ошибка", "Многа точек");
        } else if (m_points.size() == 4) {
            painter.drawLine(m_points[0], m_points[1]);
            painter.drawLine(m_points[2], m_points[3]);
        }
    } else if (m_mode == Mode::Polygon) {
        int len = m_points.size();
        if (len > 1) {
            double x = m_points[0].x() - m_points[len - 1].x();
            double y = m_points[0].y() - m_points[len - 1].y();
            if (x * x + y * y < 100) {
                m_points.pop_back();
                if (len > 2) {
                for (int i = 0; i < len - 2; i++) {
                    painter.drawLine(m_points[i], m_points[i + 1]);
                }
                painter.drawLine(m_points[0], m_points[len - 2]);
                }
            } else {
                for (int i = 0; i < len - 1; i++) {
                    painter.drawLine(m_points[i], m_points[i + 1]);
                }
            }
        }
    } else if (m_mode == Mode::Hull) {
        QVector<QPointF> hull = convexHull(m_points);
        int lenh = hull.size();
        for (int i = 0; i < lenh; i++) {
            painter.drawLine(hull[i], hull[(i + 1) % lenh]);
        }
    } else if (m_mode == Mode::Delone) {
        QVector<QPointF> left, right;
        Delone(m_points, left, right);
        int n = left.size();
        for (int i = 0; i < n; i++) {
            painter.drawLine(left[i], right[i]);
        }
    } else if (m_mode == Mode::Poly1) {
        int lenh = m_points1.size();
        for (int i = 0; i < lenh; i++) {
            painter.drawLine(m_points1[i], m_points1[(i + 1) % lenh]);
        }
    } else if (m_mode == Mode::Poly2) {
        int lenh1 = m_points1.size();
        for (int i = 0; i < lenh1; i++) {
            painter.drawLine(m_points1[i], m_points1[(i + 1) % lenh1]);
        }


        int lenh2 = m_points2.size();
        for (int i = 0; i < lenh2; i++) {
            painter.drawLine(m_points2[i], m_points2[(i + 1) % lenh2]);
        }
    } else if (m_mode == Mode::Poly3) {
        int lenh1 = m_points1.size();
        for (int i = 0; i < lenh1; i++) {
            painter.drawLine(m_points1[i], m_points1[(i + 1) % lenh1]);
        }


        int lenh2 = m_points2.size();
        for (int i = 0; i < lenh2; i++) {
            painter.drawLine(m_points2[i], m_points2[(i + 1) % lenh2]);
        }

        QPolygonF polygon1(m_points1);
        QPolygonF polygon2(m_points2);
        QPainterPath path1;
        path1.addPolygon(polygon1);

        QPainterPath path2;
        path2.addPolygon(polygon2);
        QPainterPath intersectionPath = path1.intersected(path2);

        if (!intersectionPath.isEmpty()) {
            painter.setBrush(QBrush(Qt::blue));
            painter.setPen(Qt::NoPen);
            painter.drawPath(intersectionPath);
        }
    } else if (m_mode == Mode::Poly4) {
        int lenh1 = m_points1.size();
        for (int i = 0; i < lenh1; i++) {
            painter.drawLine(m_points1[i], m_points1[(i + 1) % lenh1]);
        }

        int lenh2 = m_points2.size();
        for (int i = 0; i < lenh2; i++) {
            painter.drawLine(m_points2[i], m_points2[(i + 1) % lenh2]);
        }

        QPolygonF polygon1(m_points1);
        QPolygonF polygon2(m_points2);
        QPainterPath path1;
        path1.addPolygon(polygon1);

        QPainterPath path2;
        path2.addPolygon(polygon2);

        QPainterPath unionPath = path1.united(path2);

        if (!unionPath.isEmpty()) {
            painter.setBrush(QBrush(Qt::blue));
            painter.setPen(Qt::NoPen);
            painter.drawPath(unionPath);
        }
    } else if (m_mode == Mode::Poly5) {
        int lenh1 = m_points1.size();
        for (int i = 0; i < lenh1; i++) {
            painter.drawLine(m_points1[i], m_points1[(i + 1) % lenh1]);
        }

        int lenh2 = m_points2.size();
        for (int i = 0; i < lenh2; i++) {
            painter.drawLine(m_points2[i], m_points2[(i + 1) % lenh2]);
        }

        QPolygonF polygon1(m_points1);
        QPolygonF polygon2(m_points2);
        QPainterPath path1;
        path1.addPolygon(polygon1);

        QPainterPath path2;
        path2.addPolygon(polygon2);

        QPainterPath substractionPath = path1.subtracted(path2);

        if (!substractionPath.isEmpty()) {
            painter.setBrush(QBrush(Qt::blue));
            painter.setPen(Qt::NoPen);
            painter.drawPath(substractionPath);
        }
    } else if (m_mode == Mode::Orient) {
        int lenh1 = m_points1.size();
        for (int i = 0; i < lenh1; i++) {
            painter.drawLine(m_points1[i], m_points1[(i + 1) % lenh1]);
        }

        if (m_points2.size() == 1) {
            QPointF a = m_points2[0];
            sign(isPointInPolygon(a, m_points1));
        }
    }



    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);
    // Рисуем все точки, хранящиеся в массиве
    const int radius = 5; // Радиус отрисовки точек
    for (const auto &point : m_points) {
        painter.drawEllipse(point, radius, radius);
    }
}

void
DrawWidget::paint(QPointF &point, int radius)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);
    painter.drawEllipse(point, radius, radius);
}


void
DrawWidget::mouseReleaseEvent(QMouseEvent *event) {
    isMove = false;
}

void DrawWidget::setMode(Mode m) {
    if (m_mode == m) {
        return;
    }
    m_mode = m;
}
