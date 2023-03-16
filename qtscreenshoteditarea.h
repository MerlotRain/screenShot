#ifndef QTSCREENSHOTEDITAREA_H
#define QTSCREENSHOTEDITAREA_H

#include <QObject>
#include <QWidget>
#include "drawingoperationstack.h"
class QtScreenShotEditArea : public QWidget
{
    Q_OBJECT
public:
    explicit QtScreenShotEditArea(QWidget *parent = nullptr);

    void setBgImage(QImage &image);
    void paintEvent(QPaintEvent *event);
    void setMode(int mode);
    void setOpRect(QRect rectR,QRect rectT);
    QImage getImage();
protected:
    void mousePressEvent(QMouseEvent *e);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent *e);//鼠标按下后移动事件
    void mouseReleaseEvent(QMouseEvent *e);//鼠标按下后抬起事件
private:
    QRect tempRect;
    QPoint startPoint;
    QRect recogRect;
    QImage bgImage;
    int curMode;
signals:
    void emitOperation(DrawingOperation op);
};

#endif // QTSCREENSHOTEDITAREA_H
