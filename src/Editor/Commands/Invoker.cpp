#include "Invoker.h"

void Invoker::executeCommand(CommandSharedPtr command) {
    if (command->execute()) {
        if (command->isStackable()) {
            _history.push(command);
        }
    }
}
