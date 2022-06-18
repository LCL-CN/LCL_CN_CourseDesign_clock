#include "dialog.h"
#include "ui_dialog.h"
#include"pointer_clock.h"
#include"digital_clock.h"
#include"forward_timer.h"
#include"countdown_timer.h"
#include<QPainter>
#include<QPalette>
#include<QSoundEffect>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/s6"));

    //设置背景音乐
    bgm=new QSoundEffect;
    bgm->setParent(this);
    bgm->setSource(QUrl::fromLocalFile(":/bgm1"));
    bgm->setVolume(0.24);
    bgm->setLoopCount(1000);
    bgm->play();


    this->setFixedSize(900,600);

    this->grabKeyboard();

    clock1=new Pointer_Clock;//指针时钟对象
    clock2=new Digital_Clock;//电子显示器时钟
    clock1->setParent(this);
    clock2->setParent(this);
    clock1->move(135,50);

    //设置背景
    QPixmap pixmap = QPixmap(":/y6").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    QPixmap pixmap2=QPixmap(":/s9").scaled(this->size());
    QPalette palette2(this->palette());
    palette2.setBrush(QPalette::Window, QBrush(pixmap2));
    this->setPalette(palette);

    //正向计时器对象
    ft=new Forward_Timer(this);
    ft->hide();
    ft->setAttribute(Qt::WA_DeleteOnClose);

    //倒计时器对象
    ct=new Countdown_Timer(this);
    ct->hide();
    ct->setAttribute(Qt::WA_DeleteOnClose);

    //切换按钮1
    btn=new QPushButton;
    btn->setParent(this);
    btn->setStyleSheet("QPushButton{background-color: rgba(200,214,216,100);color:rgb(100,10,200);}");//设置按钮风格
    btn->setText("正向计时器[&F]->");
    btn->move(720,360);

    //切换按钮2
    btn2=new QPushButton;
    btn2->setParent(this);
    btn2->setStyleSheet("QPushButton{background-color: rgba(200,214,216,100);color:rgb(100,10,200);}");//设置按钮风格
    btn2->setText("倒计时器[&C]->");
    btn2->move(720,400);
    connect(btn,&QPushButton::clicked,this,[=](){

    });

    //切换到正向计时器
    connect(btn,&QPushButton::clicked,this,[=](){
        if(btn->text()=="正向计时器[&F]->"){
            clock1->hide();
            clock2->hide();
            ct->hide();
            ft->show();
            ft->bgm->setVolume(0.6);
            clock1->didastop();
            this->setPalette(palette2);
            btn->setText("<-返回时钟[&F]");
            btn2->hide();
            ft->grabKeyboard();
            bgm->setVolume(0);
        }
        else{
            ft->hide();
            clock1->show();
            clock2->show();
            ct->hide();
            bgm->setVolume(0.24);
            clock1->didaplay();
            ft->bgm->setVolume(0);
            this->setPalette(palette);
            btn->setText("正向计时器[&F]->");
            this->grabKeyboard();
            btn2->show();
        }
    });

    //切换到倒计时器
    connect(btn2,&QPushButton::clicked,this,[=](){
        if(btn2->text()=="倒计时器[&C]->"){
            clock1->hide();
            clock2->hide();
            ft->hide();
            ct->show();
            ct->bgm->setVolume(0.6);
            clock1->didastop();
            this->setPalette(palette2);
            btn2->setText("<-返回时钟[&C]");
            ct->grabKeyboard();
            btn->hide();
            bgm->setVolume(0);
        }
        else{
            ct->hide();
            clock1->show();
            clock2->show();
            ft->hide();
            bgm->setVolume(0.24);
            clock1->didaplay();
            ct->bgm->setVolume(0);
            this->setPalette(palette);
            this->grabKeyboard();
            btn2->setText("倒计时器[&C]->");
            btn->show();
        }
    });


}


Dialog::~Dialog()
{
    delete ui;

}
void Dialog::closeEvent(QCloseEvent *event){
   delete bgm;
   ct->close();
}
void Dialog::keyPressEvent(QKeyEvent *ev){
    if(ev->key()==Qt::Key_F){
        emit btn->clicked();
    }
    if(ev->key()==Qt::Key_C){
        emit btn2->clicked();
    }
}

