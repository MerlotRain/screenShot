#include "qtscreenshoteditarea.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QDebug>
QtScreenShotEditArea::QtScreenShotEditArea(QWidget *parent) : QWidget(parent)
{
    this->recogRect = QRect(0,0,0,0);
    this->tempRect = QRect(0,0,0,0);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    bgImage = QImage(0,0,QImage::Format_RGB32);
    setAttribute(Qt::WA_TranslucentBackground, true);
    curMode = -1;

}

void QtScreenShotEditArea::setBgImage(QImage &image)
{
    this->bgImage = image;
    this->update();
}

void QtScreenShotEditArea::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     if(bgImage.size().width() == 0 && bgImage.size().height() == 0)
     {
         return;
     }
     QPoint pt(0,0);
     QColor recogColor(223,80,80);
     QColor tempColor(0,137,255);
     painter.drawImage(pt,bgImage);
     if(recogRect.width() != 0 && recogRect.height() != 0)
     {
         QPoint pt1(recogRect.x(),recogRect.y());
         QPoint pt2(recogRect.x(),recogRect.y() + recogRect.height());
         QPoint pt3(recogRect.x() + recogRect.width(), recogRect.y() + recogRect.height());
         QPoint pt4(recogRect.x() + recogRect.width(), recogRect.y());
         painter.setPen(QPen(recogColor));
         painter.drawLine(pt1,pt2);
         painter.drawLine(pt2,pt3);
         painter.drawLine(pt3,pt4);
         painter.drawLine(pt4,pt1);
     }

     if(tempRect.width() !=0 &&tempRect.height() != 0)
     {
         QPoint pt1(tempRect.x(),tempRect.y());
         QPoint pt2(tempRect.x(),tempRect.y() + tempRect.height());
         QPoint pt3(tempRect.x() + tempRect.width(), tempRect.y() + tempRect.height());
         QPoint pt4(tempRect.x() + tempRect.width(), tempRect.y());
         painter.setPen(QPen(tempColor));
         painter.drawLine(pt1,pt2);
         painter.drawLine(pt2,pt3);
         painter.drawLine(pt3,pt4);
         painter.drawLine(pt4,pt1);
     }

}

void QtScreenShotEditArea::setMode(int mode)
{
    curMode = mode;
}

void QtScreenShotEditArea::setOpRect(QRect rectR,QRect rectT)
{

    this->tempRect = rectT;

    this->recogRect = rectR;
    //qDebug()<<this->tempRect<<this->recogRect;
    this->update();
}

QImage QtScreenShotEditArea::getImage()
{
    QImage image;
    QPixmap pix;
    pix = this->grab(QRect(0,0,this->width(),this->height()));
    image = pix.toImage();

    return image;
}

void QtScreenShotEditArea::mousePressEvent(QMouseEvent *e)
{
    this->startPoint = e->pos();
}

void QtScreenShotEditArea::mouseMoveEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    QRect curRect = QRect(startPoint.x(),startPoint.y(), pt.x() - startPoint.x(), pt.y() - startPoint.y());
    if(curMode ==0)
    {
        this->recogRect = curRect;
    }
    if(curMode == 1)
    {
        this->tempRect = curRect;
    }
    this->update();
}

void QtScreenShotEditArea::mouseReleaseEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    QRect curRect = QRect(startPoint.x(),startPoint.y(), pt.x() - startPoint.x(), pt.y() - startPoint.y());
    DrawingOperation op;
    op.curMode =curMode;
    if(curMode == -1)
    {
        return;
    }
    if(curMode ==0)
    {
        this->recogRect = curRect;

    }
    if(curMode == 1)
    {
        this->tempRect = curRect;
    }
    op.recogRect = this->recogRect;
    op.tempRect = this->tempRect;
    //qDebug()<<op.curMode<<op.recogRect<<op.tempRect;
    emit emitOperation(op);
    this->update();
}
