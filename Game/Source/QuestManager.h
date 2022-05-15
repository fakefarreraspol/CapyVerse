#include "Module.h"
#include "List.h"
#include "Quest.h"
#include "PugiXml/src/pugixml.hpp"
#include "App.h"
#include "GuiText.h"

#define QUEST_FILE "quests.xml"


class QuestManager : public Module 
{

public:
	QuestManager(bool isActive);
	~QuestManager();

	bool Awake(pugi::xml_node& config);
	bool Start();

public: 

	List<Quest*> questList;

	Quest* ActiveQuest(uint32_t questID);

	Quest* UpdateQuest(uint32_t questID);

	Quest* CompleteQuest(uint32_t questID);

	bool IsCompleated(uint32_t questID);

	bool Update(float dt);

	//Load quest files 
	bool Load(const char* path);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	GuiText* statusText;
	GuiText* missionName;
	GuiText* description;

	int updateCounter;

	SString folder;
	SString questFile;
};