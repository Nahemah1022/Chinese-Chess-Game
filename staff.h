#ifndef STAFF_H
#define STAFF_H

#include <chess.h>

class Staff : public Chess
{
public:
    Staff(QGraphicsView *, MainWindow *, QIcon, struct position, bool);

public slots:
    void movement();

private:
    bool isLegal(struct position);
};

#endif // STAFF_H
