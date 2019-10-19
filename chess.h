#ifndef CHESS_H
#define CHESS_H

#include <QPushButton>
#include "button_tracking.h"
#include "editorwindow.h"

class General;

class Chess : public QObject
{
    Q_OBJECT
public:
    Chess(QGraphicsView *, MainWindow *, QIcon, struct position, bool);
    Chess(QGraphicsView *, EditorWIndow *, QIcon, struct position, bool, int);
    Chess();
    virtual ~Chess();
    bool team;
    bool isKing = false;
    button_tracking *button;
    struct position setPosition(struct position);
    int typeNum = 0;
    struct position currentPos;
    struct position homePos;

protected:
    QGraphicsView *board;
    MainWindow *w;
    EditorWIndow *e;
    bool isMoving;
    struct position getTargetPosition();
    struct position getTargetPositionOnEditor();
    bool isKingMeet();
    bool isWin(struct position);

public slots:
    void setMousePosition(struct position);
    virtual void movement();
};

#endif // CHESS_H
