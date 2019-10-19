#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDateTime>
#include <QFileInfoList>
#include <QDir>
#include <QLineEdit>
#include <QNetworkInterface>
#include <QTimer>
#include "editorwindow.h"
#include "mainwindow.h"
#include "server.h"
#include "client.h"

namespace Ui {
class Menuwindow;
}

class Menuwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menuwindow(QWidget *parent = nullptr);
    static Menuwindow *me;
    static MainWindow *battleWindow;
    QPushButton *play_1;
    QPushButton *play_2;
    QPushButton *sendButton;
    QLineEdit *ipAddress;
    QLineEdit *ipPort;
    QLabel *detail;
    ~Menuwindow();

private slots:
    void on_startButton_clicked();
    void on_editorButton_clicked();
    void returnToMenu();
    void saveFiles();
    void on_loadButton_clicked();
    void on_loadButton_2_clicked();
    void on_OnlineButton_clicked();
    void play_1Pressed();
    void play_2Pressed();
    void showPlayer_1Detail();
    void showPlayer_2Detail();
    void play_1LinkStart();
    void timeCount();
    void onlineQuit();

private:
    Ui::Menuwindow *ui;
    QWidget *onlineWidget;
    EditorWIndow *editorWindow;
    MainWindow *p1Window, *p2Window;
    QVector<QFile *> files;
    int posToLoad[9][10][2];
    int turnToLoad;
    int count = 0;
    QTimer *timer;
    QPushButton *quitButton;

    void loadExistingFiles();
};

#endif // MENUWINDOW_H
