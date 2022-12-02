#include "mainwindow.h"
#include "boardwidget.h"
#include <QtWidgets>
#include <stdlib.h>
#include"homepage.h"
#include"timer.h"
#include<QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Parent=parent;
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Chess"));
    setuphomepage();
}



void MainWindow::setCompleted()
{
    QMessageBox::information(this, tr("Puzzle Completed"),
                             tr("Congratulations! You have completed the puzzle!\n"
                                "Click OK to start again."),
                             QMessageBox::Ok);

    setupBoard();
}



void MainWindow::setupBoard()
{
       boardWidget->setBoard();
}

void MainWindow::setupPlay()
{
  //  setupMenus();
    setupWidgets();
}



void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Exit"));

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    gameMenu->addAction("&Reset Board", this, &MainWindow::setupBoard);
}

void MainWindow::setupWidgets()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);

    timewidget  = new timer(this);
    timewidget->reset();
    boardWidget = new BoardWidget(this,timewidget);
    int *dummy=&boardWidget->move;
    timewidget->move=dummy;
    frameLayout->setContentsMargins(QMargins(0,0,0,0));
    frameLayout->setSpacing(0);
    QPushButton * back=new QPushButton(QIcon(":/images/PngItem_116863.png"),"",this);
    back->setFixedSize(QSize(100,100));
    back->setIconSize(QSize(50,50));
   // back->frameSize()=QSize(100,100);
    back->setMinimumSize(QSize(100,100));
    back->setMaximumSize(QSize(100,100));
    boardWidget->pos()=QPoint(500,0);
    connect(boardWidget, &BoardWidget::puzzleCompleted,
    this, &MainWindow::setCompleted, Qt::QueuedConnection);
    QObject::connect(back,&QPushButton::clicked,this ,&MainWindow::setuphomepage);
    QObject::connect(timewidget,&timer::timeup,boardWidget,&BoardWidget::gameover);
    frameLayout->addWidget(timewidget,0,Qt::AlignCenter);
        frameLayout->addWidget(boardWidget,0,Qt::AlignLeft);
    frameLayout->addWidget(back,0,Qt::AlignJustify|Qt::AlignTop);
   // setLayout(frameLayout);
    setCentralWidget(frame);
    saveState(0);
}

void MainWindow::setuphomepage()
{
    QFrame *frame = new QFrame();
    QGridLayout *framelayout= new QGridLayout(frame);
    home = new homepage(this);
    frame->setStyleSheet("QFrame{"
                         "border-image: url(:/images/wp3081383-chess-hd-wallpapers.png) 0 0 0 0  ;"
                        "background-repeat: no-repeat;"
                         "width: 100%;"
                         "height:100%;"
                         "background-position: center center;"
                         "text-align:center;"
                         "margin:auto;"
                         "padding:0;"
                        "}");
    QObject:: connect(home->play,SIGNAL(clicked()),this,SLOT(setupPlay()));
    QObject::connect(home->exit,SIGNAL(clicked()),this,SLOT(close()));
    framelayout->addWidget(home);
    timewidget->stackUnder(Parent);
    setCentralWidget(frame);

}


