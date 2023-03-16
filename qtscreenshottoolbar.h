#ifndef QTSCREENSHOTTOOLBAR_H
#define QTSCREENSHOTTOOLBAR_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
class QtScreenShotToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit QtScreenShotToolBar(QWidget *parent = nullptr);

    void setPos(int x, int y);
    void setMode(int mode);
    void init();

    void paintEvent(QPaintEvent *event);
    void resetChosen(int num);
protected:
    void mouseReleaseEvent(QMouseEvent *e);//鼠标按下后抬起事件

private:
    bool bChosen[5];
signals:
    void setDrawMode(int mode);
    void removeDrawMode(int mode);
};

#endif // QTSCREENSHOTTOOLBAR_H
