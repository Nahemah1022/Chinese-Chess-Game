#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menuwindow.h"
#include <chess.h>
#include <soldier.h>
#include <fire.h>
#include <horse.h>
#include <car.h>
#include <staff.h>
#include <defender.h>
#include <general.h>

int MainWindow::lastStepNum[9][10][2];
bool MainWindow::turn = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
    ui->menuBar->hide();

    ui->graphicsView->raise();
    setStyleSheet("background: palette(window)");

    resetButton = new QPushButton("Reset", this);
    resetButton->setGeometry(575, 290, 193, 60);
    QFont f;
    f.setFamily("仿宋");
    f.setPixelSize(40);
    resetButton->setFont(f);
    resetButton->setStyleSheet("background-color: rgb(233, 185, 110)");

    lightPix = new QPixmap(":/img/src/images/亮燈泡.png");
    darkPix = new QPixmap(":/img/src/images/暗燈泡.png");
    losing = new QPixmap(":/img/src/images/破燈泡.png");
    losingPix = new QPixmap(":/img/src/images/loser.png");
    ui->red_light->setScaledContents(true);
    ui->black_light->setScaledContents(true);
    ui->red_losing->setScaledContents(true);
    ui->black_losing->setScaledContents(true);
    ui->red_losing->setStyleSheet("background: palette(window)");
    ui->black_losing->setStyleSheet("background: palette(window)");
    ui->red_losing->setAttribute(Qt::WA_TranslucentBackground);
    ui->black_losing->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->graphicsView, SIGNAL(sendMousePosition(struct position)), this, SLOT(showMousePosition(struct position)));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetCall()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap board(":/img/src/images/棋盤.png");
    //board = board.scaled(ui->graphicsView->width(),ui->graphicsView->height());
    scene->addPixmap(board);

    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            this->pos[i][j].x = 4+58*i;
            this->pos[i][j].y = 20+58*j;
        }
    }

    changeTurn();

    for(int i=0; i<5; ++i){
        pos[i*2][6].currentChess = new Soldier(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), pos[i*2][6], true);
        pos[i*2][3].currentChess = new Soldier(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), pos[i*2][3], false);
    }
    pos[4][9].currentChess = new General(ui->graphicsView, this, QIcon(":/img/src/images/紅帥.png"), pos[4][9], true);
    pos[4][0].currentChess = new General(ui->graphicsView, this, QIcon(":/img/src/images/黑將.png"), pos[4][0], false);
    redGeneral = pos[4][9].currentChess;
    blackGeneral = pos[4][0].currentChess;

    for(int i=0; i<2; ++i){
        pos[3+i*2][9].currentChess = new Staff(ui->graphicsView, this, QIcon(":/img/src/images/紅士.png"), pos[3+i*2][9], true);
        pos[3+i*2][0].currentChess = new Staff(ui->graphicsView, this, QIcon(":/img/src/images/黑士.png"), pos[3+i*2][0], false);
        pos[i*8][9].currentChess = new Car(ui->graphicsView ,this, QIcon(":/img/src/images/紅車.png"), pos[i*8][9], true);
        pos[i*8][0].currentChess = new Car(ui->graphicsView ,this, QIcon(":/img/src/images/黑車.png"), pos[i*8][0], false);
        pos[1+i*6][7].currentChess = new Fire(ui->graphicsView ,this, QIcon(":/img/src/images/紅炮.png"), pos[1+i*6][7], true);
        pos[1+i*6][2].currentChess = new Fire(ui->graphicsView ,this, QIcon(":/img/src/images/黑炮.png"), pos[1+i*6][2], false);
        pos[2+i*4][9].currentChess = new Defender(ui->graphicsView ,this, QIcon(":/img/src/images/紅相.png"), pos[2+i*4][9], true);
        pos[2+i*4][0].currentChess = new Defender(ui->graphicsView ,this, QIcon(":/img/src/images/黑象.png"), pos[2+i*4][0], false);
        pos[1+i*6][9].currentChess = new Horse(ui->graphicsView ,this, QIcon(":/img/src/images/紅馬.png"), pos[1+i*6][9], true);
        pos[1+i*6][0].currentChess = new Horse(ui->graphicsView ,this, QIcon(":/img/src/images/黑馬.png"), pos[1+i*6][0], false);
    }
    resetButton->setEnabled(false);
}

MainWindow::MainWindow(struct position ctorPos[9][10], int turn, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
    ui->menuBar->hide();
    ui->graphicsView->raise();

    setStyleSheet("background: palette(window)");

    resetButton = new QPushButton("Reset", this);
    resetButton->setGeometry(575, 290, 193, 60);
    QFont f;
    f.setFamily("仿宋");
    f.setPixelSize(40);
    resetButton->setFont(f);
    resetButton->setStyleSheet("background-color: rgb(233, 185, 110)");

    lightPix = new QPixmap(":/img/src/images/亮燈泡.png");
    darkPix = new QPixmap(":/img/src/images/暗燈泡.png");
    losing = new QPixmap(":/img/src/images/破燈泡.png");
    losingPix = new QPixmap(":/img/src/images/loser.png");

    ui->red_light->setScaledContents(true);
    ui->black_light->setScaledContents(true);
    ui->red_losing->setScaledContents(true);
    ui->black_losing->setScaledContents(true);
    ui->red_losing->setStyleSheet("background: palette(window)");
    ui->black_losing->setStyleSheet("background: palette(window)");
    ui->red_losing->setAttribute(Qt::WA_TranslucentBackground);
    ui->black_losing->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->graphicsView, SIGNAL(sendMousePosition(struct position)), this, SLOT(showMousePosition(struct position)));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetCall()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap board(":/img/src/images/棋盤.png");
    //board = board.scaled(ui->graphicsView->width(),ui->graphicsView->height());
    scene->addPixmap(board);

    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            pos[i][j].x = ctorPos[i][j].x+4;
            pos[i][j].y = ctorPos[i][j].y+20;
            if(ctorPos[i][j].currentChess != nullptr){
                pos[i][j].currentChess = initChess(ctorPos[i][j].currentChess->typeNum, i, j, ctorPos[i][j].currentChess->team);
            }
        }
    }
    this->turn = turn;
    changeTurn();
    resetButton->setEnabled(false);
}

MainWindow::MainWindow(int posToLoad[9][10][2], int turn, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->hide();
    ui->menuBar->hide();
    ui->graphicsView->raise();
    setStyleSheet("background: palette(window)");

    resetButton = new QPushButton("Reset", this);
    resetButton->setGeometry(575, 290, 193, 60);
    QFont f;
    f.setFamily("仿宋");
    f.setPixelSize(40);
    resetButton->setFont(f);
    resetButton->setStyleSheet("background-color: rgb(233, 185, 110)");

    lightPix = new QPixmap(":/img/src/images/亮燈泡.png");
    darkPix = new QPixmap(":/img/src/images/暗燈泡.png");
    losing = new QPixmap(":/img/src/images/破燈泡.png");
    losingPix = new QPixmap(":/img/src/images/loser.png");
    ui->red_light->setScaledContents(true);
    ui->black_light->setScaledContents(true);
    ui->red_losing->setScaledContents(true);
    ui->black_losing->setScaledContents(true);
    ui->red_losing->setStyleSheet("background: palette(window)");
    ui->black_losing->setStyleSheet("background: palette(window)");
    ui->red_losing->setAttribute(Qt::WA_TranslucentBackground);
    ui->black_losing->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->graphicsView, SIGNAL(sendMousePosition(struct position)), this, SLOT(showMousePosition(struct position)));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetCall()));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap board(":/img/src/images/棋盤.png");
    //board = board.scaled(ui->graphicsView->width(),ui->graphicsView->height());
    scene->addPixmap(board);

    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            pos[i][j].x = 4+58*i;
            pos[i][j].y = 20+58*j;
            if(posToLoad[i][j][0] != 0){
                pos[i][j].currentChess = initChess(posToLoad[i][j][0], i, j, posToLoad[i][j][1]);
            }
        }
    }
    this->turn = turn;
    changeTurn();
    resetButton->setEnabled(false);
}

void MainWindow::clone()
{
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            lastStepPos[i][j].x = pos[i][j].x;
            lastStepPos[i][j].y = pos[i][j].y;
            if(pos[i][j].currentChess != nullptr){
                lastStepNum[i][j][0] = pos[i][j].currentChess->typeNum;
                lastStepNum[i][j][1] = pos[i][j].currentChess->team;
            }
            else {
                lastStepNum[i][j][0] = 0;
                lastStepNum[i][j][1] = -1;
            }
            //qDebug() << lastStepNum[i][j][0];
        }
    }

}

void MainWindow::resetOneStep()
{
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            if(pos[i][j].currentChess != nullptr
                    && (lastStepNum[i][j][0] != pos[i][j].currentChess->typeNum || lastStepNum[i][j][1] != pos[i][j].currentChess->team)){
                delete pos[i][j].currentChess->button;
                pos[i][j].currentChess->~Chess();
                pos[i][j].currentChess = nullptr;
                if(lastStepNum[i][j][0] != 0){
                    initChess(lastStepNum[i][j][0], i, j, lastStepNum[i][j][1]);
                    resetButton->setEnabled(false);
                }
            }
            else if (lastStepNum[i][j][0] != 0 && pos[i][j].currentChess == nullptr){
                initChess(lastStepNum[i][j][0], i, j, lastStepNum[i][j][1]);
                resetButton->setEnabled(false);
            }
        }
    }
}

Chess *MainWindow::initChess(int num, int xIndex, int yIndex, bool team)
{
    switch (num) {
    case 1:
        if(team){
            pos[xIndex][yIndex].currentChess = new General(ui->graphicsView, this, QIcon(":/img/src/images/紅帥.png"), pos[xIndex][yIndex], true);
            redGeneral = pos[xIndex][yIndex].currentChess;
        }
        else{
            pos[xIndex][yIndex].currentChess = new General(ui->graphicsView, this, QIcon(":/img/src/images/黑將.png"), pos[xIndex][yIndex], false);
            blackGeneral = pos[xIndex][yIndex].currentChess;
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    case 2:
        if(team){
            pos[xIndex][yIndex].currentChess = new Staff(ui->graphicsView, this, QIcon(":/img/src/images/紅士.png"), pos[xIndex][yIndex], true);
        }
        else{
            pos[xIndex][yIndex].currentChess = new Staff(ui->graphicsView, this, QIcon(":/img/src/images/黑士.png"), pos[xIndex][yIndex], false);
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    case 3:
        if(team){
            pos[xIndex][yIndex].currentChess = new Defender(ui->graphicsView, this, QIcon(":/img/src/images/紅相.png"), pos[xIndex][yIndex], true);
        }
        else{
            pos[xIndex][yIndex].currentChess = new Defender(ui->graphicsView, this, QIcon(":/img/src/images/黑象.png"), pos[xIndex][yIndex], false);
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    case 4:
        if(team){
            pos[xIndex][yIndex].currentChess = new Car(ui->graphicsView, this, QIcon(":/img/src/images/紅車.png"), pos[xIndex][yIndex], true);
        }
        else{
            pos[xIndex][yIndex].currentChess = new Car(ui->graphicsView, this, QIcon(":/img/src/images/黑車.png"), pos[xIndex][yIndex], false);
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    case 5:
        if(team){
            pos[xIndex][yIndex].currentChess = new Horse(ui->graphicsView, this, QIcon(":/img/src/images/紅馬.png"), pos[xIndex][yIndex], true);
        }
        else{
            pos[xIndex][yIndex].currentChess = new Horse(ui->graphicsView, this, QIcon(":/img/src/images/黑馬.png"), pos[xIndex][yIndex], false);
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    case 6:
        if(team){
            pos[xIndex][yIndex].currentChess = new Fire(ui->graphicsView, this, QIcon(":/img/src/images/紅炮.png"), pos[xIndex][yIndex], true);
        }
        else{
            pos[xIndex][yIndex].currentChess = new Fire(ui->graphicsView, this, QIcon(":/img/src/images/黑炮.png"), pos[xIndex][yIndex], false);
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    case 7:
        if(team){
            pos[xIndex][yIndex].currentChess = new Soldier(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), pos[xIndex][yIndex], true);
        }
        else{
            pos[xIndex][yIndex].currentChess = new Soldier(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), pos[xIndex][yIndex], false);
        }
        pos[xIndex][yIndex].currentChess->button->show();
        return pos[xIndex][yIndex].currentChess;
    }
    return pos[xIndex][yIndex].currentChess;
}

void MainWindow::sendStatus()
{
    clone();
    if(server == nullptr){
        client->writeOutData(lastStepNum);
    }
    else{
        server->writeOutData(lastStepNum);
    }
    resetButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeTurn()
{
    if(!turn){
        ui->red_light->setPixmap(*lightPix);
        ui->black_light->setPixmap(*darkPix);
    }
    else {
        ui->red_light->setPixmap(*darkPix);
        ui->black_light->setPixmap(*lightPix);
    }
    resetButton->setEnabled(true);
}

void MainWindow::win(bool team)
{
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            if(pos[i][j].currentChess != nullptr){
                pos[i][j].currentChess->~Chess();
            }
        }
    }
    resetButton->setText("Return To Menu");
    ui->saveButton->setEnabled(false);
    isEnding = true;
    QFont f;
    f.setPixelSize(20);
    resetButton->setFont(f);

    if(team){
        ui->black_losing->setPixmap(QPixmap(":/img/src/images/loser.png"));
        ui->black_light->setPixmap(QPixmap(":/img/src/images/破燈泡.png"));
        ui->black_losing->raise();
    }
    else {
        ui->red_losing->setPixmap(QPixmap(":/img/src/images/loser.png"));
        ui->red_light->setPixmap(QPixmap(":/img/src/images/破燈泡.png"));
        ui->red_losing->raise();
    }
}

void MainWindow::resetCall(){
    if(!isEnding){
        //qDebug() << "reset";
        turn = !turn;
        changeTurn();
        resetOneStep();
    }
    else{
        emit ending();
        this->~MainWindow();
    }
}

void MainWindow::restatusByData()
{
    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            lastStepNum[i][j][0] = (server == nullptr? client->status[i][j][0] : server->status[i][j][0]);
            lastStepNum[i][j][1] = (server == nullptr? client->status[i][j][1] : server->status[i][j][1]);
        }
    }
    turn = !turn;
    changeTurn();
    resetOneStep();

    if(pos[(redGeneral->currentPos.x-4)/58][(redGeneral->currentPos.y-20)/58].currentChess->typeNum != 1){
        win(false);
    }
    else if (pos[(blackGeneral->currentPos.x-4)/58][(blackGeneral->currentPos.y-20)/58].currentChess->typeNum != 1) {
        win(true);
    }

}

void MainWindow::showMousePosition(struct position pos){
    ui->label->setText("x: " + QString::number(pos.x) + ",y: " + QString::number(pos.y));
}

void MainWindow::on_quitButton_clicked()
{
    emit ending();
    this->~MainWindow();
}

void MainWindow::on_saveButton_clicked()
{
    clone();
    emit save();
}
