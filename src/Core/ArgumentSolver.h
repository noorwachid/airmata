#pragma once

#include "Core/Container/Array.h"
#include "Core/Container/HashTable.h"
#include "Core/Container/String.h"
#include "Core/Integral.h"
#include <iostream>

class ArgumentSolver
{
public:
    void AddOption(const String& key, usize consuming = 0);

    void Solve(char** data, int dataSize);

    void ParseArguments();

    void CopyOption(const String& argument);

    void CopyTheRestOfArguments();

    void CopyArgument(const String& argument);

private:
    HashTable<String, usize> optionRules;

    char** data = nullptr;
    usize dataSize = 0;
    usize cursor = 0;
    String activeKey;
    usize activeConsuming = 0;

public:
    String program;
    HashTable<String, Array<String>> options;
    Array<String> arguments;
    Array<String> invalidOptions;
};
