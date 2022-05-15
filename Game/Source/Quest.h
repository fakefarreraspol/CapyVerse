#pragma once
#include"SString.h"
#include "PugiXml/src/pugixml.hpp"
#include "SDL/include/SDL.h"


enum class QuestProgress { AVAILABLE, NOT_AVAILABLE, ACTIVE, COMPLETE, REWARDED, DONE }; //States a quest can have


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
	int nextQuest = 0;					//id of the next quest
	int objective = 0;
	int maxObjective = 0;
	bool reward = false;			//Posible quest rewards
	int experience = 0;

	SString title;					//Title for the quest
	SString description;

	SDL_Rect rTitle, rDescription;
};

