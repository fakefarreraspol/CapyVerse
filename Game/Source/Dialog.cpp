#include "Dialog.h"

Dialog::Dialog() : finished(false), activeNode(NULL)
{
}

Dialog::~Dialog()
{
}

size_t Dialog::AddNode(DialogNode& node)
{
	size_t id = nodes.size();

	nodes.push_back(node);

	activeNode = &nodes[id];

	node.nodes.clear();
	node.options.clear();

	return id;
}

void Dialog::Update()
{
	if (!finished) {
		if (activeNode) {
			system("cls");
			std::cout << activeNode->text << std::endl;

			size_t optionSize = activeNode->options.size();

			for (size_t i = 0; i < optionSize; i++) {
				std::cout << (i + 1) << ". " << activeNode->options[i] << std::endl;
			}

			if (optionSize > 0) {
				int option;

				do {
					std::cout << "Choose an option: ";
					std::cin >> option;

					if (option < 1 || option > optionSize) {
						std::cout << "Choose an option from 1 to " << optionSize << std::endl;
					}
				} while (option < 1 || option > optionSize);

				option -= 1;

				activeNode = &nodes[activeNode->nodes[option]];
			}
			else {
				if (activeNode->nodes.size() > 0) {
					system("pause");
					activeNode = &nodes[activeNode->nodes[0]];
				}
				else {
					finished = true;
				}
			}
		}
		else {
			finished = true;
		}
	}
}