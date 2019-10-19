#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>
#include "mainwindow.h"

class Menuwindow;

class Chess;

namespace Ui {
class EditorWIndow;
}

class EditorWIndow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWIndow(QWidget *parent = nullptr);
    ~EditorWIndow();
    struct position pos[9][10];
    struct position home[8][4];

private slots:
    void on_finish_clicked();
    void on_back_to_menu_clicked();

signals:
    void endingEdit();

private:
    Ui::EditorWIndow *ui;
    QGraphicsScene *scene;
    Menuwindow *me;
    MainWindow *w;
    QVector <QFile>files;
};

#endif // EDITORWINDOW_H
