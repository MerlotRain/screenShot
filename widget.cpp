#include "widget.h"
#include "ui_widget.h"
#include "qtscreenshot.h"
#include <QDesktopWidget>
#include <QLabel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->hide();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QDesktopWidget* deskTop = QApplication::desktop();
    int curMonitor = deskTop->screenNumber(this);
    st = new QtScreenShot(curMonitor,this);
    st->setParent(this);
    connect(st,SIGNAL(onScreenShotOK()),this,SLOT(closeScreenShot()));
    st->exec();
}

void Widget::closeScreenShot()
{
    QImage image = st->getScreenShotImage();
    image = image.scaled(ui->label_1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap im = QPixmap::fromImage(image);
    ui->label_1->setPixmap(im);
    st->accept();
}

