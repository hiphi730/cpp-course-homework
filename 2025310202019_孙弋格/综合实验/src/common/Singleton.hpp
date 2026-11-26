#pragma once

namespace adas {
// 只读共享服务的泛型单例，车的位置和 B/F 状态仍属于各执行器。
template <typename T>
class Singleton final {
public:
    static const T& Instance()
    {
        static const T instance;
        return instance;
    }
    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
} // namespace adas
