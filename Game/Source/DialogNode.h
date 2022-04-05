#ifndef __DIALOG_NODE_H__
#define __DIALOG_NODE_H__

#include <vector>		// list
#include <string>		// sstring

#include "List.h"
#include "SString.h"

struct DialogNode
{
	// The dialog text
	SString text;

	// The dialog ID of next nodes
	List<DialogNode> nodes;

	// The dialog text for the options
	List<SString> options;

	DialogNode(SString text)
	{
		this->text = text;
	}


	DialogNode* AddOption(SString *newOption, SString nextText)
	{
		DialogNode* n = new DialogNode(nextText);

		if (newOption != nullptr)
			this->options.Add(*newOption);

		this->nodes.Add(*n);

		return n;
	}
};

#endif // !DIALOG_SYSTEM_H

