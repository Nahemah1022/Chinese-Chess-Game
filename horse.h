#ifndef HORSE_H
#define HORSE_H

#include <chess.h>

class Horse : public Chess
{
public:
    Horse(QGraphicsView *, MainWindow *, QIcon, struct position, bool);

public slots:
    void movement();

private:
    bool isLegal(struct position);
};



#endif // HORSE_H
