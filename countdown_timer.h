#ifndef COUNTDOWN_TIMER_H
#define COUNTDOWN_TIMER_H

#include <QWidget>
#include <QTimer>
#include<QKeyEvent>
#include<QPushButton>
#include<QLCDNumber>
#include<QTimeEdit>
#include<QSoundEffect>
#include<QCloseEvent>

class Countdown_Timer : public QWidget
{
    Q_OBJECT
public:
    QSoundEffect *bgm;
    void closeEvent(QCloseEvent*event){
       // on_pushButton_clicked();
            pausef=!pausef;
    }
    explicit Countdown_Timer(QWidget *parent = nullptr);
    QPushButton *btn4;
    void keyPressEvent(QKeyEvent *ev);
signals:
private:
    QSoundEffect *overbgm;
    QPushButton *pushButton;
    QPushButton *btnReset;
    QLCDNumber *lcdNumber;
    QTimer *timer;
    QTimeEdit *timeEdit;
    void timeoutRun(void);
    int hour=12,min=0,sec=0;
    int mms,mhour=11,mmin=59,msec=59;
    int a=0;
    int cmms;

    void Delay_MSec(unsigned int msec);//延迟计时

    bool pausef=0,resetf=0;
private slots:
    void on_pushButton_clicked();

    void on_btnReset_clicked();


};

#endif // COUNTDOWN_TIMER_H
