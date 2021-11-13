#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;


static class pokeFight {


public:

	static void useAbility(Ability* a, Pokemon*& player, Pokemon*& opponent) {
		for (Effect_Dmg* effect : a->effects_dmg) {
			int attack = 0;
			if (effect->type_atk == "SP_ATK") {
				attack = -(opponent->getLevel() * effect->dmg * player->getBaseSpAtk())
					/ (60 * opponent->getBaseSpDef());
			}
			else if (effect->type_atk == "ATK") {
				attack = -(opponent->getLevel() * effect->dmg * player->getBaseAtk())
					/ (60 * opponent->getBaseDef());
			}
			opponent->setBaseHp(opponent->getBaseHp() + attack);
		}
		if (opponent->getBaseHp() <= 0) {
			return;
		}
		for (Effect_Cast* effect : a->effects_cast) {
			if (effect->mod == "SELF_MOD") {
				pokeFight::alterStat(effect, player);
			}
			else if(effect->mod == "ENEMY_MOD") {
				pokeFight::alterStat(effect, opponent);
			}
		}
	}

	static void alterStat(Effect_Cast* effect, Pokemon* &p) {

		int modifier, base_atrLevel;
		if (effect->atr == "ATK") {
			base_atrLevel = p->getBaseAtk();
			if (effect->stage >= 0) {
				modifier = ((2 + effect->stage) * base_atrLevel / 2);
			}
			else {
				modifier = ((2 * base_atrLevel) / (2 - effect->stage));
			}
			p->setBaseAtk(modifier);
		}
		else if (effect->atr == "SP_ATK") {
			base_atrLevel = p->getBaseSpAtk();
			if (effect->stage >= 0) {
				modifier = ((2 + effect->stage) * base_atrLevel / 2);
			}
			else {
				modifier = ((2 * base_atrLevel) / (2 - effect->stage));
			}
			p->setBaseSpAtk(modifier);
		}
		else if (effect->atr == "DEF") {
			base_atrLevel = p->getBaseDef();
			if (effect->stage >= 0) {
				modifier = ((2 + effect->stage) * base_atrLevel / 2);
			}
			else {
				modifier = ((2 * base_atrLevel) / (2 - effect->stage));
			}
			p->setBaseDef(modifier);
		}
		else if (effect->atr == "SP_DEF") {
			base_atrLevel = p->getBaseSpDef();
			if (effect->stage >= 0) {
				modifier = ((2 + effect->stage) * base_atrLevel / 2);
			}
			else {
				modifier = ((2 * base_atrLevel) / (2 - effect->stage));
			}
			p->setBaseSpDef(modifier);
		}
		else if (effect->atr == "SPD") {
			base_atrLevel = p->getBaseSpd();
			if (effect->stage >= 0) {
				modifier = ((2 + effect->stage) * base_atrLevel / 2);
			}
			else {
				modifier = ((2 * base_atrLevel) / (2 - effect->stage));
			}
			p->setBaseSpd(modifier);
		}

	}

	static bool battle(Pokemon* player, Pokemon* opponent, string abilitiesUsed) {

		istringstream words(abilitiesUsed);
		string word;
		Pokemon* copyPlayer = new Pokemon(*player);
		Pokemon* copyOpponent = new Pokemon(*opponent);
		bool flag = true;
		int k = 0;
		copyPlayer->initiateStats();
		copyOpponent->initiateStats();
		copyPlayer->afisare();
		copyOpponent->afisare();
		while (copyPlayer->getBaseHp() > 0 && copyOpponent->getBaseHp() > 0) {
			words >> word;
			if (k >= copyOpponent->abilities.size()) {
				k %= copyOpponent->abilities.size();
			}
			if (copyPlayer->getBaseSpd() >= copyOpponent->getBaseSpd()) {
				useAbility(readData::findAbilityByName(word, copyPlayer->abilities), copyPlayer, copyOpponent);
				if (copyOpponent->getBaseHp() <= 0) {
					copyPlayer->afisare();
					copyOpponent->afisare();
					break;
				}
				useAbility(copyOpponent->abilities[k], copyOpponent, copyPlayer);
			}
			else {
				useAbility(copyOpponent->abilities[k], copyOpponent, copyPlayer);
				if (copyPlayer->getBaseHp() <= 0) {
					copyPlayer->afisare();
					copyOpponent->afisare();
					break;
				}
				useAbility(readData::findAbilityByName(word, copyPlayer->abilities), copyPlayer, copyOpponent);
			}
			k++;
			copyPlayer->afisare();
			copyOpponent->afisare();
		}
		cout << endl;
		if (copyOpponent->getBaseHp() > 0 && copyPlayer->getBaseHp() <= 0) {
			return false;
		}

		return true;

	}

};