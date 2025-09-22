#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPointF>

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWidget(QWidget *parent = nullptr);

    void check();

signals:
    void pointsChanged(const QVector<QPointF>& points);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPointF> m_points;
};


#endif // DRAWWIDGET_H
