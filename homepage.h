#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include<QWidget>
#include<QPushButton>
class homepage:public QWidget
{
    Q_OBJECT

public:
    homepage(QWidget* parent= nullptr);
    QPushButton *play;
    QPushButton *settings;
    QPushButton *instructions;
    QPushButton *exit;


};

#endif // HOMEPAGE_H
