#ifndef FIRE_H
#define FIRE_H

#include "chess.h"

class Fire : public Chess
{
public:
    Fire(QGraphicsView *, MainWindow *, QIcon, struct position, bool);

public slots:
    void movement();

private:
    bool isLegal(struct position);
    bool isEatable = false;
};

#endif // FIRE_H
