#include "Dialog.h"

Dialog::Dialog() : finished(false), activeNode(NULL)
{

}

Dialog::~Dialog()
{
}

bool Dialog::StartDialog()
{
	activeNode = &nodes.start->data;
	if (activeNode == nullptr)
		finished = true;
	else
		finished = false;

	return !finished;
}

size_t Dialog::AddNode(DialogNode& node)
{
	size_t id = nodes.Count();

	nodes.Add(node);

	activeNode = &nodes.end->data;

	node.nodes.Clear();
	node.options.Clear();

	return id;
}

void Dialog::Update()
{
	if (finished==false) {
		if (activeNode!=nullptr) {

			this->text->text = activeNode->text;

			if (activeNode->options.Count() == 0)
			{
				// esperar input
				// active node= nodes.start
			}
			else
			{
				// selector de opciones
				int choosenOption = -1;

				// hay que hacer un menu

				SetActiveNode(choosenOption);
			}

			//// get option

			//system("cls");
			//std::cout << activeNode->text.GetString() << std::endl;

			//size_t optionSize = activeNode->options.Count();

			//for (size_t i = 0; i < optionSize; i++) {
			//	std::cout << (i + 1) << ". " << activeNode->options.At(i) << std::endl;
			//}

			//if (optionSize > 0) {
			//	int option;

			//	do {
			//		std::cout << "Choose an option: ";
			//		std::cin >> option;

			//		if (option < 1 || option > optionSize) {
			//			std::cout << "Choose an option from 1 to " << optionSize << std::endl;
			//		}
			//	} while (option < 1 || option > optionSize);

			//	option -= 1;


			//	activeNode = &nodes[activeNode->nodes[option]];
			//}
			//else {
			//	if (activeNode->nodes.Count() > 0) {
			//		system("pause");
			//		activeNode = &nodes[activeNode->nodes[0]];
			//	}
			//	else { 
			//		finished = true;
			//	}
			//}
		}
		else {
			// pues alguna animacion para cerrar dialogo
			finished = true;
		}
	}
}

void Dialog::SetActiveNode(int option)
{
	int size = activeNode->options.Count();
	if ( size > 0)
	{
		if (option >= 0 || option < size)
		{
			activeNode = &activeNode->nodes.At(option)->data;
		}
	}
	if (size == 0)
	{
		finished = true;
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