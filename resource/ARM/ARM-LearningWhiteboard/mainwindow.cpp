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



    //信号槽连接
    connect(tool, SIGNAL(clicked()), this, SLOT(on_tools_clicked()));
    connect(pen, SIGNAL(clicked()), this, SLOT(pen_clicked()));
    connect(eraser, SIGNAL(clicked()), this, SLOT(eraser_clicked()));

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
        tools_status = !tools_status;
        tool_bg->setVisible(true);
        pen->setVisible(true);
        eraser->setVisible(true);
    }else
    {
        tools_status = !tools_status;
        tool_bg->setVisible(false);
        pen->setVisible(false);
        eraser->setVisible(false);
    }

}

void MainWindow::pen_clicked()
{
    //设置状态
    pen->setStyleSheet(QString::fromUtf8("QPushButton#pen{background-image: url(:/icon/icon/pen_checked_70x70.png);background-color: transparent;}"));
    eraser->setStyleSheet(QString::fromUtf8("QPushButton#eraser{background-image: url(:/icon/icon/eraser_release_70x70.png);background-color: transparent;}"));
    pen->setEnabled(false);
    eraser->setEnabled(true);

    drawingWidget->setPenColor(Qt::black);
    drawingWidget->setPenWidth(2);
}

void MainWindow::eraser_clicked()
{
    //设置状态
    pen->setStyleSheet(QString::fromUtf8("QPushButton#pen{background-image: url(:/icon/icon/pen_release_70x70.png);background-color: transparent;}"));
    eraser->setStyleSheet(QString::fromUtf8("QPushButton#eraser{background-image: url(:/icon/icon/eraser_checked_70x70.png);background-color: transparent;}"));
    pen->setEnabled(true);
    eraser->setEnabled(false);

    drawingWidget->setPenColor(Qt::white);
    drawingWidget->setPenWidth(20);
//    QColor color = QColorDialog::getColor(Qt::black, this, "Choose Pen Color");
//    if (color.isValid()) {
//        drawingWidget->setPenColor(color);
//    }
}

