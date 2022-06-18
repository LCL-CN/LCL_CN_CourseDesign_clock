#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

#include <QWidget>
#include <QMainWindow>
#include<QPushButton>
#include<QLCDNumber>//电子显示屏
class Digital_Clock : public QWidget
{
    Q_OBJECT
public:
    explicit Digital_Clock(QWidget *parent = nullptr);
    void sentsignal();

public slots:
    void showtime();//显示电子显示器时间
signals:

private:

    QLCDNumber *lcd;//电子显示屏

};

#endif // DIGITAL_CLOCK_H
