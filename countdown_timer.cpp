#include "countdown_timer.h"
#include<QKeyEvent>
#include<QDate>
#include<QCoreApplication>
#include<QEventLoop>
#include<QDateTime>
#include<QSoundEffect>
Countdown_Timer::Countdown_Timer(QWidget *parent)
    : QWidget{parent}
{
    btn4=new QPushButton;
    btn4->setParent(this);
    btn4->setStyleSheet("QPushButton{background-color: rgba(200,214,216,100);color:rgb(100,10,200);}");//设置按钮风格
    btn4->setText("<-返回时钟[&C]");
    btn4->move(720,400);

    bgm=new QSoundEffect;
    bgm->setParent(this);
    bgm->setSource(QUrl::fromLocalFile(":/c_bgm"));
    bgm->setVolume(0.6);//设置音量（最大为1）
    bgm->setLoopCount(1000);//循环次数

    overbgm=new QSoundEffect;
    overbgm->setParent(this);
    overbgm->setSource(QUrl::fromLocalFile(":/jieshu"));
    overbgm->setVolume(1);

    lcdNumber=new QLCDNumber(this);
    lcdNumber->setDigitCount(11);
    lcdNumber->resize(400,100);
    lcdNumber->move(260,300);
    lcdNumber->display("00:00:00:00");

    lcdNumber->setSegmentStyle(QLCDNumber::Filled);

    timer = new QTimer(this);

    pushButton=new QPushButton(this);
    pushButton->move(415,250);
    pushButton->setText("开始");
    pushButton->hide();
    pushButton->setStyleSheet("QPushButton{background-color: rgba(200,214,216,100);color:rgb(100,10,200);}");
    btnReset=new QPushButton(this);
    btnReset->move(415,100);
    btnReset->setText("重置[&B]");
    btnReset->setStyleSheet("QPushButton{background-color: rgba(200,214,216,100);color:rgb(100,10,200);}");
    timeEdit=new QTimeEdit(this);
    timeEdit->move(400,200);
    timeEdit->setFixedSize(100,30);
    timeEdit->setDisplayFormat("hh:mm:ss");
    on_btnReset_clicked();
    connect(timer,&QTimer::timeout,this,&Countdown_Timer::timeoutRun);//信号槽当按时间结束后运行自定义槽信号
    connect(pushButton,&QPushButton::clicked,this,&Countdown_Timer::on_pushButton_clicked);
    connect(btnReset,&QPushButton::clicked,this,&Countdown_Timer::on_btnReset_clicked);
    connect(btnReset,&QPushButton::clicked,this,[=](){pushButton->show();});
}
void Countdown_Timer:: keyPressEvent(QKeyEvent *ev){

    if(ev->key()==Qt::Key_A)
    {
        if(ev->isAutoRepeat()) return;

        emit pushButton->clicked();

    }
    if(ev->key()==Qt::Key_B)
    {
        if(ev->isAutoRepeat()) return;
        emit btnReset->clicked();

    }
    if(ev->key()==Qt::Key_C)
    {
        if(ev->isAutoRepeat()) return;
        emit btn4->clicked();

    }

}

void Countdown_Timer::timeoutRun()//pausef判断是否该倒计时
{
    if(pausef){
        //定时
        for(hour = mhour;hour>=0;hour--)
            for( min =mmin;min>=0 ;min--)
                for(sec=msec-1;sec>=0;sec--)

                    for(mms=99;mms>=0;mms--)
                    {

                        lcdNumber->display(QDateTime::currentDateTime().toString(
                                                   QString("%1").arg(hour, 2, 10, QChar('0'))+":"+
                                                   QString("%1").arg(min, 2, 10, QChar('0'))+":"+
                                                   QString("%1").arg(sec, 2, 10, QChar('0')))+":"+
                                                   QString("%1").arg(mms, 2, 10, QChar('0')));
                        Delay_MSec(10);//延时毫秒,而不是用start函数来计时

                        if(min>0 && sec==0)
                            msec=59;
                        if(hour>0 && min==0)
                            mmin=59;
                        if(!pausef )//未开始时
                        {
                            if(!resetf) //被重置后不记录当前时间位置
                            {
                                mhour=hour;
                                mmin=min;
                                msec=sec;
                            }
                            return;
                        }
                    }

        timer->stop();//让time start只进行一次，只作为一个信号传递 不作为时间的叠加
        bgm->stop();//标志着倒计时结束。
        overbgm->play();
        on_pushButton_clicked();
    }


}

void Countdown_Timer::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < _Timer ){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);

    }

}

void Countdown_Timer::on_pushButton_clicked()//开始
{
    resetf=0;//持续更新时分秒

    pausef=!pausef;//psusef变为1
    if(pausef)
    {
        timer->start(0);//开始标志
        pushButton->setText("暂停[&A]");
        bgm->play();
    }
    else
    {
        pushButton->setText("开始[&A]");
        timer->stop();//暂停
        bgm->stop();
    }
}

void Countdown_Timer::on_btnReset_clicked()//重置
{
    pausef=0;
    resetf=1; //重置标志，不会使时分秒更新
    timer->stop();

    pushButton->setText("开始[&A]");
    bgm->stop();

    mhour=timeEdit->time().hour();
    msec=timeEdit->time().second();
    mmin=timeEdit->time().minute();


    lcdNumber->display(QDateTime::currentDateTime().toString(
                               QString("%1").arg(mhour, 2, 10, QChar('0'))+":"+
                               QString("%1").arg(mmin, 2, 10, QChar('0'))+":"+
                               QString("%1").arg(msec, 2, 10, QChar('0')))+":"+"00");

}

