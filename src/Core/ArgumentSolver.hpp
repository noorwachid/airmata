#pragma once

#include "Core/Container/Array.hpp"
#include "Core/Container/HashMap.hpp"
#include "Core/Container/String.hpp"
#include "Core/Integer.hpp"
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
