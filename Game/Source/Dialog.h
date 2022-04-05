#ifndef __DIALOG_H__
#define __DIALOG_H__

#pragma once
#include <iostream>
#include <vector>
#include "DialogNode.h"
#include "GuiButton.h"

#include "GuiText.h"

class Dialog
{
private:
	// All nodes

	List <DialogNode> nodes;

	// Active node
	DialogNode* activeNode = nullptr;
	GuiText* text = nullptr;

	// Whether the dialog has finished or not
	bool finished;
public:
	Dialog();
	~Dialog();

	// Add a node and return its ID
	size_t AddNode(DialogNode& node);

	bool StartDialog();

	// Set a node ID as active
	void SetActiveNode(int option);

	// Update dialog
	void Update();

	// Return if the dialog has finished
	bool Finished() { return finished; }
};

#endif // !__DIALOG_H__