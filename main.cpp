#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "pokemon.h"
#include "read.h"
#include "pokeFight.h"
using namespace std;




int main()
{	
	//Reading the names of the files.
	int EXP = 0;
	string fileAbilities, filePokemons, pokemonData;
	string pokeAbilities, fight;
	cin >> fileAbilities >> filePokemons;

	//Flush data
	getline(cin, pokemonData);
	//Actual input
	getline(cin, pokemonData);

	//Store data
	Pokemon* myPokemon = new Pokemon();
	Pokemon* enemy = new Pokemon();
	vector<Pokemon*> pokemons;
	vector<Ability*> abilities;
	
	readData::readAbilities(abilities, fileAbilities);
	readData::readPokemons(pokemons, filePokemons);
	myPokemon = readData::declarePokemon(pokemonData, pokemons, abilities);

	while (true) {
		getline(cin, fight);
		if (fight == "") {
			break;
		}
		getline(cin, pokeAbilities);
		if (pokeAbilities == "") {
			break;
		}
		enemy = readData::declareEnemy(fight, pokemons, abilities);
		if (pokeFight::battle(myPokemon, enemy, pokeAbilities) == true) {
			EXP += enemy->getLevel();
			while (EXP >= (2 * myPokemon->getLevel())) {
				myPokemon->setLevel(myPokemon->getLevel() + 1);
				EXP -= (2 * myPokemon->getLevel());
			}
		}
	}
	
	return 0;
}