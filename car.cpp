#include "car.h"

Car::Car(QGraphicsView *board, MainWindow *w, QIcon bIcon, struct position pos, bool team) : Chess(board, w, bIcon, pos, team){
    connect(button, SIGNAL(clicked()), this, SLOT(movement()));
    typeNum = 4;
}

void Car::movement(){
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
            if(isEatable){
                chessToDestroy = w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess;
            }
            w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess = this;
            currentPos =  setPosition(targetPos);
        }
        else {
            currentPos = setPosition(currentPos);
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

bool Car::isLegal(struct position targetPos){
    if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team == this->team){
        return false;
    }

    if(targetPos.x != currentPos.x && targetPos.y != currentPos.y){//no oblique
        return false;
    }

    if(targetPos.y < currentPos.y){
        int currentXIndex = (currentPos.x-4)/58;
        for(int i=currentPos.y-58; i>targetPos.y; i-=58){
            if(w->pos[currentXIndex][(i-20)/58].currentChess != nullptr){
                return false;
            }
        }
        if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team != this->team){
            isEatable = true;
        }
    }

    if(targetPos.y > currentPos.y){
        int currentXIndex = (currentPos.x-4)/58;
        for(int i=currentPos.y+58; i<targetPos.y; i+=58){
            if(w->pos[currentXIndex][(i-20)/58].currentChess != nullptr){
                return false;
            }
        }
        if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team != this->team){
            isEatable = true;
        }
    }

    if(targetPos.x < currentPos.x){
        int currentYIndex = (currentPos.y-20)/58;
        for(int i=currentPos.x-58; i>targetPos.x; i-=58){
            if(w->pos[(i-4)/58][currentYIndex].currentChess != nullptr){
                return false;
            }
        }
        if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team != this->team){
            isEatable = true;
        }
    }

    if(targetPos.x > currentPos.x){
        int currentYIndex = (currentPos.y-20)/58;
        for(int i=currentPos.x+58; i<targetPos.x; i+=58){
            if(w->pos[(i-4)/58][currentYIndex].currentChess != nullptr){
                return false;
            }
        }
        if(w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess != nullptr && w->pos[(targetPos.x-4)/58][(targetPos.y-20)/58].currentChess->team != this->team){
            isEatable = true;
        }
    }

    return true;
}
