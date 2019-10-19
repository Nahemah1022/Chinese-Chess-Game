#ifndef MOUSE_TRACKING_H
#define MOUSE_TRACKING_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <chess.h>

class mouse_tracking : public QGraphicsView
{
    Q_OBJECT
public:
    mouse_tracking(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *mouse_event);

signals:
    void sendMousePosition(struct position);
};

#endif // MOUSE_TRACKING_H
