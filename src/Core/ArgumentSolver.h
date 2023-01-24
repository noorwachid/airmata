#pragma once

#include "Core/Container/Array.h"
#include "Core/Container/HashMap.h"
#include "Core/Container/RC.h"
#include "Core/Container/String.h"
#include "Core/Integer.h"
#include <iostream>

class ArgumentSolver {
  public:
    void addOption(const String& key, UintSize consuming = 0);

    void solve(char** data, int dataSize);

    void parseArguments();

    void copyOption(const String& argument);

    void copyTheRestOfArguments();

    void copyArgument(const String& argument);

  private:
    HashMap<String, UintSize> optionRules;

    char** data = nullptr;
    UintSize dataSize = 0;
    UintSize cursor = 0;
    String activeKey;
    UintSize activeConsuming = 0;

  public:
    String program;
    HashMap<String, Array<String>> options;
    Array<String> arguments;
    Array<String> invalidOptions;
};
