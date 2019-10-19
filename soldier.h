#ifndef SOLDIER_H
#define SOLDIER_H

#include <chess.h>

class Soldier : public Chess
{
public:
    Soldier(QGraphicsView *, MainWindow *, QIcon, struct position, bool);

public slots:
    void movement();

private:
    bool isLegal(struct position);
};

#endif // SOLDIER_H
