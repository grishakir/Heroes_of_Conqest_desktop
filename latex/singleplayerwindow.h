#ifndef SINGLEPLAYERWINDOW_H
#define SINGLEPLAYERWINDOW_H

#include "unit.h"

#include <QWidget>

namespace Ui {
class SinglePlayerWindow;
}

class SinglePlayerWindow : public QWidget
{
    Q_OBJECT

    Warrior *player1;
    Warrior *player2;
    QTimer *analysTimer;
    QPixmap* background;
public:
    explicit SinglePlayerWindow(QWidget *parent = nullptr);
    ~SinglePlayerWindow();
signals:
    void returnToMainWindow();
public slots:
    void checkEnding();
    void analysAndHit();

private:
    Ui::SinglePlayerWindow *ui;
};

#endif // SINGLEPLAYERWINDOW_H
