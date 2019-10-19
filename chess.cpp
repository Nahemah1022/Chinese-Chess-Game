#include <chess.h>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>

struct position Chess::setPosition(struct position pos){
    button->setGeometry(pos.x, pos.y, 89, 91);
    return pos;
}

Chess::Chess(QGraphicsView *board, MainWindow *w, QIcon bIcon, struct position pos, bool team){
    button = new button_tracking(w);
    this->w = w;
    QRegion region(QRect(16,18,56,56), QRegion::Ellipse);
    button->setMask(region);
    button->setIcon(bIcon);
    button->setIconSize(button->size()*3);
    button->setFlat(true);
    currentPos =  setPosition(pos);
    this->team = team;
    this->board = board;
    isMoving = false;
    connect(board, SIGNAL(sendMousePosition(struct position)), this, SLOT(setMousePosition(struct position)));
    connect(button, SIGNAL(sendMouseOnButton(struct position)), this, SLOT(setMousePosition(struct position)));
}

Chess::Chess(QGraphicsView *board, EditorWIndow *e, QIcon bIcon, struct position pos, bool team, int num)
{
    button = new button_tracking(e);
    this->e = e;
    QRegion region(QRect(17,17,55,55), QRegion::Ellipse);
    button->setMask(region);
    button->setIcon(bIcon);
    button->setIconSize(button->size()*3);
    button->setFlat(true);
    currentPos =  setPosition(pos);
    homePos = currentPos;
    this->team = team;
    this->board = board;
    isMoving = false;
    typeNum = num;
    connect(board, SIGNAL(sendMousePosition(struct position)), this, SLOT(setMousePosition(struct position)));
    connect(button, SIGNAL(sendMouseOnButton(struct position)), this, SLOT(setMousePosition(struct position)));
    connect(button, SIGNAL(clicked()), this, SLOT(movement()));
}

void Chess::movement(){
    if(!isMoving){
        isMoving = true;
    }
    else {
        isMoving = false;
        struct position targetPos = getTargetPositionOnEditor();
        if(targetPos.x < 510){
            e->pos[(currentPos.x)/58][(currentPos.y)/58].currentChess = nullptr;
            e->pos[(targetPos.x)/58][(targetPos.y)/58].currentChess = this;
        }
        else {
            e->pos[(currentPos.x)/58][(currentPos.y)/58].currentChess = nullptr;
        }
        currentPos = setPosition(targetPos);
    }
}

bool Chess::isKingMeet(){
    for(int i=w->redGeneral->currentPos.y-58; i>=20; i-=58){
        if(w->pos[(w->redGeneral->currentPos.x-4)/58][(i-20)/58].currentChess != nullptr
                && !w->pos[(w->redGeneral->currentPos.x-4)/58][(i-20)/58].currentChess->isKing){
            break;
        }
        else if(w->pos[(w->redGeneral->currentPos.x-4)/58][(i-20)/58].currentChess != nullptr
                && w->pos[(w->redGeneral->currentPos.x-4)/58][(i-20)/58].currentChess->isKing){
            qDebug() << "王見王";
            QMessageBox::critical(w, "警告！", "王見王");
            w->resetButton->setEnabled(false);
            return true;
        }
    }
    return false;
}

bool Chess::isWin(struct position targetPos)
{
    if(team && targetPos.x == w->blackGeneral->currentPos.x && targetPos.y == w->blackGeneral->currentPos.y){
        delete w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->button;
        w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->~Chess();
        w->pos[(currentPos.x-4)/58][(currentPos.y-20)/58].currentChess = nullptr;
        w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess = this;
        currentPos = setPosition(targetPos);
        isMoving = false;
        w->win(team);
        return true;
    }
    else if(!team && targetPos.x == w->redGeneral->currentPos.x && targetPos.y == w->redGeneral->currentPos.y){
        delete w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->button;
        w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->~Chess();
        w->pos[(currentPos.x-4)/58][(currentPos.y-20)/58].currentChess = nullptr;
        w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess = this;
        currentPos = setPosition(targetPos);
        isMoving = false;
        w->win(team);
        return true;
    }
    return false;
}

struct position Chess::getTargetPosition(){
    struct position targetPos;
    targetPos.x = 1000;
    targetPos.y = 1000;
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            if((w->pos[i][j].x-button->geometry().x())*(w->pos[i][j].x-button->geometry().x()) + (w->pos[i][j].y-button->geometry().y())*(w->pos[i][j].y-button->geometry().y()) <
                    (targetPos.x-button->geometry().x())*(targetPos.x-button->geometry().x()) + (targetPos.y-button->geometry().y())*(targetPos.y-button->geometry().y())){
                targetPos.x = w->pos[i][j].x;
                targetPos.y = w->pos[i][j].y;
            }
        }
    }
    return targetPos;
}

position Chess::getTargetPositionOnEditor()
{
    struct position targetPos;
    targetPos.x = 1000;
    targetPos.y = 1000;
    if(button->geometry().x() <= 510){
        for(int i=0; i<9; ++i){
            for(int j=0; j<10; ++j){
                if((e->pos[i][j].x-button->geometry().x())*(e->pos[i][j].x-button->geometry().x()) + (e->pos[i][j].y-button->geometry().y())*(e->pos[i][j].y-button->geometry().y()) <
                        (targetPos.x-button->geometry().x())*(targetPos.x-button->geometry().x()) + (targetPos.y-button->geometry().y())*(targetPos.y-button->geometry().y())){
                    targetPos.x = e->pos[i][j].x;
                    targetPos.y = e->pos[i][j].y;
                }
            }
        }
        return targetPos;
    }
    else {
        return homePos;
    }
}

void Chess::setMousePosition(struct position pos){
    if(isMoving){
        button->raise();
        pos.x -= 43;
        pos.y -= 40;
        this->setPosition(pos);
    }
}

Chess::Chess(){

}

Chess::~Chess(){

}
