#include "Core/ArgumentSolver.h"

void ArgumentSolver::addOption(const String& key, UintSize consuming) { optionRules[key] = consuming; }

void ArgumentSolver::solve(char** newData, int newDataSize) {
    data = newData;
    dataSize = newDataSize;
    program = data[0];

    for (cursor = 1; cursor < dataSize; ++cursor) {
        parseArguments();
    }
}

void ArgumentSolver::parseArguments() {
    String argument = data[cursor];

    if (argument.length() > 1) {
        if (argument[0] == '-' && argument[1] == '-') {
            return copyOption(argument);
        }
    }

    return copyArgument(argument);
}

void ArgumentSolver::copyOption(const String& argument) {
    if (argument.length() == 2) {
        return copyTheRestOfArguments();
    }

    String key = argument.substr(2);

    if (optionRules.count(key)) {
        UintSize consuming = optionRules[key];

        if (consuming == 0) {
            activeKey.clear();
            activeConsuming = 0;
        } else {
            activeKey = key;
            activeConsuming = consuming;
        }
    } else {
        invalidOptions.push_back(argument);
    }
}

void ArgumentSolver::copyTheRestOfArguments() {
    for (++cursor; cursor < dataSize; ++cursor) {
        arguments.push_back(data[cursor]);
    }
}

void ArgumentSolver::copyArgument(const String& argument) {
    if (activeConsuming > 0) {
        options[activeKey].push_back(argument);

        --activeConsuming;
    } else {
        arguments.push_back(argument);
    }
}

