#pragma once

#include <memory>

template <typename T>
using RC = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr RC<T> createRC(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}
