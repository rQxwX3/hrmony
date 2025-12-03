#include "../include/baseplatform.hpp"

auto BasePlatform::key2Native(Key key) -> NativeKeyCode {
    return sKey2NativeMap.at(static_cast<size_t>(key));
}

auto BasePlatform::native2Key(NativeKeyCode nativeKey) -> Key {
    return sNative2KeyMap.at(nativeKey);
}
