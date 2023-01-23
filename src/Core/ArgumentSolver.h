#pragma once

#include "Core/Container/String.h"
#include "Core/Container/Array.h"
#include "Core/Container/HashMap.h"

class ArgumentSolver {
  public:
    ArgumentSolver(int argc, char** argv) {
        for (int i = 0; i < argc; ++i) {
            String argument = argv[i];

            if (argument.length() > 1) {
                if (argument[0] == '-' && argument[1] == '-') {
                    if (argument.length() == 2) {
                        for (int j = i + 1; j < argc; ++j) {
                            arguments.push_back(argv[j]);
                        }
                        break;
                    }

                    String key = argument.substr(2);

                    if (flagRules.count(key)) {
                        if (flagRules[key]) {
                            if (i + 1 < argc)
                                flags[key] = argv[i + 1];
                            else
                                invalidFlags.push_back(argument);
                            continue;
                        }

                        flags[key] = "";
                    }
                }
            }

            arguments.push_back(argv[i]);
        }
    }

    void AddFlag(const String& key, bool value = false) {}

    void AddFlag(const String& key, char shortKey, bool value = false) { AddFlag(key, value); }

    const HashMap<String, String>& GetFlags() { return flags; }

    const Array<String>& GetInvalidFlags() { return invalidFlags; }

    const Array<String>& GetArguments() { return arguments; }

  private:
    void ParseFlags();

    void ParseArguments();

  private:
    HashMap<String, bool> flagRules;

    Array<String> arguments;
    HashMap<String, String> flags;
    Array<String> invalidFlags;
};
