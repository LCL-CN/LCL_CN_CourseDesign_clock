#include "pointer_clock.h"
#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QSoundEffect>

Pointer_Clock::Pointer_Clock(QWidget *parent)
    : QWidget{parent}
{

        QTimer *timer = new QTimer(this);
        dida->setVolume(1);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        connect(timer, SIGNAL(timeout()), this, SLOT(musicdida()));
        timer->start(1000);



}
QRectF Pointer_Clock::textRectF(double radius, int pointSize, double angle)
{
    QRectF rectF;
    rectF.setX(radius*qCos(angle*M_PI/180.0) - pointSize*2);
    rectF.setY(radius*qSin(angle*M_PI/180.0) - pointSize/2.0);
    rectF.setWidth(pointSize*4);
    rectF.setHeight(pointSize);
    return rectF;
}
void Pointer_Clock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 时针、分针、秒针位置 - 多边形
    static const QPoint hourHand[4] = {

        QPoint(4, 0),
        QPoint(0,8),
        QPoint(-4, 0),
        QPoint(0, -36)
    };
    static const QPoint minuteHand[4] = {
        QPoint(3, 0),
        QPoint(0,9),
        QPoint(-3, 0),
        QPoint(0, -64)
    };

    static const QPoint secondHand[4] = {
        QPoint(2, 0),
        QPoint(0,10),
        QPoint(-2, 0),
        QPoint(0, -81)
    };

    // 时针、分针、秒针颜色
    QColor hourColor(50, 200, 100, 200);
    QColor minuteColor(0, 160, 160, 200);
    QColor secondColor(0, 160, 230, 150);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);//绘图
    painter.setRenderHint(QPainter::Antialiasing);
    // 平移坐标系原点至中心点
    painter.translate(width() / 2, height() / 2);
    // 缩放
    painter.scale(side / 200.0, side / 200.0);

    // 绘制时针
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);//笔刷颜色

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();

    painter.setPen(hourColor);

    // 绘制小时线
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    int radius = 100;
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    int pointSize = font.pointSize();

    // 绘制小时文本
    int nHour = 0;
    for (int i = 0; i < 12; ++i) {
        nHour = i + 3;
        if (nHour > 12)
            nHour -= 12;
        painter.drawText(textRectF(radius*0.8, pointSize, i * 30), Qt::AlignCenter, QString::number(nHour));
    }

    // 绘制分针
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();

    painter.setPen(minuteColor);

    // 绘制分钟线
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

    // 绘制秒针
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);



    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 4);
    painter.restore();


}
void Pointer_Clock::musicdida(){

    dida->setParent(this);
    dida->setSource(QUrl::fromLocalFile(":/dida"));

    dida ->play();
}
void Pointer_Clock::didastop(){
    dida->setVolume(0);
}
void Pointer_Clock::didaplay(){
    dida->setVolume(1);
}
