#include "unit.h"
#include "spell.h"

#include <QPixmap>
#include <QString>
#include <QTimer>

Warrior::Warrior()
{

    force = 50;
    agility = 11;
    mind = 9;
    stamina = 45;
    baseDamage = 28.8;
    baseDef = 46;
    typeOfEnergy = RAGE;
    critChance = agility * 0.5;
    critMultiplicateDamage = 1 + force * 0.005;
    critDamage = baseDamage * critMultiplicateDamage * PERCENT_TO_FRAC;
    defence = baseDef;
    globalCoolDown = 1.9 - agility * 0.016;
    maxHp = stamina * 10;
    resHp = force * 0.08;
    resEnergy = 5;
    hp = maxHp;
    damage = baseDamage;
    energy = 100;
    baseAppearance = new QPixmap(":/unit/w_0.png");
    appearance = baseAppearance;
    isStanned = 0;
    baseAppearanceRight = new QPixmap(":/unit/w_0_r.png");
    // давай посмотрим, где Ты выделил память под этого дядечку (weapons)
    //
    weapons = (Spell**)calloc(5, sizeof (Spell*));
    weapons[SPELL_1] = new SpellCuttingBlow();
    weapons[SPELL_2] = new SpellReflektion();
    weapons[SPELL_3] = new SpellDeepWound();
    weapons[SPELL_4] = new SpellThunderstorm();
    weapons[SPELL_5] = new SpellMadness();
//    QTimer resTimer;
//    connect(&resTimer, &QTimer::timeout, this, &Unit::resHpSL);
    resTimerIn = new QTimer();
    connect(resTimerIn, &QTimer::timeout, this, &Unit::resHpSL);
    connect(resTimerIn, &QTimer::timeout, this, &Unit::resEnergSL);
    resTimerIn->start(1000);


}

Unit::Unit()
{
    stamina = 0;
}

int Unit::getHp()
{
    return hp;
}

void Unit::setEnergLabel(QLabel *label)
{
    energLabel = label;
}

void Unit::setHpLabel(QLabel *label)
{
    hpLabel = label;
}

int Unit::getTypeOfEnergy()
{
    return typeOfEnergy;
}

int Unit::getTypeOfEnergy(int &res)
{
    res = typeOfEnergy;
    return res;
}

int Unit::getEnergy()
{
    return energy;
}

void Unit::useEnergy(int val)
{
    energy -= val;
}

void Unit::returnDefence()
{
    setDefence(baseDef);
}

void Unit::offGCD()
{
    GCD = false;
}

void Unit::returnToBaseApperance()
{
    appearance = baseAppearance;
    this->show();
}

void Unit::show()
{
    label->setPixmap(*appearance);
}

void Unit::deStanned()
{
    isStanned = 0;
}

void Unit::useSkill1()
{
    if (this->weapons[SPELL_1]->canUse(this))
    {
        this->weapons[SPELL_1]->use(target, this);
        energLabel->setText(QString::number(this->energy));
    }

}

void Unit::useSkill2()
{
    if (this->weapons[SPELL_2]->canUse(this))
    {
        this->weapons[SPELL_2]->use(target, this);
        energLabel->setText(QString::number(this->energy));
    }
}

void Unit::useSkill3()
{
    if (this->weapons[SPELL_3]->canUse(this))
    {
        this->weapons[SPELL_3]->use(target, this);
        energLabel->setText(QString::number(this->energy));
    }

}

void Unit::useSkill4()
{
    if (this->weapons[SPELL_4]->canUse(this))
    {

        this->weapons[SPELL_4]->use(target, this);
        energLabel->setText(QString::number(this->energy));
    }
}

void Unit::useSkill5()
{
    if (this->weapons[SPELL_5]->canUse(this))
    {
        this->weapons[SPELL_5]->use(target, this);
        energLabel->setText(QString::number(this->energy));
    }
}
double Unit::getDamage()
{
    return (rand() % 100 < critChance) ?
	(1 + force * 0.005) * damage : damage;
}

void Unit::stan(int duration)
{
    delete timerStan;
    timerStan = new QTimer;
    isStanned = 1;
    connect(timerStan, &QTimer::timeout, this, &Unit::deStanned);
    connect(timerStan, &QTimer::timeout, timer, &QTimer::stop);
    timerStan->start(SECTOMILL * duration);
}

void Unit::setDamage(int damage)
{
    this->damage = damage;
}

bool Unit::getIsStanned()
{
    return isStanned;
}

void Unit::setApperance(QPixmap *img)
{
    this->appearance = img;
    this->show();
    delete endTimer;
    endTimer = new QTimer;
    connect(endTimer, &QTimer::timeout, this, &Unit::returnToBaseApperance);
    connect(endTimer, &QTimer::timeout, endTimer, &QTimer::stop);
    connect(endTimer, &QTimer::timeout, this, &Unit::show);
    endTimer->start(1*SECTOMILL);
}

int Unit::getPosition()
{
    return position;
}

void Unit::setPosition(int pos)
{
    position = pos;
    if (pos == RIGHT)
        baseAppearance = baseAppearanceRight;
}

void Unit::setLabel(QLabel *label)
{
    this->label = label;
}

QLabel *Unit::getLabel()
{
    return label;
}

void Unit::setTarget(Unit *unit)
{
    target = unit;
}

void Unit::takeDamage(int damage)
{
    this->hp -= damage * (100 - this->defence) / 100;
    hpLabel->setText(QString::number(this->hp));

    if (hp <= 0)
        emit destroed();
}

void Unit::setDefence(int val)
{
    defence = val;
}

void Unit::resHpSL()
{
    reshp(resHp);

}

void Unit::resEnergSL()
{
    resEnerg(resEnergy);

}

void Unit::reshp(int val)
{
    hp = (hp + val > maxHp) ? maxHp : hp + val;
    hpLabel->setText(QString::number(this->hp));
}


void Unit::resEnerg(int val)
{
    energy = (energy + val > maxEnergy) ? 100 : energy + val;
    energLabel->setText(QString::number(this->energy));
}

Unit::~Unit()
{
    delete target;
    delete label;
    delete energLabel;
    delete hpLabel;
    delete timer;
    delete endTimer;
    delete timerStan;
    delete resTimerIn;
    delete baseAppearance;
    delete baseAppearanceRight;
    delete appearance;
    delete weapons;

    for (int i = 0; i < 5; i++)
    {
        free(weapons[i]);
    }

    free(weapons);
}

void Unit::globalCallDown()
{
    delete timer;
    timer = new QTimer();
    GCD = true;
    connect(timer, &QTimer::timeout, this, &Unit::offGCD);
    connect(timer, &QTimer::timeout, timer, &QTimer::stop);
    timer->start(this->globalCoolDown * SECTOMILL);
}

