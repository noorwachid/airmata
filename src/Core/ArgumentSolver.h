#pragma once 

#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

class ArgumentSolver 
{
  public:
    ArgumentSolver(int argc, char** argv)
    {
        for (int i = 0; i < argc; ++i) 
        {
            std::string argument = argv[i];

            if (argument.length() > 1)
            {
                if (argument[0] == '-' && argument[1] == '-')
                {
                    if (argument.length() == 2)
                    {
                        for (int j = i + 1; j < argc; ++j) 
                        {
                            _arguments.push_back(argv[j]);
                        }
                        break;
                    }

                    std::string key = argument.substr(2);

                    if (_flagRules.count(key)) 
                    {
                        if (_flagRules[key])
                        {
                            if (i + 1 < argc) 
                                _flags[key] = argv[i + 1];
                            else
                                _invalidFlags.push_back(argument);
                            continue;
                        }

                        _flags[key] = "";
                    }
                }
            }

            _arguments.push_back(argv[i]);
        }
    }

    void AddFlag(const std::string& key, bool value = false)
    {
    }

    void AddFlag(const std::string& key, char shortKey, bool value = false)
    {
        AddFlag(key, value);
    }

    const std::unordered_map<std::string, std::string>& GetFlags()
    {
        return _flags;
    }

    const std::vector<std::string>& GetInvalidFlags()
    {
        return _invalidFlags;
    }

    const std::vector<std::string>& GetArguments()
    {
        return _arguments;
    }

  private:
    void ParseFlags();

    void ParseArguments();

  private:
    std::unordered_map<std::string, bool> _flagRules;

    std::vector<std::string> _arguments;
    std::unordered_map<std::string, std::string> _flags;
    std::vector<std::string> _invalidFlags;
};
