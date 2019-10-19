#include "horse.h"

Horse::Horse(QGraphicsView *board, MainWindow *w, QIcon bIcon, struct position pos, bool team) : Chess(board, w, bIcon, pos, team){
    connect(button, SIGNAL(clicked()), this, SLOT(movement()));
    typeNum = 5;
}

void Horse::movement(){
    if(!isMoving && team ^ w->turn && ((w->server == nullptr && w->client == nullptr) || (w->server != nullptr && team) || (w->client != nullptr && !team))){
        isMoving = true;
    }
    else if(isMoving && team ^ w->turn){
        w->clone();
        struct position targetPos = getTargetPosition();
        struct position tempPos = currentPos;
        Chess *chessToDestroy = nullptr;
        if(isLegal(targetPos)){
            if(isWin(targetPos) && (w->server != nullptr || w->client != nullptr)){
                w->sendStatus();
                return;
            }
            w->pos[(currentPos.x-4)/58][(currentPos.y-20)/58].currentChess = nullptr;
            if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team != this->team){
                chessToDestroy = w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess;
            }
            w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess = this;
            currentPos =  setPosition(targetPos);
        }
        else {
            currentPos =  setPosition(currentPos);
            isMoving = false;
            return ;
        }

        if(isKingMeet()){
            currentPos = setPosition(tempPos);
            w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess = chessToDestroy;
            w->pos[(tempPos.x-4)/58][(tempPos.y-20)/58].currentChess = this;
            isMoving = false;
            return ;
        }

        if(chessToDestroy != nullptr){
            delete chessToDestroy->button;
            chessToDestroy->~Chess();
        }
        w->turn = !w->turn;
        w->changeTurn();
        isMoving = false;
        if(w->server != nullptr || w->client != nullptr)
            w->sendStatus();
    }
}

bool Horse::isLegal(struct position targetPos){
    if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team == this->team){
        return false;
    }

    if(!(abs(targetPos.x - currentPos.x) == 58 && abs(targetPos.y - currentPos.y) == 116) && !(abs(targetPos.x - currentPos.x) == 116 && abs(targetPos.y - currentPos.y) == 58)){
        return false;
    }

    if(targetPos.y - currentPos.y == 116 && w->pos[(currentPos.x-4)/58][(currentPos.y+58-20)/58].currentChess != nullptr){
        return false;
    }

    if(targetPos.y - currentPos.y == -116 && w->pos[(currentPos.x-4)/58][(currentPos.y-58-20)/58].currentChess != nullptr){
        return false;
    }

    if(targetPos.x - currentPos.x == 116 && w->pos[(currentPos.x+58-4)/58][(currentPos.y-20)/58].currentChess != nullptr){
        return false;
    }

    if(targetPos.x - currentPos.x == -116 && w->pos[(currentPos.x-58-4)/58][(currentPos.y-20)/58].currentChess != nullptr){
        return false;
    }

    return true;
}
