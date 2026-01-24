#ifndef KEYS_HPP
#define KEYS_HPP

#include <cstddef>
#include <cstdint>

namespace key {
enum class Keys : uint8_t {
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    SEMICOLON,
    ESC,
    m_regularsCount,
    RIGHT_CMD,
    LEFT_CMD,
    RIGHT_ALT,
    LEFT_ALT,
    RIGHT_CTRL,
    LEFT_CTRL,
    RIGHT_SHIFT,
    LEFT_SHIFT,
    m_keysCount,
    NULLKEY,
};

constexpr size_t keysCount{static_cast<size_t>(Keys::m_keysCount) - 1};
constexpr size_t regularsCount{static_cast<size_t>(Keys::m_regularsCount)};
constexpr size_t modifiersCount{keysCount - regularsCount};

constexpr size_t modifiersEnumOffset{key::regularsCount + 1};

constexpr auto isModifier(const Keys key) -> bool {
    return key > Keys::m_regularsCount && key < Keys::NULLKEY;
}
} // namespace key

#endif // KEYS_HPP
