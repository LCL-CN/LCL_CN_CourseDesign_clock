#ifndef FORWARD_TIMER_H
#define FORWARD_TIMER_H

#include <QWidget>
#include<QTimer>
#include<QLCDNumber>
#include<QPushButton>
#include<QKeyEvent>
#include<QKeyEvent>
#include<QSoundEffect>
#include<QCloseEvent>
class Forward_Timer : public QWidget
{
    Q_OBJECT
public:
    explicit Forward_Timer(QWidget *parent = nullptr);
    QSoundEffect *bgm;
    void closeEvent(QCloseEvent*event){
        emit qpushButton_2.clicked();

    }
    void keyPressEvent(QKeyEvent *ev);



signals:

private:
    QPushButton  qpushButton;
    QPushButton  qpushButton_2;
    QTimer * timer;
    QLCDNumber * lcdNumber;


};

#endif // FORWARD_TIMER_H
