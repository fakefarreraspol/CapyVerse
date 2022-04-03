#ifndef __DIALOG_NODE_H__
#define __DIALOG_NODE_H__

#pragma once
#include <vector>
#include <string>

struct DialogNode
{
	// The dialog text
	std::string text;

	// The dialog ID of next nodes
	std::vector<size_t> nodes;

	// The dialog text for the options
	std::vector<std::string> options;
};

#endif // !DIALOG_SYSTEM_H

