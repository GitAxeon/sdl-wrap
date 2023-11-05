#pragma once
#include "Macro.hpp"

#include <memory>

SDLW_NAMESPACE_BEGIN

template<typename T> using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

SDLW_NAMESPACE_END