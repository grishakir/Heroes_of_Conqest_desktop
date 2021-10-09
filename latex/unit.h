#ifndef UNIT_H
#define UNIT_H

#include "spell.h"

#include <QLabel>
#include <QObject>


#define SPELL_1 0
#define SPELL_2 1
#define SPELL_3 2
#define SPELL_4 3
#define SPELL_5 4

#define SpreadDamage = 0.03
#define AVOID 0.6

#define maxRage 100.0
#define maxEnergy 100.0
#define maxMana 100.0

#define minGCD 0.5
#define minLCD 0.35

#define WARRIOR 0
#define HUNTER 1
#define MAGE 2
#define ROGUE 3

#define MANA 0
#define RAGE 1
#define ENERGY 2
#define PERCENT_TO_FRAC 0.01

class Spell;

class Unit;
class Warrior;

class Unit : public QObject
{
Q_OBJECT
protected:
    int force;
    int agility;
    int mind;
    int stamina;
    int hp;
    double damage;
    double baseDamage;
    double baseDef;
    double maxHp;
    int typeOfEnergy;
    int critChance;
    int critMultiplicateDamage;
    int critDamage;
    int defence;
    double globalCoolDown;
    double resHp;
    double resEnergy;
    double energy;
    bool GCD;
    QPixmap *baseAppearance;
    QPixmap *baseAppearanceRight;
    QPixmap *appearance;
    bool isStanned;
    int position;
    Unit* target;
    QLabel *label;
    QLabel *energLabel;
    QLabel *hpLabel;
    QTimer *timer = nullptr;
    QTimer *endTimer = nullptr;
    QTimer *timerStan = nullptr;
    QTimer *resTimer = nullptr;
public:
    Unit();
    Spell **weapons;
    int getHp();
    void setEnergLabel(QLabel* label);
    void setHpLabel(QLabel* label);
    int getTypeOfEnergy();
    int getTypeOfEnergy(int &res);
    int getEnergy();
    double getDamage();
    void stan(int duration);
    void setDamage(int damage);
    bool getIsStanned();
    void setApperance(QPixmap* img);
    int getPosition();
    void setPosition(int pos);
    void setLabel(QLabel *label);
    QLabel* getLabel();
    void setTarget(Unit* unit);
    void reshp(int val);
    void resEnerg(int val);
    QTimer *resTimerIn;
    ~Unit();
signals:
    void destroed();
public slots:
    void takeDamage(int damage);
    void setDefence(int val);
    void resHpSL();
    void resEnergSL();
    void globalCallDown();
    void useEnergy(int val);
    void returnDefence();
    void offGCD();
    void returnToBaseApperance();
    void show();
    void deStanned();
    void useSkill1();
    void useSkill2();
    void useSkill3();
    void useSkill4();
    void useSkill5();

};

class Warrior : public Unit
{
   public:
   Warrior();
};
#endif // UNIT_H
