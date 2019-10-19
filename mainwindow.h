#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include "server.h"
#include "client.h"

class Chess;
class Menuwindow;

struct position{
    int x;
    int y;
    Chess *currentChess = nullptr;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(struct position[9][10], int, QWidget *parent = nullptr);
    MainWindow(int[9][10][2], int, QWidget *parent = nullptr);
    struct position pos[9][10];
    struct position lastStepPos[9][10];
    static int lastStepNum[9][10][2];
    void clone();
    void resetOneStep();
    Chess *initChess(int, int, int, bool);
    void sendStatus();
    static bool turn;
    bool isEnding = false;
    void changeTurn();
    void win(bool);
    Chess *redGeneral, *blackGeneral;
    QPixmap *lightPix, *darkPix, *losing;
    QPixmap *losingPix;
    QPushButton *resetButton;
    myServer *server = nullptr;
    Client *client = nullptr;

    ~MainWindow();
signals:
    void ending();
    void save();

public slots:
    void showMousePosition(struct position);
    void resetCall();
    void restatusByData();

private slots:
    void on_quitButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Menuwindow *me;
};

#endif // MAINWINDOW_H
