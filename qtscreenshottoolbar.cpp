#include "qtscreenshottoolbar.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

QtScreenShotToolBar::QtScreenShotToolBar(QWidget *parent) : QWidget(parent)
{
    //this->setGeometry(100,100,100,20);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    this->init();
    this->update();
}

void QtScreenShotToolBar::setPos(int x, int y)
{
    int curX = x- 100;
    if(curX<0)
    {
        curX = 0;
    }
    this->setGeometry(curX,y,100,20);
    this->update();
}

void QtScreenShotToolBar::setMode(int mode)
{

    bChosen[mode] = true;
    resetChosen(mode);
    qDebug()<<mode<<bChosen[mode];
    qDebug()<<"ready to update";
    this->update();
}

void QtScreenShotToolBar::init()
{
    //this->setGeometry(100,100,100,20);
    for(int i=0;i<5;i++)
    {
        bChosen[i] = false;
    }
//    this->set
}

void QtScreenShotToolBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    qDebug()<<"painting!";
    for(int i=0;i<5;i++)
    {
        qDebug()<<bChosen[i];
    }
    QColor bgcolor(81,162,249);
    QColor darkColor(0,118,246);
    QColor penColor(0,50,100);
    /*绘制圆角四四边形的底*/
    /**/
    painter.setPen(QPen(penColor));
    painter.setBrush(QBrush(bgcolor));
    painter.drawRect(0,0,100,20);

    /*绘制五个图形*/
    /*绘制第一个区域的长方体*/
    /**/
    QRect recRect = QRect(3,4,14,12);
    QRect bgRect = QRect(0,0,20,20);
    //qDebug()<<recRect;
    if(bChosen[0])
    {
        painter.setBrush(QBrush(darkColor));
    }
    else
    {
        painter.setBrush(QBrush(bgcolor));
    }
    painter.drawRect(bgRect);
    painter.drawRect(recRect);

    /*绘制第二个区域的圆形*/
    /**/
    if(bChosen[1])
    {
        painter.setBrush(QBrush(darkColor));
    }
    else
    {
        painter.setBrush(QBrush(bgcolor));
    }
    bgRect.setX(bgRect.x() + 20);
    bgRect.setWidth(20);
    painter.drawRect(bgRect);
    recRect.setX(recRect.x()+20);
    recRect.setWidth(14);
    //qDebug()<<recRect;
    painter.drawRoundedRect(recRect,10,5);

    /*绘制第三个区域的图形*/
    /**/
    if(bChosen[2])
    {
        painter.setBrush(QBrush(darkColor));
    }
    else
    {
        painter.setBrush(QBrush(bgcolor));
    }
    bgRect.setX(bgRect.x() + 20);
    bgRect.setWidth(20);
    painter.drawRect(bgRect);
    recRect.setX(recRect.x()+20);
    recRect.setWidth(14);
    painter.drawLine(recRect.x()+1,recRect.y()+6,recRect.x()+13,recRect.y()+6);
    painter.drawLine(recRect.x()+1,recRect.y()+6,recRect.x()+6,recRect.y() + 3);
    painter.drawLine(recRect.x()+1,recRect.y()+6,recRect.x()+6,recRect.y() + 9);

    /*绘制第四个区域的图形*/
    /**/
    if(bChosen[3])
    {
        painter.setBrush(QBrush(darkColor));
    }
    else
    {
        painter.setBrush(QBrush(bgcolor));
    }
    bgRect.setX(bgRect.x() + 20);
    bgRect.setWidth(20);
    painter.drawRect(bgRect);
    recRect.setX(recRect.x()+20);
    recRect.setWidth(14);
    //qDebug()<<recRect;
    painter.drawLine(recRect.x() + 2,recRect.y()+6,recRect.x()+5,recRect.y()+11);
    painter.drawLine(recRect.x()+5,recRect.y()+11,recRect.x()+13,recRect.y()+3);

    /*绘制第五个区域的图形*/
    /**/
    if(bChosen[4])
    {
        painter.setBrush(QBrush(darkColor));
    }
    else
    {
        painter.setBrush(QBrush(bgcolor));
    }
    bgRect.setX(bgRect.x() + 20);
    bgRect.setWidth(20);
    painter.drawRect(bgRect);
    recRect.setX(recRect.x()+20);
    recRect.setWidth(14);
   // qDebug()<<recRect;
    painter.drawLine(recRect.x()+1,recRect.y()+1,recRect.x()+12,recRect.y()+12);
    painter.drawLine(recRect.x()+12,recRect.y()+1,recRect.x()+1,recRect.y()+12);

    /*绘制四条个竖线*/
    /**/
    painter.setPen(QPen(penColor));
    painter.setBrush(QBrush(darkColor));
    for(int i =1;i<5;i++)
    {
        painter.drawLine(0+ i*20,0 + 0 ,0+i*20, 20);
    }

}

void QtScreenShotToolBar::mouseReleaseEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    if(pt.y()<0 || pt.y()>20)
    {
        return;
    }
    int chosenNum = 0;
    if(pt.x() < 0)
    {
        return;
    }
    else if(pt.x() < 20)
    {
        chosenNum = 0;
    }
    else if(pt.x() < 40)
    {
        chosenNum = 1;
    }
    else if(pt.x() < 60)
    {
        chosenNum = 2;
    }
    else if(pt.x() < 80)
    {
        chosenNum = 3;
    }
    else if(pt.x()<100)
    {
        chosenNum = 4;
    }
    else{
        return;
    }
    bChosen[chosenNum] = !bChosen[chosenNum];
    if(bChosen[chosenNum] == true)
    {
        resetChosen(chosenNum);
        emit setDrawMode(chosenNum);
    }
    else
    {
        resetChosen(chosenNum);
        emit removeDrawMode(chosenNum);
    }
    if(chosenNum > 1)
    {
        bChosen[chosenNum] = false;
    }


    this->update();
}

void QtScreenShotToolBar::resetChosen(int num)
{
    for(int i=0; i<5;i++)
    {
        if(i != num)
        {
            bChosen[i] = false;
        }
    }
}
