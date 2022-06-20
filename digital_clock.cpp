#include "digital_clock.h"

#include<QTime>
#include<QTimer>
#include<QLCDNumber>
#include<QPainter>



Digital_Clock::Digital_Clock(QWidget *parent)
    : QWidget{parent}
{

    QTimer *timer1=new QTimer(this);
    timer1->start(100);
    connect(timer1,SIGNAL(timeout()),this,SLOT(showtime()));
    lcd=new QLCDNumber();
    lcd->setSegmentStyle(QLCDNumber::Filled);
    lcd->setParent(this);
    lcd->move(350,160);
    lcd->setDigitCount(11);
    lcd->resize(200,50);
    lcd->setStyleSheet("QLCDNumber{background-color: rgba(0, 160, 160, 200);}");
    showtime();
}

void Digital_Clock::showtime()
{
    QTime time1=QTime::currentTime();
    QString text=time1.toString("hh:mm:ss");
    int timee=time1.msec();
    QString text2=QString::number(timee/10);
    //控制显示位数
    if((timee/10)<10){
        text2="0"+text2;
    }
    text=text+":"+text2;//得到最终显示字符串
    lcd->display(text);
}


