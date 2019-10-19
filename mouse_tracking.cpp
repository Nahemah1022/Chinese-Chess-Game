#include "mouse_tracking.h"

mouse_tracking::mouse_tracking(QWidget *parent) : QGraphicsView (parent)
{
    setMouseTracking(true);
}

void mouse_tracking::mouseMoveEvent(QMouseEvent *mouse_event)
{
    struct position mouse_pos;
    mouse_pos.x = mouse_event->x();
    mouse_pos.y = mouse_event->y();

    if(mouse_pos.x <= this->size().width()+100 && mouse_pos.y <= this->size().height()+100){
        if(mouse_pos.x > 0 && mouse_pos.y > 0){
            //qDebug() << "send mouse position";
            emit sendMousePosition(mouse_pos);
        }
    }
}
