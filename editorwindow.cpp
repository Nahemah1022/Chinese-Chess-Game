#include "editorwindow.h"
#include "ui_editorwindow.h"
#include <QGraphicsPixmapItem>
#include "menuwindow.h"

EditorWIndow::EditorWIndow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWIndow)
{
    ui->setupUi(this);
    ui->menubar->hide();
    ui->statusbar->hide();
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    //QGraphicsScene::itemsBoundingRect()

    QGraphicsPixmapItem *board = new QGraphicsPixmapItem(QPixmap(":/img/src/images/棋盤.png"));
    scene->setSceneRect(0,0,ui->graphicsView->width()-10,ui->graphicsView->height()-10);

    scene->addItem(board);
    board->setPos(0, 0);

    for(int i=0; i<9; ++i){
        for(int j=0; j<10; ++j){
            this->pos[i][j].x = 58*i;
            this->pos[i][j].y = 58*j;
        }
    }

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
            home[i][j].x = 575+58*i;
            home[i][j].y = 10+58*j;
        }
    }

    for(int i=4; i<8; ++i){
        for(int j=0; j<4; ++j){
            home[i][j].x = 575+58*(i-4);
            home[i][j].y = 330+58*j;
        }
    }

    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑將.png"), home[0][0], false, 1);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑士.png"), home[1][0], false, 2);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑士.png"), home[2][0], false, 2);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑象.png"), home[3][0], false, 3);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑象.png"), home[0][1], false, 3);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑車.png"), home[1][1], false, 4);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑車.png"), home[2][1], false, 4);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑馬.png"), home[3][1], false, 5);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑馬.png"), home[0][2], false, 5);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑炮.png"), home[1][2], false, 6);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑炮.png"), home[2][2], false, 6);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), home[3][2], false, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), home[0][3], false, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), home[1][3], false, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), home[2][3], false, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/黑卒.png"), home[3][3], false, 7);


    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅帥.png"), home[4][0], true, 1);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅士.png"), home[5][0], true, 2);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅士.png"), home[6][0], true, 2);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅相.png"), home[7][0], true, 3);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅相.png"), home[4][1], true, 3);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅車.png"), home[5][1], true, 4);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅車.png"), home[6][1], true, 4);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅馬.png"), home[7][1], true, 5);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅馬.png"), home[4][2], true, 5);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅炮.png"), home[5][2], true, 6);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅炮.png"), home[6][2], true, 6);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), home[7][2], true, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), home[4][3], true, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), home[5][3], true, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), home[6][3], true, 7);
    new Chess(ui->graphicsView, this, QIcon(":/img/src/images/紅兵.png"), home[7][3], true, 7);
}

EditorWIndow::~EditorWIndow()
{
    delete ui;
}

void EditorWIndow::on_finish_clicked()
{
    w = new MainWindow(pos, (ui->redCheck->isChecked() ? 0 : 1));
    Menuwindow::battleWindow = w;
    w->show();
    connect(w, SIGNAL(ending()), Menuwindow::me, SLOT(returnToMenu()));
    connect(w, SIGNAL(save()), Menuwindow::me, SLOT(saveFiles()));
    this->~EditorWIndow();
}

void EditorWIndow::on_back_to_menu_clicked()
{
    emit endingEdit();
    this->~EditorWIndow();
}

