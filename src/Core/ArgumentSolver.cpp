#include "Core/ArgumentSolver.h"

void ArgumentSolver::AddOption(const String& key, UintSize consuming) { optionRules[key] = consuming; }

void ArgumentSolver::Solve(char** newData, int newDataSize)
{
    data = newData;
    dataSize = newDataSize;
    program = data[0];

    for (cursor = 1; cursor < dataSize; ++cursor)
    {
        ParseArguments();
    }
}

void ArgumentSolver::ParseArguments()
{
    String argument = data[cursor];

    if (argument.length() > 1)
    {
        if (argument[0] == '-' && argument[1] == '-')
        {
            return CopyOption(argument);
        }
    }

    return CopyArgument(argument);
}

void ArgumentSolver::CopyOption(const String& argument)
{
    if (argument.length() == 2)
    {
        return CopyTheRestOfArguments();
    }

    String key = argument.substr(2);

    if (optionRules.count(key))
    {
        UintSize consuming = optionRules[key];

        if (consuming == 0)
        {
            activeKey.clear();
            activeConsuming = 0;
        }
        else
        {
            activeKey = key;
            activeConsuming = consuming;
        }
    }
    else
    {
        invalidOptions.push_back(argument);
    }
}

void ArgumentSolver::CopyTheRestOfArguments()
{
    for (++cursor; cursor < dataSize; ++cursor)
    {
        arguments.push_back(data[cursor]);
    }
}

void ArgumentSolver::CopyArgument(const String& argument)
{
    if (activeConsuming > 0)
    {
        options[activeKey].push_back(argument);

        --activeConsuming;
    }
    else
    {
        arguments.push_back(argument);
    }
}
