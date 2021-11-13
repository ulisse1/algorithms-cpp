#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


struct Effect_Dmg {

    Effect_Dmg() {}

    int dmg;
    string type_atk;

    Effect_Dmg(int dmg, string type_atk) {
        this->dmg = dmg;
        this->type_atk = type_atk;
    }
};

struct Effect_Cast {

    Effect_Cast() {}

    string mod, atr;
    int stage;

    Effect_Cast(string mod, string atr, int stage) {
        this->mod = mod;
        this->atr = atr;
        this->stage = stage;
    }

};

struct Ability {

    string nume;
    vector<Effect_Dmg*> effects_dmg;
    vector<Effect_Cast*> effects_cast;



    //DEBUG
    /*
    void afisare() {

        cout << nume << " ";
        for (Effect_Dmg* effect : effects_dmg) {
            cout << "DMG " << effect->dmg << " " << effect->type_atk << " ";
        }
        for (Effect_Cast* effect : effects_cast) {
            cout << effect->mod << " " << effect->atr << " " << effect->stage << " ";
        }
    }
    */
    //DEBUGs

};
