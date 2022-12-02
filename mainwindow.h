#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include"timer.h"

class homepage;
class BoardWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


public slots:
    void setupBoard();
    void setupPlay();
    void setCompleted();


private:
    void setupMenus();
    void setupWidgets();
public slots:
    void setuphomepage();

private:
    BoardWidget *boardWidget;
    homepage *home;
    timer *timewidget;
    QWidget *Parent;
};

#endif // MAINWINDOW_H
