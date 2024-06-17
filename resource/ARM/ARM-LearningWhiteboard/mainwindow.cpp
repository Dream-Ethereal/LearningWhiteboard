#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int flag;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawingWidget = new DrawingWidget(ui->widget);

    //工具栏的背景
    tool_bg = new QWidget(drawingWidget);
    tool_bg->setObjectName(QString::fromUtf8("tool_bg"));
    tool_bg->setGeometry(QRect(20, 360, 280, 70));
    tool_bg->setStyleSheet(QString::fromUtf8("QWidget#tool_bg{background-image: url(:/icon/icon/tool_bar.png);background-color: transparent;}"));
    tool_bg->setVisible(false);

    //工具栏按钮
    tool = new QPushButton(drawingWidget);
    tool->setObjectName(QString::fromUtf8("tool"));
    tool->setGeometry(QRect(20, 360, 73, 72));
    tool->setStyleSheet(QString::fromUtf8("QPushButton#tool{background-image: url(:/icon/icon/tool_70x70.png);background-color: transparent;}"));
    tool->setFlat(true);

    //画笔按钮
    pen = new QPushButton(drawingWidget);
    pen->setObjectName(QString::fromUtf8("pen"));
    pen->setGeometry(QRect(120, 360, 73, 72));
    pen->setStyleSheet(QString::fromUtf8("QPushButton#pen{background-image: url(:/icon/icon/pen_checked_70x70.png);background-color: transparent;}"));
    pen->setFlat(true);
    pen->setEnabled(false);
    pen->setVisible(false);

    //橡皮擦按钮
    eraser = new QPushButton(drawingWidget);
    eraser->setObjectName(QString::fromUtf8("eraser"));
    eraser->setGeometry(QRect(220, 360, 73, 72));
    eraser->setStyleSheet(QString::fromUtf8("QPushButton#eraser{background-image: url(:/icon/icon/eraser_release_70x70.png);background-color: transparent;}"));
    eraser->setFlat(true);
    eraser->setEnabled(true);
    eraser->setVisible(false);

    //调色盘按钮
    color_change = new QPushButton(drawingWidget);
    color_change->setObjectName(QString::fromUtf8("color_change"));
    color_change->setGeometry(QRect(320, 360, 73, 72));
    color_change->setStyleSheet(QString::fromUtf8("QPushButton#color_change{background-image: url(:/icon/icon/color.png);background-color: transparent;}"));
    color_change->setFlat(true);
    color_change->setEnabled(true);
    color_change->setVisible(false);

    //调色盘按钮
    color_change1 = new QPushButton(drawingWidget);
    color_change1->setObjectName(QString::fromUtf8("color_change1"));
    color_change1->setGeometry(QRect(420, 360, 73, 72));
    color_change1->setStyleSheet(QString::fromUtf8("QPushButton#color_change1{background-image: url(:/icon/icon/color.png);background-color: transparent;}"));
    color_change1->setFlat(true);
    color_change1->setEnabled(true);
    color_change1->setVisible(false);

    //信号槽连接
    connect(tool, SIGNAL(clicked()), this, SLOT(on_tools_clicked()));
    connect(pen, SIGNAL(clicked()), this, SLOT(pen_clicked()));
    connect(eraser, SIGNAL(clicked()), this, SLOT(eraser_clicked()));
    connect(color_change, SIGNAL(clicked()), this, SLOT(color_clicked()));
    connect(color_change1, SIGNAL(clicked()), this, SLOT(color1_clicked()));
    ui->setupUi(this);
    setCentralWidget(drawingWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tools_clicked()
{
    if(!tools_status)
    {
        //展开工具栏
        tools_status = !tools_status;
        tool_bg->setVisible(true);
        pen->setVisible(true);
        eraser->setVisible(true);
        color_change->setVisible(true);
        color_change1->setVisible(true);
    }else
    {
        //收回工具栏
        tools_status = !tools_status;
        tool_bg->setVisible(false);
        pen->setVisible(false);
        eraser->setVisible(false);
        color_change->setVisible(false);
        color_change1->setVisible(false);
    }

}

//点击画笔
void MainWindow::pen_clicked()
{
    drawingWidget->drawPolygon({QPoint(100, 100), QPoint(200, 100), QPoint(150, 200)});
    //drawingWidget->drawFunctionGraph([](double x) { return 50 * qSin(x / 50); }, 0, 400, 1);

    //设置状态
    pen->setStyleSheet(QString::fromUtf8("QPushButton#pen{background-image: url(:/icon/icon/pen_checked_70x70.png);background-color: transparent;}"));
    eraser->setStyleSheet(QString::fromUtf8("QPushButton#eraser{background-image: url(:/icon/icon/eraser_release_70x70.png);background-color: transparent;}"));
    pen->setEnabled(false);
    eraser->setEnabled(true);
    color_change->setEnabled(true);

    //调整画笔，黑色，粗细2
    drawingWidget->setPenColor(Qt::black);
    drawingWidget->setPenWidth(2);
}

//点击橡皮擦
void MainWindow::eraser_clicked()
{
    //设置状态
    pen->setStyleSheet(QString::fromUtf8("QPushButton#pen{background-image: url(:/icon/icon/pen_release_70x70.png);background-color: transparent;}"));
    eraser->setStyleSheet(QString::fromUtf8("QPushButton#eraser{background-image: url(:/icon/icon/eraser_checked_70x70.png);background-color: transparent;}"));
    pen->setEnabled(true);
    eraser->setEnabled(false);
    color_change->setEnabled(false);

    //调整画笔，背景色，粗细20,充当橡皮擦
    drawingWidget->setPenColor(Qt::white);
    drawingWidget->setPenWidth(20);

}

void MainWindow::color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose Pen Color");
    if (color.isValid()) {
        drawingWidget->setPenColor(color);
    }
}

void MainWindow::color1_clicked()
{
    drawingWidget->setMoveFlag(true);
}

