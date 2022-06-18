#ifndef POINTER_CLOCK_H
#define POINTER_CLOCK_H

#include <QWidget>
#include<QSoundEffect>

class Pointer_Clock : public QWidget
{
    Q_OBJECT
public:
    QRectF textRectF(double radius, int pointSize, double angle);
    void paintEvent(QPaintEvent *event);
    explicit Pointer_Clock(QWidget *parent = nullptr);
    void didastop();
    void didaplay();

signals:
public slots:
    void musicdida();
private:
    QSoundEffect *dida=new QSoundEffect;
};

#endif // POINTER_CLOCK_H
