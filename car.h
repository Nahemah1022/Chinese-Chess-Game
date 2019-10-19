#ifndef CAR_H
#define CAR_H

#include <chess.h>

class Car : public Chess{
public:
    Car(QGraphicsView *, MainWindow *, QIcon, struct position, bool);

public slots:
    void movement();

private:
    bool isLegal(struct position);
    bool isEatable = false;
};

#endif // CAR_H
