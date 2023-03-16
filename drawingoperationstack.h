#ifndef DRAWINGOPERATIONSTACK_H
#define DRAWINGOPERATIONSTACK_H

#include <QObject>
#include <QRect>
#include <QStack>
struct DrawingOperation{
    int curMode;
    QRect recogRect;
    QRect tempRect;
};

class DrawingOperationStack
{
public:
    DrawingOperationStack();
    void pushInStack(int curMode, QRect rectr, QRect rectt);
    DrawingOperation popStack();
    DrawingOperation getCurOperation();
    bool isEmptyStack();
private:
    QStack<DrawingOperation*> stack;

};

#endif // DRAWINGOPERATIONSTACK_H
