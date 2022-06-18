#include "forward_timer.h"
#include<QTime>
#include<QKeyEvent>


Forward_Timer::Forward_Timer(QWidget *parent)
    : QWidget{parent}
{
    bgm=new QSoundEffect;
    bgm->setParent(this);
    bgm->setSource(QUrl::fromLocalFile(":/c_bgm"));//设置资源文件
    bgm->setVolume(0.6);//设置音量（最大为1）
    bgm->setLoopCount(1000);//循环次数

    qpushButton.setParent(this);
    qpushButton.move(360,100);
    qpushButton.setText("开始[&A]");
    qpushButton.setStyleSheet("QPushButton{background-color: rgba(20,214,216,60);color:rgb(100,50,20);}");//设置按钮风格

    qpushButton_2.setParent(this);
    qpushButton_2.setText("清零[&B]");
    qpushButton_2.setStyleSheet("QPushButton{background-color: rgba(20,214,216,60);color:rgb(100,50,20);}");//设置按钮风格
    qpushButton_2.move(460,100);
    lcdNumber=new QLCDNumber;
    lcdNumber->setSegmentStyle(QLCDNumber::Filled);//设置显示器风格
    lcdNumber->setParent(this);
    lcdNumber->resize(400,100);
    lcdNumber->move(260,200);
    lcdNumber->setDigitCount(11);

    timer=new QTimer(this);


    lcdNumber->display("00:00:00:00");

    connect(&qpushButton,&QPushButton::clicked,this,[=](){
        if(qpushButton.text()=="开始[&A]"||qpushButton.text()=="继续[&A]"){
        timer->start(10);
        bgm->play();
        qpushButton.setText("暂停[&A]");
        }
        else{
            timer->stop();
            bgm->stop();
            qpushButton.setText("继续[&A]");
        }

    });


        static int num=0;
        static int hour=0;
        static int min=0;
        static int sec=0;

    connect(timer,&QTimer::timeout,this,[=](){

        num++;
        hour=(num/360000);
        min=(num/60000)%60;
        sec=(num/100)%60;
        lcdNumber->display(
                    "0"+QString::number(hour)+":"
                    +(min>9?QString::number(min):("0"+QString::number(min)))+":"
                    +(sec>9?QString::number(sec):("0"+QString::number(sec)))+":"
                    +((num%100)>9?QString::number(num%100):("0"+QString::number(num%100))));



    });



    connect(&qpushButton_2,&QPushButton::clicked,[=](){
        timer->stop();
        lcdNumber->display("00:00:00:00");
        num=0;
        bgm->stop();
        qpushButton.setText("开始[&A]");
    });

}
void Forward_Timer::keyPressEvent(QKeyEvent*ev){
    if(ev->key()==Qt::Key_A){
        emit qpushButton.clicked();
    }
    if(ev->key()==Qt::Key_B){
        emit qpushButton_2.clicked();
    }
}



