#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "gamewindow.h"
#include "singleplayerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *quitPushButton;
    QPushButton *aboutPushButton;
    QPushButton *duelPushButton;
     QPushButton *singlePlayerPushButton;
     QMenu *menu;
     QAction *singlePlayerAction;
     QAction *duelAction;
     QAction *aboutAction;
     QAction *quitAction;
     QLabel *label;
     QVBoxLayout *layout;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void about();
    void duel();
    void singlePlayer();
    void delGameWindow();
private:
    Ui::MainWindow *ui;
    GameWindow *gameWindow;
    SinglePlayerWindow *singlePlayerWindow;
};
#endif // MAINWINDOW_H
