#include "drawwidget.h"


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

void
DrawWidget::mousePressEvent(QMouseEvent *event)
{
    // Добавляем точку в массив каждый раз, когда кликаем на виджет
    m_points.append(event->pos());
    update(); // Обновляем виджет, чтобы он перерисовался

    emit pointsChanged(m_points);
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
}
