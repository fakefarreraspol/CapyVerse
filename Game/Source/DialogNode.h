#ifndef __DIALOG_NODE_H__
#define __DIALOG_NODE_H__

#include <vector>		// list
#include <string>		// sstring

#include "List.h"
#include "SString.h"

struct DialogNode
{
	DialogNode() {};
	DialogNode(SString text)
	{
		this->text = text;
	}

	// The dialog text
	SString text;
	SString optionText;

	// The dialog ID of next nodes
	List<DialogNode*> nodes;

	// The dialog text for the options


	
};

#endif // !DIALOG_SYSTEM_H

