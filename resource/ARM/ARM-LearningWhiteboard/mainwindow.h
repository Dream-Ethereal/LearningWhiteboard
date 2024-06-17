#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <drawingwidget.h>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tools_clicked();            //点击工具栏
    void pen_clicked();                 //点击画笔
    void eraser_clicked();              //点击橡皮擦

private:
    Ui::MainWindow *ui;                 //ui界面
    DrawingWidget *drawingWidget;       //绘画界面
    QPushButton *tool;                  //工具栏
    QPushButton *pen;                   //绘画
    QPushButton *eraser;                //橡皮擦
    QWidget *tool_bg;                   //工具栏背景

    bool tools_status = false;          //工具栏状态
};
#endif // MAINWINDOW_H
