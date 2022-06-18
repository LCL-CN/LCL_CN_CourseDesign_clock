#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QCloseEvent>
#include"countdown_timer.h"
#include"forward_timer.h"
#include"pointer_clock.h"
#include"digital_clock.h"
#include<QKeyEvent>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*event);
    void keyPressEvent(QKeyEvent *ev);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSoundEffect *bgm;
    Countdown_Timer *ct;
    Pointer_Clock *clock1;
    Digital_Clock* clock2;
    Forward_Timer *ft;
    QPushButton *btn;
    QPushButton *btn2;
};
#endif // DIALOG_H
