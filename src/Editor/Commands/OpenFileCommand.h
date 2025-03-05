#pragma once
#include "NotStackableCommand.h"
#include "../../defines.h"

class OpenFileCommand final : public NotStackableCommand
{
public:
	bool execute() override;

	OpenFileCommand() = default;
	~OpenFileCommand() = default;
};

DECLARE_SHARED_PTR_FACTORY(OpenFileCommand)
