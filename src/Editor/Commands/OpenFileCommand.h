#pragma once
#include <defines.h>
#include "NotStackableCommand.h"

class OpenFileCommand final : public NotStackableCommand
{
public:
	bool execute() override;

	OpenFileCommand() = default;
	~OpenFileCommand() = default;
};

DECLARE_SHARED_PTR_FACTORY(OpenFileCommand)
