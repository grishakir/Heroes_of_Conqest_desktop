#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "unit.h"

#include <qmessagebox.h>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(1280, 720));
    switch (rand() % 3)
    {
    case 0:
        background = new QPixmap(":/backgrounds/res/fon_battle1.jpg");
        break;
    case 1:
        background = new QPixmap(":/backgrounds/res/fon_battle2.jpg");
        break;
    default:
        background = new QPixmap(":/backgrounds/res/fon_battle3.jpg");
        break;
    }

    *background = background->scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, *background);
    this->setPalette(palette);
    player1 = new Warrior();
    player1->setPosition(LEFT);
    player2 = new Warrior();
    player2->setPosition(RIGHT);
    player1->setLabel(this->ui->unit1);
    player2->setLabel(this->ui->unit2);
    player1->setTarget(player2);
    player2->setTarget(player1);

    player1->weapons[SPELL_1]->connectButton(this->ui->player1_skill_1);
    player1->weapons[SPELL_2]->connectButton(this->ui->player1_skill_2);
    player1->weapons[SPELL_3]->connectButton(this->ui->player1_skill_3);
    player1->weapons[SPELL_4]->connectButton(this->ui->player1_skill_4);
    player1->weapons[SPELL_5]->connectButton(this->ui->player1_skill_5);

    player2->weapons[SPELL_1]->connectButton(this->ui->player2_skill_1);
    player2->weapons[SPELL_2]->connectButton(this->ui->player2_skill_2);
    player2->weapons[SPELL_3]->connectButton(this->ui->player2_skill_3);
    player2->weapons[SPELL_4]->connectButton(this->ui->player2_skill_4);
    player2->weapons[SPELL_5]->connectButton(this->ui->player2_skill_5);


    player1->setHpLabel(this->ui->player1_hp);
    player1->setEnergLabel(this->ui->player1_energ);

    player2->setHpLabel(this->ui->player2_hp);
    player2->setEnergLabel(this->ui->player2_energ);

    connect(this->ui->player1_skill_1, &QPushButton::clicked, player1, &Unit::useSkill1);
    connect(this->ui->player1_skill_2, &QPushButton::clicked, player1, &Unit::useSkill2);
    connect(this->ui->player1_skill_3, &QPushButton::clicked, player1, &Unit::useSkill3);
    connect(this->ui->player1_skill_4, &QPushButton::clicked, player1, &Unit::useSkill4);
    connect(this->ui->player1_skill_5, &QPushButton::clicked, player1, &Unit::useSkill5);

    connect(this->ui->player2_skill_1, &QPushButton::clicked, player2, &Unit::useSkill1);
    connect(this->ui->player2_skill_2, &QPushButton::clicked, player2, &Unit::useSkill2);
    connect(this->ui->player2_skill_3, &QPushButton::clicked, player2, &Unit::useSkill3);
    connect(this->ui->player2_skill_4, &QPushButton::clicked, player2, &Unit::useSkill4);
    connect(this->ui->player2_skill_5, &QPushButton::clicked, player2, &Unit::useSkill5);

    connect(player1, &Unit::destroed, this, &GameWindow::checkEnding);
    connect(player2, &Unit::destroed, this, &GameWindow::checkEnding);
}

void GameWindow::checkEnding()
{
    if (player2->getHp() <= 0)
    {
        QMessageBox::information(this, "Winner", "Player 1 is winner!");
    }
    else if (player1->getHp() <= 0)
    {
        QMessageBox::information(this, "Winner", "Player 2 is winner!");
    }
    this->close();
    qApp->quit();
}

GameWindow::~GameWindow()
{
    delete ui;
    delete player1;
    delete player2;
    delete background;
}
