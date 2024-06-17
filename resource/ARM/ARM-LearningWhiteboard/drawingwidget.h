#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QPoint>

struct Line {
    QLine line;
    QColor color;
    int width;
};

class DrawingWidget : public QWidget {
    Q_OBJECT

public:
    DrawingWidget(QWidget *parent = nullptr);

    // 设置画笔颜色和宽度的接口
    void setPenColor(const QColor &color);
    void setPenWidth(int width);

    // 设置多边形和函数图像参数的接口
    void drawPolygon(const QVector<QPoint> &points);
    void drawFunctionGraph(double (*func)(double), double xMin, double xMax, double step);

    // 设置状态标志
    void setMoveFlag(bool flag);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool drawing = false;
    bool moveFlag = false;  // 状态标志
    QPoint lastPoint;
    QVector<Line> lines;
    QVector<QPolygon> polygons;
    QVector<QVector<QPointF>> functionGraphs;
    QColor penColor = Qt::black;
    int penWidth = 2;

    // 框选和拖动相关变量
    bool selecting = false;
    bool dragging = false;
    QRect selectionRect;
    QPoint dragStartPos;
    QVector<QPolygon> selectedPolygons;
    QVector<QVector<QPointF>> selectedGraphs;

    // 检查是否在框选区域内
    bool isInSelectionArea(const QPoint &pos) const;
};

#endif // DRAWINGWIDGET_H
