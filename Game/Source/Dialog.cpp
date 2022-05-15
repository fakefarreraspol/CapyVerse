#include "Dialog.h"
#include "App.h"
#include "QuestManager.h"

Dialog::Dialog() : finished(false), activeNode(NULL)
{

}

Dialog::Dialog(uint32_t questID)
{
	this->questID = questID;
}

Dialog::~Dialog()
{
}

bool Dialog::StartDialog()
{
	activeNode = nodes.start->data;
	if (activeNode == nullptr)
		finished = true;
	else
		finished = false;

	return !finished;
}

size_t Dialog::AddFirstNode(DialogNode *node)
{
	size_t id = nodes.Count();

	nodes.Add(node);

	activeNode = nodes.start->data;

	/*node.nodes.Clear();
	node.options.Clear();*/

	return id;
}

void Dialog::Update()
{

	if (finished==false) {
		if (activeNode!=nullptr) {

			this->text->text = activeNode->text;

			if (activeNode->nodes.Count() == 0)
			{
				// esperar input
				// active node= nodes.start
			}
			else
			{
				// selector de opciones
				int choosenOption = -1;

				// hay que hacer un menu

				//SetActiveNode(choosenOption);
			}
		}
		else {
			// pues alguna animacion para cerrar dialogo
			finished = true;
		}
	}
}

void Dialog::SetActiveNode(int option)
{
	if (activeNode->nodes.Count()==0)
		finished = true;
	else
	{
		int size = activeNode->nodes.Count();

		if (size > 0)
		{
			if (option >= 0 || option < size)
			{
				activeNode = activeNode->nodes.At(option)->data;
			}
		}
		if (size == 0)
		{
			activeNode = nullptr;
			finished = true;
		}
	}
	

}

DialogNode* Dialog::GetActiveNode()
{
	if (activeNode == nullptr)
	{
		finished = true;
		return nullptr;
	}
	return activeNode;
}

DialogNode* Dialog::AddOption(DialogNode* node, SString nextText, SString newOption)
{
	DialogNode* n = new DialogNode(nextText.GetString());
	n->optionText=newOption.GetString();
	node->nodes.Add(n);

	return n;
}



void Dialog::AddOption(DialogNode* node, DialogNode* newOption)
{
	node->nodes.Add(newOption);
}
