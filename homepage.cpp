#include "homepage.h"
#include <QPushButton>
#include<QPainter>
#include<QDebug>
#include<QtWidgets>
homepage::homepage( QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 800);
    setMaximumSize(800, 800);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));


    QButtonGroup *framelayout= new QButtonGroup();
    play=new QPushButton(QIcon(":/images/Play-Games-icon.png"),"    Play",this);
    play->setFixedSize(QSize(250,150));
    play->move(260,0);
    qDebug()<<play->x();
    play->setIconSize(QSize(100,100));
    settings=new QPushButton(QIcon(":/images/Settings-icon.png"),"Settings",this);
    settings->setFixedSize(QSize(250,150));
    settings->move(260,200);
    settings->setIconSize(QSize(100,100));
    instructions=new QPushButton(QIcon(":/images/2618630.png"),"   Rules",this);
    instructions ->setFixedSize(QSize(250,150));
    instructions->move(260,400);
    instructions->setIconSize(QSize(100,100));
    exit=new QPushButton(QIcon(":/images/223301.png"),"    Exit",this);
    exit->setFixedSize(QSize(250,150));
    exit->move(260,600);
    exit->setIconSize(QSize(100,100));
    framelayout->addButton(play);
    framelayout->addButton(settings);
    framelayout->addButton(instructions);
    framelayout->addButton(exit);
}



