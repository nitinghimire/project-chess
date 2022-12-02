#ifndef TIMER_H
#define TIMER_H
#include<QTimer>
#include<QLabel>
#include <QWidget>

class timer: public QWidget
{
    Q_OBJECT
public:
    timer(QWidget *parent);
    void settime(int timeformat);
    struct actual_time{
        int minutes;
        int seconds;
    };
    void reset();

 public   slots:
    void decrease();
    void display();
    void setup();
signals:
    void timeup();

public:
    actual_time timeformatwhite;
    actual_time timeformatblack;
    QTimer *time;
    QWidget *parent;
    QLabel *label;
    int *move;
    int time_up=0;
};

#endif // TIMER_H
