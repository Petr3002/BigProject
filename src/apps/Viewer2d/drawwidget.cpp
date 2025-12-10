#include "drawwidget.h"
#include <QMessageBox>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
}
void DrawWidget::check()
{

}

int DrawWidget::pickPoint(QPoint point) {
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
    m_points.append(event->pos());
    update(); // Обновляем виджет, чтобы он перерисовался

    emit pointsChanged(m_points);
}

void
DrawWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << (event->button() == Qt::RightButton) << std::endl;
    if (event->button() == Qt::LeftButton) {
        int indexPoint = pickPoint(event->pos());
        if (isMove) {
            m_points[indexPoint] = event->pos();
            update();
        }
    }
}

void
DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);

    // Рисуем все точки, хранящиеся в массиве
    const int radius = 5; // Радиус отрисовки точек
    for (const auto &point : m_points) {
        painter.drawEllipse(point, radius, radius);
    }

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
    clr_points();
}
