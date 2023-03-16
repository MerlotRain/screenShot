#ifndef QTSCREENSHOT_H
#define QTSCREENSHOT_H
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QPoint>
#include <QScreen>
#include <QMouseEvent>
#include "qtscreenshottoolbar.h"
#include "qtscreenshoteditarea.h"
#include "drawingoperationstack.h"
class QtScreenShot :public QDialog
{
    Q_OBJECT

public:

public:
    explicit QtScreenShot(int curScreen, QWidget* parent = nullptr);

    void init(int curScreen);
    void ShowToolBar();
    void paintEvent(QPaintEvent* event);
    QImage getScreenShotImage();
    QImage getFullScreenImage();
    void closeAll();
    bool hasGotImage;
public slots:
    void onDrawModeSet(int mode);
    void onDrawModeRemove(int mode);
    void onGetOperation(DrawingOperation op);
    //void reject();
protected:
    void mousePressEvent(QMouseEvent* e);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* e);//鼠标按下后移动事件
    void mouseReleaseEvent(QMouseEvent* e);//鼠标按下后抬起事件

private:
    QScreen* baseScreen;//屏幕截图
    QRect selectArea;//选中截图区域大小（相对）
    QRect globalSelectArea;
    QRect selectTempArea;//选中背景/模板大小（相对）
    QRect globalTempArea;
    QRect selectRecogArea;//选中的前景/识别区域大小（相对）
    QRect globalSelectRecogArea;
    QtScreenShotToolBar *toolBar;//截图工具栏
    QtScreenShotEditArea *editArea;//截图编辑界面
    QPoint startPoint;
    QPoint startGlobalPoint;
    QImage baseImage;
    DrawingOperationStack operationStack;
    int curMode;
    int curScreen;
    QImage ansImage;
private:
    QImage getSelectImage(int x, int y, int width, int height);
    void bindSignalSlots();
    QImage AdjustBrightness(QImage Img, int iBrightValue);
    void AutoUnOperation(DrawingOperation delOperation, DrawingOperation curOperation);
    bool hasArea;

signals:
    void onScreenShotOK();
};

#endif // QTSCREENSHOT_H
