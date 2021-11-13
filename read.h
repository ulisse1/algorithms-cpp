#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

static class readData {

private:


public:
	static Pokemon* findPokemonByName(string name, vector<Pokemon*> pokemons) {

		for (Pokemon* p : pokemons) {
			if (p->getName() == name) {
				return p;
			}
		}
		return NULL;
	}

	static Ability* findAbilityByName(string name, vector<Ability*> abilities) {

		for (Ability* a : abilities) {
			if (a->nume == name) {
				return a;
			}
		}
		return NULL;
	}
	static void readAbilities(vector<Ability*> &abilities, string fileAbilities) {

		ifstream f;
		f.open(fileAbilities);
		string currLine, word;
		while (getline(f, currLine)) {
			istringstream words(currLine);       
			words >> word;
			Ability* a = new Ability();
			a->nume = word;

			while (words >> word) {
				if (word == "DMG") {
					Effect_Dmg* effect = new Effect_Dmg();
					words >> word;
					effect->dmg = stoi(word);
					words >> word;
					effect->type_atk = word;
					a->effects_dmg.push_back(effect);
				}
				else if (word == "ENEMY_MOD" || word == "SELF_MOD") {
					Effect_Cast* effect = new Effect_Cast();
					effect->mod = word;
					words >> word;
					effect->atr = word;
					words >> word;
					effect->stage = stoi(word);
					a->effects_cast.push_back(effect);
				}
			}
			abilities.push_back(a);
		}
		f.close();

	}


	static void readPokemons(vector<Pokemon*> &pokemons, string filePokemons) {

		ifstream f;
		f.open(filePokemons);
		string currLine, word;
		while (getline(f, currLine)) {
			istringstream words(currLine);
			string nume;
			int base_hp, base_atk, base_def, base_sp_atk, base_sp_def, base_spd;
			words >> nume >> base_hp >> base_atk >> base_def >> base_sp_atk >> base_sp_def >> base_spd;
			pokemons.push_back(new Pokemon(nume, base_hp, base_atk, base_def, base_sp_atk, base_sp_def, base_spd));
		}
		f.close();
	}

	static Pokemon* declarePokemon(string pokemonData, vector<Pokemon*> pokemons, vector<Ability*> abilities) {

		istringstream words(pokemonData);
		string word;
		words >> word;
		Pokemon* p = new Pokemon(*(findPokemonByName(word, pokemons)));
		words >> word;
		int level = stoi(word);
		p->setLevel(level);
		while (words >> word) {
			Ability* a = new Ability(*(findAbilityByName(word, abilities)));
			p->abilities.push_back(a);
		}
		return p;
	}

	static Pokemon* declareEnemy(string pokemonData, vector<Pokemon*> pokemons, vector<Ability*> abilities) {

		istringstream words(pokemonData);
		string word;
		words >> word;
		Pokemon* p = new Pokemon(*(findPokemonByName(word, pokemons)));
		words >> word;
		int level = stoi(word);
		p->setLevel(level);
		words >> word;
		if (word == "USOR") {
			words >> word;
			Ability* a = new Ability(*(findAbilityByName(word, abilities)));
			p->abilities.push_back(a);
		}
		else if (word == "MEDIU") {
			while (words >> word) {
				Ability* a = new Ability(*(findAbilityByName(word, abilities)));
				p->abilities.push_back(a);
			}
		}
		else if (word == "AVANSAT") {
			words >> word;
			Ability* maxDmg = new Ability(*(findAbilityByName(word, abilities)));
			int maxSum = 0, aux = 0;
			for (Effect_Dmg* effect : maxDmg->effects_dmg) {
				maxSum += effect->dmg;
			}
			while (words >> word) {
				aux = 0;
				Ability* a = new Ability(*(findAbilityByName(word, abilities)));
				for (Effect_Dmg* effect : a->effects_dmg) {
					aux += effect->dmg;
				}
				if (maxSum < aux) {
					maxSum = aux;
					maxDmg = a;
				}
			}
			p->abilities.push_back(maxDmg);
		}

		return p;
	}
};


