#include "button_tracking.h"

button_tracking::button_tracking(QWidget *parent) : QPushButton (parent)
{
    setMouseTracking(true);
}

void button_tracking::mouseMoveEvent(QMouseEvent *mouse_event)
{
    struct position mouse_pos;
    mouse_pos.x = mouse_event->x()+this->geometry().x();
    mouse_pos.y = mouse_event->y()+this->geometry().y();

    //qDebug() << "x: " << mouse_pos.x << ",y: " << mouse_pos.y;
    //qDebug() << "mouse on button";
    emit sendMouseOnButton(mouse_pos);
}
