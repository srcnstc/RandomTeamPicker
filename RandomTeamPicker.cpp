// Author: Sercan SATICI

// Bu program mevkilerine ayrılmis oyuncu grubunu halısahada rastgele seçmek için oluşturulmuştur.

#include <iostream>
#include "time.h"
#include <string>
#include <map>

enum Position {
	GOALKEEPER,
	DEFENDER,
	RL_BACK,
	MIDFIELDER,
	RL_ATTACK,
	FORWARD
};

enum Teams
{
	A = 1,
	B
};

using Player = std::map<std::string, Position>;

Player pool_g = 
{
	{"Behcet"		, GOALKEEPER},
	{"Ziya"			, GOALKEEPER},
	{"Omer"			, DEFENDER},
	{"Sercan"		, DEFENDER},
	{"Nail"			, DEFENDER},
	{"Esen"			, DEFENDER},
	{"Mahir"		, RL_BACK},
	{"Erol"			, RL_BACK},
	{"Emin"			, RL_BACK},
	{"Faruk"		, RL_BACK},
	{"Ahmet"		, RL_BACK},
	{"OmerSungur"	, MIDFIELDER},
	{"Okan"			, MIDFIELDER},
	{"Kocak"		, RL_ATTACK},
	{"Emrah"		, RL_ATTACK},
	{"Ozan"			, RL_ATTACK},
	{"Aykut"		, FORWARD},
	{"Oguz"			, FORWARD}
};

/*Prototype of Functions*/
void printTeams(Player* Team);
void insertPosMap(Player* TeamMap, Player* PosMap, Position pos);
void randomTeamPicker(Player* TeamMap, Position pos);

/*Global variables*/
Player TeamA;
Player TeamB;
Teams lastOrderFlag = B;

int main()
{
	srand(time(NULL));

	Player PlayerList;
	std::cout << "Oyuncu Havuzu:";
	printTeams(&pool_g);

	std::cout << "\nTum (14 kisi) takim oyuncularinin isimlerini yukaridaki havuzdan giriniz!\n";
	std::string playerName;
	for (size_t i = 0; i < 14; i++)
	{
		std::getline(std::cin, playerName);
		auto it = pool_g.find(playerName);
		if (it != pool_g.end())
			PlayerList.insert({it->first, it->second});
		else
		{
			std::cout << "Girilen oyuncu havuzda bulunmamaktadır.\n";
			return EXIT_FAILURE;
		}
	}
		
	//printTeams(&PlayerList);

	Player GK_Map;			insertPosMap(&PlayerList, &GK_Map,			GOALKEEPER);
	Player Defender_Map;	insertPosMap(&PlayerList, &Defender_Map,	DEFENDER);
	Player RL_Back_Map;		insertPosMap(&PlayerList, &RL_Back_Map,		RL_BACK);
	Player Midfielder_Map;	insertPosMap(&PlayerList, &Midfielder_Map,	MIDFIELDER);
	Player RL_Attack_Map;	insertPosMap(&PlayerList, &RL_Attack_Map,	RL_ATTACK);
	Player Forward_Map;		insertPosMap(&PlayerList, &Forward_Map,		FORWARD);
	
	//printTeams(&GK_Map);
	//printTeams(&Defender_Map);
	//printTeams(&RL_Back_Map);
	//printTeams(&Midfielder_Map);
	//printTeams(&Forward_Map);

	randomTeamPicker(&GK_Map, GOALKEEPER);
	randomTeamPicker(&Defender_Map, DEFENDER);
	randomTeamPicker(&RL_Back_Map, RL_BACK);
	randomTeamPicker(&Midfielder_Map, MIDFIELDER);
	randomTeamPicker(&RL_Attack_Map, RL_ATTACK);
	randomTeamPicker(&Forward_Map, FORWARD);

	std::cout << "\nP.tesi - 22.00-23.00 Aydin Oral Oyuncu Listesi: \n";
	std::cout << "\nTeam-A: \n";
	printTeams(&TeamA);

	std::cout << "\nTeam-B:\n";
	printTeams(&TeamB);

}

void printTeams(Player* Team)
{
	int i = 0;
	for (auto it = Team->begin(); it != Team->end(); ++it)
	{
		std::cout << it->first;
		if(++i != Team->size())
			std::cout << ",";
		else
			std::cout << "\n";
	}
}

void insertPosMap(Player* TeamMap, Player* PosMap, Position pos)
{
	for (auto it : *TeamMap)
	{
		if (it.second == pos)
			PosMap->insert({ it.first, it.second });
	}
}

void randomTeamPicker(Player* TeamMap, Position pos)
{
	/*distribute weak players to different teams*/
	if (pos == RL_BACK)
	{
		auto iter1 = TeamMap->find("Emin");
		auto iter2 = TeamMap->find("Faruk");
		if ((iter1 != TeamMap->end()) && (iter2 != TeamMap->end()))
		{
			TeamA.insert(*iter1);
			TeamB.insert(*iter2);

			TeamMap->erase(iter1);
			TeamMap->erase(iter2);
		}
	}


	for ( auto it = TeamMap->begin(); it != TeamMap->end(); ++it)
	{
		if (lastOrderFlag == B)
			TeamA.insert(*it);
		else
			TeamB.insert(*it);

		lastOrderFlag = (lastOrderFlag == A) ? B : A;
	}
}
