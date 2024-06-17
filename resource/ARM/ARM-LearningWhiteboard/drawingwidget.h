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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool drawing = false;
    QPoint lastPoint;
    QVector<Line> lines;
    QColor penColor = Qt::black;        //画笔颜色
    int penWidth = 2;                   //画笔粗细
};

#endif // DRAWINGWIDGET_H
