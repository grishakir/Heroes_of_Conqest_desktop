#include "spell.h"

#include <QPixmap>
#include <QTimer>
#include <QUrl>


void Spell::connectButton(QPushButton *inButton)
{
    button = inButton;
}

int Spell::getCost()
{
    return cost;
}

int Spell::getCallDown()
{
    return callDown;
}

int Spell::getCost(int &cost)
{
    cost = this->cost;
    return cost;
}

int Spell::getCallDown(int &timeCallDown)
{
    timeCallDown = this->callDown;
    return callDown;
}


bool Spell::canUse(Unit *unit)
{
    return (unit->getEnergy() - cost > 0) 
	&& isCanUse && !unit->getIsStanned();
}

Spell::~Spell()
{
    delete sound;
    delete apperance;
    delete apperanceR;
    delete timer;
    delete callDownTimer;
}

void Spell::startCallDown()
{
    delete callDownTimer;
    isCanUse = 0;

    button->setText("X");
    callDownTimer = new QTimer;
    connect(callDownTimer, &QTimer::timeout, this, &Spell::callDownTimeout);
    connect(callDownTimer, &QTimer::timeout, callDownTimer, &QTimer::stop);
    callDownTimer->start(SECTOMILL*callDown);
}

void Spell::callDownTimeout()
{
    isCanUse = 1;
     button->setText("");
}

SpellCuttingBlow::SpellCuttingBlow()
{
    isCanUse = 1;
    cost = 10;
    callDown = 4;
    damage = 180;
    //sound =  new QUrl("qrc:/sounds/res/sounds/w_1.wav");
    apperance = new QPixmap(":/unit/w_1.png");
    apperanceR = new QPixmap(":/unit/w_1_r.png");

}



void SpellCuttingBlow::use(Unit *target, Unit *initioner)
{
    target->takeDamage(initioner->getDamage() * damage * PERCENT_TO_FRAC);
    initioner->useEnergy(cost);
    initioner->globalCallDown();
    this->startCallDown();
    if (initioner->getPosition() == RIGHT)
        initioner->setApperance(apperanceR);
    else
        initioner->setApperance(apperance);
}


SpellReflektion::SpellReflektion()
{
    isCanUse = 1;
    cost = 20;
    callDown = 40;
    duration = 4;
    sound = new QUrl("qrc:/sounds/res/sounds/w_2.wav");
    apperance = new QPixmap(":/unit/w_2.png");
    apperanceR = new QPixmap(":/unit/w_2_r.png");
}

void SpellReflektion::use(Unit *target, Unit *initioner)
{
    initioner->useEnergy(cost);
    initioner->setDefence(100);
    initioner->globalCallDown();
    this->startCallDown();
    delete timer;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, initioner, &Unit::returnDefence);

    timer->start((duration + (100 - initioner->getEnergy())
	/ 20 ) * SECTOMILL);

    connect(timer, &QTimer::timeout, timer, &QTimer::stop);

    if (initioner->getPosition() == RIGHT)
        initioner->setApperance(apperanceR);
    else
        initioner->setApperance(apperance);
}


SpellDeepWound::SpellDeepWound()
{
    isCanUse = 1;
    cost = 30;
    callDown = 12;
    duration = 13;
    damage = mult = 45;
    sound = new QUrl("qrc:/sounds/res/sounds/w_3.wav");
    apperance = new QPixmap(":/unit/w_3.png");
    apperanceR = new QPixmap(":/unit/w_3_r.png");
}

void SpellDeepWound::use(Unit *target, Unit *initioner)
{
    target->takeDamage(400);
    this->startCallDown();
    initioner->useEnergy(cost);
    initioner->globalCallDown();
    this->startCallDown();
    if (initioner->getPosition() == RIGHT)
        initioner->setApperance(apperanceR);
    else
        initioner->setApperance(apperance);
}

void SpellDeepWound::hit()
{
    target->takeDamage(damage);
}


SpellThunderstorm::SpellThunderstorm()
{
    duration = 4;
    damage = 200;
    sound = new QUrl("qrc:/sounds/res/sounds/w_4.wav");
    cost = 40;
    callDown = 20;

    apperance = new QPixmap(":/unit/w_4.png");
    apperanceR = new QPixmap(":/unit/w_4_r.png");
}

void SpellThunderstorm::use(Unit *target, Unit *initioner)
{
    damage = damage * PERCENT_TO_FRAC * initioner->getDamage();
    target->stan(duration);
    target->takeDamage(damage);
    initioner->useEnergy(cost);
    initioner->globalCallDown();
    damage = 200;
    this->startCallDown();
    if (initioner->getPosition() == RIGHT)
        initioner->setApperance(apperanceR);
    else
        initioner->setApperance(apperance);
}

SpellMadness::SpellMadness()
{
    cost = 0;
    callDown = 90;
    duration = 5;
    damage = 120;
    apperance = new QPixmap(":/unit/w_5.png");
    apperanceR = new QPixmap(":/unit/w_5_r.png");
}

void SpellMadness::use(Unit *target, Unit *initioner)
{
    initioner->setDamage(initioner->getDamage() * damage * PERCENT_TO_FRAC);

    this->startCallDown();
    if (initioner->getPosition() == RIGHT)
        initioner->setApperance(apperanceR);
    else
        initioner->setApperance(apperance);

    initioner->globalCallDown();

}
