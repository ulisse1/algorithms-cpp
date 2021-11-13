#include <iostream>
#include <string.h>
#include <vector>
#include "abilities.h"

using namespace std;


class Pokemon {

private:
    string name;
    int level = 0, base_hp = 0, base_atk = 0, base_def = 0, base_sp_atk = 0, base_sp_def = 0, base_spd = 0;

public:

    vector<Ability*> abilities;
    Pokemon() {}

    Pokemon(string name, int base_hp, int base_atk, int base_def, int base_sp_atk, int base_sp_def, int base_spd) {
        this->name = name;
        this->base_hp = base_hp;
        this->base_atk = base_atk;
        this->base_def = base_def;
        this->base_sp_atk = base_sp_atk;
        this->base_sp_def = base_sp_def;
        this->base_spd = base_spd;
    }

    void afisare() {
        cout << name << " " << base_hp << " " << base_atk << " " << base_def << " " << base_sp_atk << " " << base_sp_def << " " << base_spd;
        cout << endl;
    }

    void initiateStats() {
        base_hp = ((base_hp * level) / 50) + level + 10;
        base_atk = ((base_atk * level) / 50) + 10;
        base_def = ((base_def * level) / 50) + 10;
        base_sp_atk = ((base_sp_atk * level) / 50) + 10;
        base_sp_def = ((base_sp_def * level) / 50) + 10;
        base_spd = ((base_spd * level) / 50) + 10;
    }

    //Getters
    string getName() {
        return name;
    }
    int getBaseHp() {
        return base_hp;
    }
    int getBaseAtk() {
        return base_atk;
    }
    int getBaseDef() {
        return base_def;
    }
    int getBaseSpAtk() {
        return base_sp_atk;
    }
    int getBaseSpDef() {
        return base_sp_def;
    }
    int getBaseSpd() {
        return base_spd;
    }
    int getLevel() {
        return level;
    }
    //Setters
    void setBaseHp(int base_hp) {
        this->base_hp = base_hp;
    }
    void setBaseAtk(int base_atk) {
        this->base_atk = base_atk;
    }
    void setBaseDef(int base_def) {
        this->base_def = base_def;
    }
    void setBaseSpAtk(int base_sp_atk) {
        this->base_sp_atk = base_sp_atk;
    }
    void setBaseSpDef(int base_sp_def) {
        this->base_sp_def = base_sp_def;
    }
    void setBaseSpd(int base_spd) {
        this->base_spd = base_spd;
    }
    void setLevel(int level) {
        this->level = level;
    }



};