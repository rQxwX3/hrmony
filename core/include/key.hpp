#ifndef KEY_HPP
#define KEY_HPP

#include <cstdint>

enum class keyName : uint8_t {
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
    Command,
    Option,
    Control,
    Shift,
};

struct Key {
    keyName name;
    bool isMod;
};

#endif // KEY_HPP
