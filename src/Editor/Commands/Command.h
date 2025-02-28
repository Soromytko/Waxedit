#pragma once
#include <memory>

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual bool execute() = 0;
	virtual bool undo() { return false; };

	virtual bool isStackable() const { return true; }
};

typedef std::shared_ptr<Command> CommandSharedPtr;
