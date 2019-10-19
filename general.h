#ifndef GENERAL_H
#define GENERAL_H

#include <chess.h>

class General : public Chess
{
public:
    General(QGraphicsView *, MainWindow *, QIcon, struct position, bool);
    QLabel *losingLable;

public slots:
    void movement();

private:
    bool isLegal(struct position);
};

#endif // GENERAL_H
