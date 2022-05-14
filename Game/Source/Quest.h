#pragma once
#include"SString.h"
#include "PugiXml/src/pugixml.hpp"
#include "SDL/include/SDL.h"


enum class QuestProgress { AVAILABLE, NOT_AVAILABLE, ACTIVE, COMPLETE, REWARDED }; //States a quest can have


class Quest
{
public:
	Quest() {}

	Quest(int id, SString title, SString description, int objective)
	{
		this->id = id;
		progress = QuestProgress::NOT_AVAILABLE;
		this->title = title;
		this->description = description;
		this->objective = objective;
	}

	~Quest(){}

public:
	int id;							//Quest identification
	QuestProgress progress;			//State of the current quest 
	int nextQuest;					//next quest, if there is any (chain quest)

	int objective;					//Posible quest objectives
	bool reward=false;						//Posible quest rewards
	int experience;

	int amount;

	SString title;					//Title for the quest
	SString description;			//What player has to know about the quest

	SDL_Texture* titleTex;
	SDL_Texture* descriptionTex;

	SDL_Rect rTitle, rDescription;
};

