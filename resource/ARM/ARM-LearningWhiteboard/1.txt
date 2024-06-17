#include "drawingwidget.h"
#include <QtMath>  // 包含 qSin 函数

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);

    // 设置背景色为白色
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void DrawingWidget::setPenColor(const QColor &color) {
    penColor = color;
}

void DrawingWidget::setPenWidth(int width) {
    penWidth = width;
}

void DrawingWidget::setMoveFlag(bool flag) {
    moveFlag = flag;
}

void DrawingWidget::drawPolygon(const QVector<QPoint> &points) {
    polygons.append(QPolygon(points));
    update();
}

void DrawingWidget::drawFunctionGraph(double (*func)(double), double xMin, double xMax, double step) {
    QVector<QPointF> points;
    for (double x = xMin; x <= xMax; x += step) {
        points.append(QPointF(x, func(x)));
    }
    functionGraphs.append(points);
    update();
}

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if (moveFlag) {
        if (isInSelectionArea(event->pos())) {
            // 如果在框选区域内，开始拖动
            dragging = true;
            dragStartPos = event->pos();
        } else {
            // 如果不在框选区域内，开始新的框选
            selecting = true;
            selectionRect.setTopLeft(event->pos());
            selectionRect.setBottomRight(event->pos());
            selectedPolygons.clear();
            selectedGraphs.clear();
        }
    } else {
        // 进入绘图模式
        if (event->button() == Qt::LeftButton) {
            lastPoint = event->pos();
            drawing = true;
        }
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if (moveFlag) {
        if (selecting) {
            // 更新框选矩形
            selectionRect.setBottomRight(event->pos());
            update();
        } else if (dragging) {
            // 拖动选中的区域
            QPoint delta = event->pos() - dragStartPos;
            dragStartPos = event->pos();
            // 移动选中的多边形
            for (QPolygon &polygon : selectedPolygons) {
                polygon.translate(delta);
            }
            // 移动选中的函数图像
            for (QVector<QPointF> &graph : selectedGraphs) {
                for (QPointF &point : graph) {
                    point += delta;
                }
            }
            update();
        }
    } else {
        if (drawing && (event->buttons() & Qt::LeftButton)) {
            lines.append({QLine(lastPoint, event->pos()), penColor, penWidth});
            lastPoint = event->pos();
            update();
        }
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (moveFlag) {
        if (selecting) {
            // 结束框选，确定选中区域内的图形
            selecting = false;
            for (const QPolygon &polygon : qAsConst(polygons)) {
                if (selectionRect.intersects(polygon.boundingRect())) {
                    selectedPolygons.append(polygon);
                }
            }
            for (const QVector<QPointF> &graph : qAsConst(functionGraphs)) {
                QRectF boundingRect;
                for (const QPointF &point : graph) {
                    boundingRect |= QRectF(point, QSizeF(1, 1));
                }
                if (selectionRect.intersects(boundingRect.toRect())) {
                    selectedGraphs.append(graph);
                }
            }
            if (!selectedPolygons.isEmpty() || !selectedGraphs.isEmpty()) {
                dragging = true;
                dragStartPos = event->pos();
            }
            update();
        } else if (dragging) {
            // 结束拖动
            dragging = false;
        }
    } else {
        if (event->button() == Qt::LeftButton && drawing) {
            lines.append({QLine(lastPoint, event->pos()), penColor, penWidth});
            drawing = false;
            update();
        }
    }
}

void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制之前的线条
    for (const Line &line : qAsConst(lines)) {
        QPen pen(line.color, line.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(line.line);
    }

    // 绘制多边形
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (const QPolygon &polygon : qAsConst(polygons)) {
        painter.drawPolygon(polygon);
    }

    // 绘制函数图像
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (const QVector<QPointF> &graph : qAsConst(functionGraphs)) {
        for (int i = 0; i < graph.size() - 1; ++i) {
            painter.drawLine(graph[i], graph[i + 1]);
        }
    }

    // 绘制框选矩形
    if (selecting) {
        painter.setPen(Qt::DashLine);
        painter.drawRect(selectionRect);
    }
}

bool DrawingWidget::isInSelectionArea(const QPoint &pos) const {
    return selectionRect.contains(pos);
}
