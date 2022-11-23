#include "mainwindow.h"
#include "boardwidget.h"
#include <QtWidgets>
#include <stdlib.h>
#include"homepage.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupMenus();
    setupWidgets();
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Chess"));
//    setuphomepage();
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
    boardWidget = new BoardWidget();



    connect(boardWidget, &BoardWidget::puzzleCompleted,
            this, &MainWindow::setCompleted, Qt::QueuedConnection);


    frameLayout->addWidget(boardWidget);
    setCentralWidget(frame);
}

void MainWindow::setuphomepage()
{
    QFrame *frame = new QFrame;
    QVBoxLayout *framelayout= new QVBoxLayout(frame);
    home = new homepage(this);
    framelayout->addWidget(home);
    setCentralWidget(frame);

}
