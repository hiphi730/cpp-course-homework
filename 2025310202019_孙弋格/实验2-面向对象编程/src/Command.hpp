#pragma once

namespace adas {
class ExecutorImpl;
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
};
class MoveCommand final : public ICommand {
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override;
};
class TurnLeftCommand final : public ICommand {
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override;
};
class TurnRightCommand final : public ICommand {
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override;
};
class FastCommand final : public ICommand {
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override;
};
const ICommand* FindCommand(char command) noexcept;
} // namespace adas
