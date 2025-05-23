#pragma once
#include <memory>
#include <defines.h>

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	virtual bool execute() = 0;
	virtual bool undo() { return false; };

	virtual bool isStackable() const { return true; }
};

DECLARE_SHARED_PTR(Command)
