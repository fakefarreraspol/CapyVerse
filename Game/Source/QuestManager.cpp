#include "QuestManager.h"
#include "Log.h"

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

	/*folder.Create(config.child("folder").child_value());*/

	/*LOG(folder.GetString());*/
	/*if (folder == NULL)
	{
		LOG("Could not load quest folder");
	}
	folder = "Assets/";*/
	/*questFile = "quests.xml";*/

	return ret;
}

bool QuestManager::Start()
{
	//Load the quest file, this can be for the hole game or
	// foreach level load quest file. 
	/*Load(questFile.GetString());*/


	
	return true;
}



void QuestManager::ActivateQuest(int questID)
{
	Quest* q = questList->At(questID)->data;

	if (q != nullptr)
		q->progress = QuestProgress::ACTIVE;
}

void QuestManager::CanelQuest(int questID)
{
	Quest* q = questList->At(questID)->data;

	if (q!=nullptr)
		q->progress = QuestProgress::NOT_AVAILABLE;
}

void QuestManager::CompleteQuest(int questID)
{
	Quest* q = questList->At(questID)->data;

	if (q != nullptr)
		q->progress = QuestProgress::COMPLETE;
}

void QuestManager::FinishQuest(int questID)
{
	Quest* q = questList->At(questID)->data;

	if (q != nullptr)
		q->progress = QuestProgress::REWARDED;
}

void QuestManager::AddItem(int id, SString title, SString description, int objective)
{
	Quest* q = new Quest(id, title, description, objective);
	questList->Add(q);
}

bool QuestManager::GetAvailableQuest(int questID)
{
	bool ret = false;
	Quest* q = questList->At(questID)->data;

	if (q != nullptr)
	{
		if (q->progress == QuestProgress::AVAILABLE)
			ret = true;
	}
	
	return ret;
}

bool QuestManager::GetActiveQuest(int questID)
{
	bool ret = false;
	Quest* q = questList->At(questID)->data;

	if (q != nullptr)
	{
		if (q->progress == QuestProgress::ACTIVE)
			ret = true;
	}

	return ret;
}

bool QuestManager::GetCompletedQuest(int questID)
{
	bool ret = false;
	Quest* q = questList->At(questID)->data;

	if (q != nullptr)
	{
		if (q->progress == QuestProgress::COMPLETE)
			ret = true;
	}

	return ret;
}

//bool QuestManager::Load(const char* path) 
//{
//	bool ret = true;
//	SString tmp("%s%s", folder.GetString(), path);
//
//	LOG("File path: %s", tmp.GetString());
//
//	pugi::xml_document questsFile;
//	pugi::xml_parse_result result = questsFile.load_file(tmp.GetString());
//	pugi::xml_node currentQuest;
//
//	if (result == NULL)
//	{
//		LOG("Could not load map xml file %s. pugi error: %s", path, result.description());
//		ret = false;
//	}
//	else {
//
//		currentQuest = questsFile.child("quests_list").first_child();
//		ListItem<Quest*>* quest = questList->start;
//
//		while (currentQuest != NULL)
//		{
//			Quest* quest = new Quest();
//
//			//laod properties
//			quest->id = currentQuest.attribute("id").as_int();
//			quest->progress = Quest::NOT_AVAILABLE;
//			quest->title = currentQuest.attribute("title").as_string();
//			quest->description = currentQuest.child("description").child_value();
//			
//			//generate text textures
//			quest->titleTex = app->fonts->LoadRenderedText(quest->rTitle, app->fonts->titles,quest->title.GetString(), SDL_Color{ 32,27,46 });
//			quest->descriptionTex = app->fonts->LoadRenderedParagraph(quest->rDescription, 0, quest->description.GetString(), SDL_Color{ 32,27,46 },500);
//
//			questList->add(quest);
//
//			currentQuest = currentQuest.next_sibling();
//		}
//	}
//
//	return ret;
//}

//bool QuestManager::LoadState(pugi::xml_node&)
//{
//	return false;
//}
//
//bool QuestManager::SaveState(pugi::xml_node&) const
//{
//	return false;
//}
