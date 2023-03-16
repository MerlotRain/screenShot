#include "qtscreenshot.h"
#include <QGuiApplication>
#include <QPainter>
#include <QImage>
#include <QSize>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
QtScreenShot::QtScreenShot(int curScreen, QWidget* parent) :
    QDialog(parent)
{
    this->init(curScreen);

}

void QtScreenShot::init(int curScreen)
{
    this->selectArea = QRect(-1, -1, -1, -1);
    this->selectRecogArea = QRect(-1, -1, -1, -1);
    this->selectTempArea = QRect(-1, -1, -1, -1);
    QList<QScreen*> screens = QGuiApplication::screens();
    qDebug() << screens.size();

    qDebug() << curScreen;
    this->baseScreen = screens.at(curScreen);
    QRect rectCurWin = this->baseScreen->geometry();;
    qDebug() << rectCurWin;
    QSize siz = this->baseScreen->size();
    this->setGeometry(rectCurWin);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    this->hasGotImage = false;
    this->editArea = new QtScreenShotEditArea(this);
    this->editArea->hide();
    this->toolBar = new QtScreenShotToolBar(this);
    this->toolBar->hide();

    this->baseImage = baseScreen->grabWindow(0).toImage();
    this->curMode = -1;
    this->hasArea = false;
    this->bindSignalSlots();
}

void QtScreenShot::bindSignalSlots()
{
    connect(toolBar, SIGNAL(setDrawMode(int)), this, SLOT(onDrawModeSet(int)));
    connect(toolBar, SIGNAL(removeDrawMode(int)), this, SLOT(onDrawModeRemove(int)));
    connect(editArea, SIGNAL(emitOperation(DrawingOperation)), this, SLOT(onGetOperation(DrawingOperation)));
}

QImage QtScreenShot::AdjustBrightness(QImage Img, int iBrightValue)
{
    int red, green, blue;
    int pixels = Img.width() * Img.height();
    unsigned int* data = (unsigned int*)Img.bits();

    for (int i = 0; i < pixels; ++i)
    {
        red = qRed(data[i]) + iBrightValue;
        red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
        green = qGreen(data[i]) + iBrightValue;
        green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
        blue = qBlue(data[i]) + iBrightValue;
        blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;
        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }

    return Img;

}

void QtScreenShot::AutoUnOperation(DrawingOperation delOperation, DrawingOperation curOperation)
{
    /**/
    /**/
    if (delOperation.curMode == -1)
    {
        this->hasArea = false;
        editArea->hide();
        toolBar->hide();
    }
    else
    {
        /*无论什么操作，先清空*/
        /**/
        QRect rect(0, 0, 0, 0);
        editArea->setOpRect(rect, rect);
        editArea->setMode(-1);
        /*可还原再还原*/
        /**/
        if (curOperation.curMode != -1)
        {
            editArea->setMode(curOperation.curMode);
            editArea->setOpRect(curOperation.recogRect, curOperation.tempRect);
            this->toolBar->setMode(curOperation.curMode);
        }
    }

}
void QtScreenShot::ShowToolBar()
{

}

void QtScreenShot::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage image = getFullScreenImage();
    image = AdjustBrightness(image, -30);
    painter.drawImage(0, 0, image);
}

QImage QtScreenShot::getScreenShotImage()
{
    QImage pixmap = this->editArea->getImage();
    this->ansImage = pixmap;
    return this->ansImage;
}

QImage QtScreenShot::getFullScreenImage()
{
    return baseImage;
}

void QtScreenShot::closeAll()
{
    while (!operationStack.isEmptyStack())
    {
        operationStack.popStack();
    }

}

void QtScreenShot::onDrawModeSet(int mode)
{
    curMode = mode;
    if (mode < 0)
    {
        return;
    }
    else if (mode < 2)
    {
        this->editArea->setMode(mode);
    }
    else if (mode == 2)
    {
        qDebug() << "in redo ";
        DrawingOperation op = operationStack.popStack();
        DrawingOperation op2 = operationStack.getCurOperation();
        AutoUnOperation(op, op2);
    }
    else if (mode == 3)
    {
        emit onScreenShotOK();

    }
    else if (mode == 4)
    {
        this->closeAll();
        this->accept();
    }
    else
    {
        return;
    }

}

void QtScreenShot::onDrawModeRemove(int mode)
{
    curMode = -1;
    if (mode < 0)
    {
        return;
    }
    else if (mode < 2)
    {
        this->editArea->setMode(-1);
    }
    else if (mode == 2)
    {

    }
    else if (mode == 3)
    {
        emit onScreenShotOK();
    }
    else if (mode == 4)
    {

    }
    else
    {
        return;
    }
}

void QtScreenShot::onGetOperation(DrawingOperation op)
{
    this->operationStack.pushInStack(op.curMode, op.recogRect, op.tempRect);
}

void QtScreenShot::mousePressEvent(QMouseEvent* e)
{
    this->startPoint = e->pos();
    this->startGlobalPoint = e->globalPos();
}

void QtScreenShot::mouseMoveEvent(QMouseEvent* e)
{
    QPoint curPoint;
    curPoint = e->pos();
    //qDebug() << "move";
    if (hasArea)
    {
        qDebug() << "return";
        return;
    }
    int posX = startPoint.x();
    int posY = startPoint.y();
    int posWid = curPoint.x() - startPoint.x();
    int posHig = curPoint.y() - startPoint.y();

    this->editArea->setGeometry(posX, posY, posWid, posHig);
    QImage ima = this->getSelectImage(posX, posY, posWid, posHig);
    this->editArea->setBgImage(ima);
    this->editArea->show();
    //qDebug() << "showarea in move";
}

void QtScreenShot::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton)
    {
        closeAll();
        this->accept();
        return;
    }
    if (hasArea)
    {
        qDebug() << "return";
        return;
    }
    QPoint curPoint;
    curPoint = e->pos();
    int posX = startPoint.x();
    int posY = startPoint.y();
    int posWid = curPoint.x() - startPoint.x();
    int posHig = curPoint.y() - startPoint.y();

    QPoint glcurPoint;
    glcurPoint = e->globalPos();
    this->globalSelectArea.setRect(startGlobalPoint.x(), startGlobalPoint.y(), glcurPoint.x() - startGlobalPoint.x(), glcurPoint.y() - startGlobalPoint.y());
    this->editArea->setGeometry(posX, posY, posWid, posHig);
    QImage ima = this->getSelectImage(posX, posY, posWid, posHig);
    this->editArea->setBgImage(ima);
    this->editArea->show();
    this->toolBar->setPos(curPoint.x(), curPoint.y());
    this->toolBar->show();
    this->hasArea = true;
    qDebug() << startPoint << curPoint;
    qDebug() << "showarea in release";
}

QImage QtScreenShot::getSelectImage(int x, int y, int width, int height)
{
    QImage pixmap = baseImage;

    return pixmap.copy(x, y, width, height);
}

