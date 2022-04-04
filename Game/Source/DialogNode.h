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
	List<size_t> nodes;

	// The dialog text for the options
	List<SString> options;
};

#endif // !DIALOG_SYSTEM_H

