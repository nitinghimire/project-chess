#include "timer.h"
#include<QTimer>
#include<QLabel>
#include<QString>
#include<QPainter>
#include<QHBoxLayout>
timer::timer( QWidget *parent)
    : QWidget(parent)
{
    this->parent=parent;
    setMinimumSize(400,400);
    setMaximumSize(400, 400);
    label = new QLabel(parent);
    time =new QTimer(parent);
    display();
    QObject::connect(time,SIGNAL(timeout()),this,SLOT(decrease()));
    QObject::connect(time,SIGNAL(timeout()),this,SLOT(display()));
    QObject::connect(time,SIGNAL(timeout()),this,SLOT(setup()));
    time->start(1000);
}

void timer::reset()
{
    this->timeformatwhite.minutes = 5;
    this->timeformatwhite.seconds =0;
    this->timeformatblack.minutes=5;
    this->timeformatblack.seconds=0;
    time->start(1000);

}


void timer::display()
{
    qDebug()<<"display was entered";
   // label->activateWindow();
    label->setStyleSheet("QLabel{background-color: #999999;"
                                                   "border-radius: 10px;"
                                                   "border-width: 1px;"
                                                   "color: #ffffff;"
                                                   "display: inline-block;"
                                                   "font-family:  Helvetica, Arial, sans-serif;"
                                                   "font-size: 30px;"
                                                   " font-weight: 500;"
                                                   "line-height: 20px;"
                                                   "margin: 0;"
                                                   "padding: 10px 12px;"
                                                   "text-align: center;}");
    label->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    label->setText(QString("BLACK : ")+QString::number(timeformatblack.minutes)+" : "+QString::number(timeformatblack.seconds)
                   +"\n"+"\n"+"\n"+
                   QString("WHITE : ")+QString::number(timeformatwhite.minutes)+" : "+QString::number(timeformatwhite.seconds));
    label->setAlignment( Qt::AlignLeft);
    label->setFixedSize(QSize(230,200));
    label->frameSize()=QSize();
    label->move(QPoint(50,50));
    label->show();
    return;

}

void timer::setup()
{
    if(((this->timeformatblack.minutes==0
        &&this->timeformatblack.seconds==0)
            ||(this->timeformatwhite.minutes==0
               &&this->timeformatwhite.seconds==0))
            && time_up==0
            ){
        ++time_up;
        time->stop();
        emit timeup();
    }
    else return;
}

void timer::decrease()
{
      if (*move==13){
          if(timeformatwhite.minutes!=0 ||timeformatwhite.seconds!=0)
    --timeformatwhite.seconds;
    if(timeformatwhite.seconds<0&&timeformatwhite.minutes!=0){
        timeformatwhite.minutes--;
        timeformatwhite.seconds+=60;

        return;
    }
    }
    else if(*move==14){
          if(timeformatblack.minutes!=0||timeformatblack.seconds!=0)
        --timeformatblack.seconds;
        if(timeformatblack.seconds<0&&timeformatblack.minutes!=0){
            --timeformatblack.minutes;
            timeformatblack.seconds+=60;

        return;
    }

}
}
