#ifndef __DIALOG_H__
#define __DIALOG_H__

#pragma once
#include <iostream>
#include <vector>
#include "DialogNode.h"
#include "GuiButton.h"

class Dialog
{
private:
	// All nodes
	std::vector<DialogNode> nodes;

	// Active node
	DialogNode* activeNode;

	// Whether the dialog has finished or not
	bool finished;
public:
	Dialog();
	~Dialog();

	// Add a node and return its ID
	size_t AddNode(DialogNode& node);

	// Set a node ID as active
	void SetActiveNode(size_t id) { if (id >= 0 && id < nodes.size()) activeNode = &nodes[id]; }

	// Update dialog
	void Update();

	// Return if the dialog has finished
	bool Finished() { return finished; }
};

#endif // !__DIALOG_H__