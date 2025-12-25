#ifndef KEYS_HPP
#define KEYS_HPP

#include <cstdint>

namespace key {
enum class Keys : uint8_t {
    NULLKEY = 0,
    A,
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
    m_size
};

enum class Modifiers : uint8_t { NULLKEY = 0, CMD, ALT, CTRL, SHIFT, m_size };
} // namespace key

#endif // KEYS_HPP
