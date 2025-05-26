#pragma once
#include "Command.h"

class CloseCurrentDocumentCommand final : public Command
{
public:
	CloseCurrentDocumentCommand() = default;
	~CloseCurrentDocumentCommand() = default;

	bool execute() override;
};

DECLARE_SHARED_PTR_FACTORY(CloseCurrentDocumentCommand)

