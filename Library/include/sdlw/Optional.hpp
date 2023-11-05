#pragma once

#include <optional>

namespace sdlw
{
    template<typename T>
    using Optional = std::optional<T>;

    constexpr std::nullopt_t NullOpt = std::nullopt;
}