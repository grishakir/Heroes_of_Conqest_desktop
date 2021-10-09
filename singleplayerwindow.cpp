//#include "ai.h"
#include "singleplayerwindow.h"
#include "ui_singleplayerwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QTimer>

SinglePlayerWindow::SinglePlayerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SinglePlayerWindow)
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


    this->ui->player1_skill_20->hide();
    this->ui->player1_skill_19->hide();
    this->ui->player1_skill_18->hide();
    this->ui->player1_skill_17->hide();
    this->ui->player1_skill_16->hide();

    player1 = new Warrior();
    player1->setPosition(LEFT);
    player2 = new Warrior();
    player2->setPosition(RIGHT);
    player1->setLabel(this->ui->unit1);
    player2->setLabel(this->ui->unit2);
    player1->setTarget(player2);
    player2->setTarget(player1);
    player1->weapons[SPELL_1]->connectButton(this->ui->player1_skill_11);
    player1->weapons[SPELL_2]->connectButton(this->ui->player1_skill_12);
    player1->weapons[SPELL_3]->connectButton(this->ui->player1_skill_13);
    player1->weapons[SPELL_4]->connectButton(this->ui->player1_skill_14);
    player1->weapons[SPELL_5]->connectButton(this->ui->player1_skill_15);

    player2->weapons[SPELL_1]->connectButton(this->ui->player1_skill_16);
    player2->weapons[SPELL_2]->connectButton(this->ui->player1_skill_17);
    player2->weapons[SPELL_3]->connectButton(this->ui->player1_skill_18);
    player2->weapons[SPELL_4]->connectButton(this->ui->player1_skill_19);
    player2->weapons[SPELL_5]->connectButton(this->ui->player1_skill_20);


    player1->setHpLabel(this->ui->player1_hp);
    player1->setEnergLabel(this->ui->player1_energ);

    player2->setHpLabel(this->ui->player2_hp);
    player2->setEnergLabel(this->ui->player2_energ);

    connect(this->ui->player1_skill_11, &QPushButton::clicked, player1, &Unit::useSkill1);
    connect(this->ui->player1_skill_12, &QPushButton::clicked, player1, &Unit::useSkill2);
    connect(this->ui->player1_skill_13, &QPushButton::clicked, player1, &Unit::useSkill3);
    connect(this->ui->player1_skill_14, &QPushButton::clicked, player1, &Unit::useSkill4);
    connect(this->ui->player1_skill_15, &QPushButton::clicked, player1, &Unit::useSkill5);
    //Ai *ai = new Ai(player2);

    analysTimer = new QTimer;
    connect(analysTimer, &QTimer::timeout, this, &SinglePlayerWindow::analysAndHit);
    analysTimer->start(2000);

    connect(player1, &Unit::destroed, this, &SinglePlayerWindow::checkEnding);
    connect(player2, &Unit::destroed, this, &SinglePlayerWindow::checkEnding);

    player1->show();
    player2->show();

}

SinglePlayerWindow::~SinglePlayerWindow()
{
    delete ui;
    delete player2;
    delete background;
    delete analysTimer;
    delete player1;
    delete background;
}

void SinglePlayerWindow::checkEnding()
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

void SinglePlayerWindow::analysAndHit()
{
    if (player2->weapons[SPELL_1]->canUse(player2))
    {
        player2->useSkill1();
    } else if (player2->weapons[SPELL_2]->canUse(player2))
    {
        player2->useSkill2();
    } else if (player2->weapons[SPELL_3]->canUse(player2))
    {
        player2->useSkill3();
    }else if (player2->weapons[SPELL_4]->canUse(player2))
    {
        player2->useSkill4();
    }
    if (player2->weapons[SPELL_5]->canUse(player2))
    {
        player2->useSkill5();
    }
}
