#include "QuestManager.h"
#include "Log.h"
#include "Fonts.h"
#include "GuiManager.h"
#include "Input.h"

QuestManager::QuestManager(bool isActive) : Module(isActive)
{
	name.Create("quest_manager");
}

QuestManager::~QuestManager()
{
}

bool QuestManager::Awake(pugi::xml_node& config)
{

	LOG("Loading quests file");
	bool ret = true;

	folder.Create(config.child("folder").child_value());

	LOG(folder.GetString());
	if (folder == NULL)
	{
		LOG("Could not load quest folder");
	}
	folder = "Assets/";
	questFile = QUEST_FILE;


	return ret;
}

bool QuestManager::Start()
{
	//Load the quest file, this can be for the hole game or
	// foreach level load quest file. 
	missionName = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 1, "Mission name", { 600, 50, 10, 100 }, this);
	description = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 2, "This is a description hehe", { 500, 100, 10, 100 }, this);
	statusText = (GuiText*)app->guiManager->CreateGuiControl(GuiControlType::TEXT, 3, "Compleated", { 600, 150, 10, 100 }, this);

	missionName->state = GuiControlState::DISABLED;
	description->state = GuiControlState::DISABLED;
	statusText->state = GuiControlState::DISABLED;

	Load(questFile.GetString());

	return true;
}

Quest* QuestManager::ActiveQuest(uint32_t questID)
{
	if (questID < 0 || questID > questList.Count() - 1)
		return nullptr;
	Quest* q = questList.At(questID)->data;
	if (q->progress != QuestProgress::AVAILABLE)
		return nullptr;


	q->progress = QuestProgress::ACTIVE;
	missionName->SetText(q->title.GetString());
	description->SetText(q->description.GetString());
	statusText->SetText("New quest");

	updateCounter = 600;
	return q;
}

Quest* QuestManager::CompleteQuest(uint32_t questID)
{
	if (questID < 0 || questID > questList.Count() - 1)
		return nullptr;
	Quest* q = questList.At(questID)->data;
	if (q->progress == QuestProgress::COMPLETE)
		return q;
	q->progress = QuestProgress::COMPLETE;

	if (q->nextQuest != 0)
	{
		ActiveQuest(q->nextQuest);
		return q;
	}

	missionName->SetText(q->title.GetString());
	description->SetText(q->description.GetString());
	statusText->SetText("Quest compleated");
	updateCounter = 400;
	return q;
}

Quest* QuestManager::UpdateQuest(uint32_t questID)
{
	if (questID < 0 || questID > questList.Count() - 1)
		return nullptr;
	Quest* q = questList.At(questID)->data;
	
	q->objective--;

	if (q->objective <= 0)
	{
		CompleteQuest(questID);
		return q;
	}

	missionName->SetText(q->title.GetString());
	description->SetText(q->description.GetString());
	SString t("Objective compleated %i/%i", q->maxObjective - q->objective, q->maxObjective);
	statusText->SetText(t.GetString());
	updateCounter = 300;
	return q;
}

bool QuestManager::Update(float dt)
{
	if (app->GetDebug())
	{
		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		{
			ActiveQuest(0);
		}
		if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			ActiveQuest(2);
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		{
			UpdateQuest(1);
		}
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
		{
			CompleteQuest(1);
		}
	}
	if (updateCounter >= 0)
	{
		updateCounter -= dt / 10;
		missionName->state = GuiControlState::NORMAL;
		description->state = GuiControlState::NORMAL;
		statusText->state = GuiControlState::NORMAL;
	}
	else
	{
		missionName->state = GuiControlState::DISABLED;
		description->state = GuiControlState::DISABLED;
		statusText->state = GuiControlState::DISABLED;
	}

	return true;
}

bool QuestManager::IsCompleated(uint32_t questID)
{
	if (questList.At(questID)->data->progress == QuestProgress::COMPLETE)
		return true;
	return false;
}



bool QuestManager::Load(const char* path) 
{
	bool ret = true;
	SString tmp("%s%s", folder.GetString(), path);

	LOG("File path: %s", tmp.GetString());

	pugi::xml_document questsFile;
	pugi::xml_parse_result result = questsFile.load_file(tmp.GetString());
	pugi::xml_node currentQuest;

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", path, result.description());
		ret = false;
	}
	else {

		currentQuest = questsFile.child("quests_list").first_child();
		ListItem<Quest*>* quest = questList.start;

		while (currentQuest != NULL)
		{
			Quest* quest = new Quest();

			//laod properties
			quest->id = currentQuest.attribute("id").as_int();
			quest->progress = (QuestProgress)currentQuest.attribute("progress").as_int();
			quest->nextQuest = currentQuest.attribute("nextQuest").as_int();
			quest->reward = currentQuest.attribute("reward").as_bool();
			quest->title = currentQuest.attribute("title").as_string();
			quest->description = currentQuest.child("description").child_value();
			quest->objective = currentQuest.attribute("objective").as_int();
			quest->maxObjective = currentQuest.attribute("maxObjective").as_int();

			questList.Add(quest);

			currentQuest = currentQuest.next_sibling();
		}
	}

	return ret;
}

bool QuestManager::LoadState(pugi::xml_node&data)
{
	pugi::xml_node currentQuest = data.child("quests_list").first_child();
	ListItem<Quest*>* quest = questList.start;

	while (currentQuest != NULL)
	{
		Quest* quest = new Quest();

		//laod properties
		quest->id = currentQuest.attribute("id").as_int();
		quest->progress = (QuestProgress)currentQuest.attribute("progress").as_int();
		quest->nextQuest = currentQuest.attribute("nextQuest").as_int();
		quest->reward = currentQuest.attribute("reward").as_bool();
		quest->title = currentQuest.attribute("title").as_string();
		quest->description = currentQuest.child("description").child_value();

		questList.Add(quest);

		currentQuest = currentQuest.next_sibling();
	}
	return true;
}

bool QuestManager::SaveState(pugi::xml_node&) const
{

	return true;
}
