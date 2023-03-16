#include "drawingoperationstack.h"
#include <QDebug>
DrawingOperationStack::DrawingOperationStack()
{
    this->stack.clear();
}

void DrawingOperationStack::pushInStack(int curMode, QRect rectr, QRect rectt)
{
    DrawingOperation *st;
    st = new DrawingOperation;
    st->curMode = curMode;
    st->recogRect = rectr;
    st->tempRect = rectt;
    //qDebug()<<st->mode<<st->rect;
    this->stack.push(st);
}

DrawingOperation DrawingOperationStack::popStack()
{
    DrawingOperation op;
    op.curMode = -1;
    op.recogRect = QRect(0,0,0,0);
    op.tempRect = QRect(0,0,0,0);

    if(this->stack.isEmpty())
    {
        return op;
    }
    DrawingOperation *opera = this->stack.pop();
    op.recogRect = opera->recogRect;
    op.tempRect = opera->tempRect;
    op.curMode = opera->curMode;
    //this->stack.pop();
    delete opera;
    //qDebug()<<op.mode << op.rect;
    return op;
}

DrawingOperation DrawingOperationStack::getCurOperation()
{
    DrawingOperation op;
    op.curMode = -1;
    op.recogRect = QRect(0,0,0,0);
    op.tempRect = QRect(0,0,0,0);
    if(this->stack.isEmpty())
    {
        return op;
    }
    DrawingOperation *opera = this->stack.back();
    op.recogRect = opera->recogRect;
    op.tempRect = opera->tempRect;
    op.curMode = opera->curMode;
    return op;
}

bool DrawingOperationStack::isEmptyStack()
{
    return this->stack.isEmpty();
}
