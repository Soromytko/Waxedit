#pragma once
#include "Command.h"
#include <cassert>

class NotStackableCommand : public Command {
public:
    NotStackableCommand() = default;
    virtual ~NotStackableCommand() = default;

    bool isStackable() const override { return false; }

    bool undo() override {
        assert(false);
        return false;
    }
};
