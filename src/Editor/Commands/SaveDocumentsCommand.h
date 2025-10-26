#pragma once
#include "NotStackableCommand.h"

class SaveDocumentsCommand final : public NotStackableCommand {
public:
    bool execute() override;

    SaveDocumentsCommand() = default;
    ~SaveDocumentsCommand() = default;
};

DECLARE_SHARED_PTR_FACTORY(SaveDocumentsCommand)
