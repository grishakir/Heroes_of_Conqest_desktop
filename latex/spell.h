#ifndef SPELL_H
#define SPELL_H
#include <QObject>
#include <QPushButton>
#include <QTimer>
#include "unit.h"

#define SECTOMILL 1000
#define PERCENT_TO_FRAC 0.01

#define RIGHT 1
#define LEFT 0

class Spell;
class SpellCuttingBlow;
class SpellDeepWound;
class SpellReflektion;
class SpellDeepWound;

class Unit;
class Warrior;

class Spell : public QObject
{
    Q_OBJECT
protected:
    int cost;
    int callDown;
    bool isCanUse;
    QUrl* sound;
    QPixmap* apperance;
    QPixmap* apperanceR;
    QString normalShow;
    QString callDownShow;
    QTimer* callDownTimer = nullptr;
    QTimer *timer = nullptr;
    QPushButton* button = nullptr;
    public:
    void connectButton(QPushButton* inButton);
    int getCost();
    int getCallDown();;
    int getCost(int &cost);
    int getCallDown(int &timeCallDown);
    bool canUse(Unit *unit);
    virtual ~Spell();
 public slots:
    void startCallDown();
    void callDownTimeout();
    virtual void use(Unit *target, Unit *initioner) = 0;
};

class SpellCuttingBlow : public Spell
{
    Q_OBJECT
    double damage;
public:
    SpellCuttingBlow();
public slots:
    void use(Unit *target, Unit *initioner);
};

class SpellReflektion : public Spell
{
    Q_OBJECT
    double duration;
public:
    SpellReflektion();

public slots:
    void use(Unit *target, Unit *initioner);
};

class SpellDeepWound :public Spell
{
    Q_OBJECT
   double duration;
   double damage;
   Unit *target;
   int mult;
public:
    SpellDeepWound();
public slots:
    void use(Unit *target, Unit *initioner);
    void hit();


};

class SpellThunderstorm : public Spell
{
    Q_OBJECT
    double duration;
    double damage;
public:
    SpellThunderstorm();
public slots:
    void use(Unit *target, Unit *initioner);
};

class SpellMadness : public Spell
{
    Q_OBJECT
    double duration;
    int damage;
public:
    SpellMadness();
public slots:
    void use(Unit *target, Unit *initioner);
};

#endif // SPELL_H
