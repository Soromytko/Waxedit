#pragma once
#include <memory>
#include <stack>
#include <defines.h>
#include "Command.h"

class Invoker
{
public:
	Invoker() = default;
	virtual ~Invoker() = default;

	void executeCommand(CommandSharedPtr command);

private:
	std::stack<CommandSharedPtr> _history;
	std::stack<CommandSharedPtr> _redoHistory;

};

DECLARE_SHARED_PTR_FACTORY(Invoker)
