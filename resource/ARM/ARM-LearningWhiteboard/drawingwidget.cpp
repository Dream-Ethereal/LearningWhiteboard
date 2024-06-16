#include "drawingwidget.h"

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

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        lines.append({QLine(lastPoint, event->pos()), penColor, penWidth});
        lastPoint = event->pos();
        update();
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        lines.append({QLine(lastPoint, event->pos()), penColor, penWidth});
        drawing = false;
        update();
    }
}

void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const Line &line : qAsConst(lines)) {
        QPen pen(line.color, line.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(line.line);
    }
}
