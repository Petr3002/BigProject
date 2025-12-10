#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPointF>

enum class Mode {
    VectorPoint,
    VectorVector,
    Polygon
};

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    QVector<QPointF> m_points;
    explicit DrawWidget(QWidget *parent = nullptr);
    void clr_points();
    void paint(QPointF &point, int radius);
    void setMode(Mode m);
    void check();

signals:
    void pointsChanged(const QVector<QPointF>& points);

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
