#pragma once
#include "NotStackableCommand.h"

class OpenFileCommand final : public NotStackableCommand
{
public:
	bool execute() override;

	OpenFileCommand() = default;
	~OpenFileCommand() = default;
};

typedef std::shared_ptr<OpenFileCommand> OpenFileCommandSharedPtr;
