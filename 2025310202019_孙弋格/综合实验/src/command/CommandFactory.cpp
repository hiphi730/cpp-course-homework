#include "command/CommandFactory.hpp"
#include <cstddef>

namespace adas {
std::vector<Command> CommandFactory::GetCommands(const std::string& commands) const
{
    std::vector<Command> result;
    result.reserve(commands.size());
    for (std::size_t i = 0; i < commands.size(); ++i) {
        const char code = commands[i];
        if (code == 'T') {
            // 一次消费完整TR，紧随的R不再单独执行。
            if (i + 1 >= commands.size() || commands[i + 1] != 'R') { continue; }
            ++i;
        }
        const auto it = table.find(code);
        if (it != table.end()) { result.push_back(it->second); }
    }
    return result;
}
} // namespace adas
