#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "unit.h"

#include <QWidget>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT
    Warrior *player1;
    Warrior *player2;
    QPixmap* background;
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
signals:
    void returnToMainWindow();
public slots:
    void checkEnding();

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
