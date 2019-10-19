#ifndef DEFENDER_H
#define DEFENDER_H

#include <chess.h>

class Defender : public Chess
{
public:
    Defender(QGraphicsView *, MainWindow *, QIcon, struct position, bool);

public slots:
    void movement();

private:
    bool isLegal(struct position);
};

#endif // DEFENDER_H
