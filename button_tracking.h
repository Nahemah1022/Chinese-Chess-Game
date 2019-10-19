#ifndef BUTTON_TRACKING_H
#define BUTTON_TRACKING_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include "mainwindow.h"

class button_tracking : public QPushButton
{
    Q_OBJECT
public:
    button_tracking(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *mouse_event);

signals:
    void sendMouseOnButton(struct position);

};

#endif // BUTTON_TRACKING_H
