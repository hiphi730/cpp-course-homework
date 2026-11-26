#pragma once
#include "command/Command.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace adas {
class CommandFactory final {
public:
    std::vector<Command> GetCommands(const std::string& commands) const;
private:
    const std::unordered_map<char, Command> table{
        {'M', MoveCommand{}}, {'L', TurnLeftCommand{}}, {'R', TurnRightCommand{}},
        {'F', FastCommand{}}, {'B', ReverseCommand{}}, {'T', TurnRoundCommand{}}
    };
};
} // namespace adas
