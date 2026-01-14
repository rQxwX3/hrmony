#ifndef INDEXMAP_HPP
#define INDEXMAP_HPP

#include <array>
#include <concepts>
#include <cstddef>
#include <optional>

namespace hrm {
template <auto Converter, typename From>
concept IndexConverter =
    std::invocable<decltype(Converter), From> &&
    std::same_as<std::invoke_result_t<decltype(Converter), From>, std::size_t>;

template <typename From, typename To, size_t N, auto Converter>
    requires IndexConverter<Converter, From>
class IndexMap {
  private:
    std::array<To, N> m_array;

  public:
    [[nodiscard]] auto at(From value) const -> std::optional<To> {
        const auto index{Converter(value)};

        if (index > N) {
            return {};
        }

        return m_array[index];
    }

    [[nodiscard]] auto at(From value) -> std::optional<To> {
        const auto index{Converter(value)};

        if (index > N) {
            return {};
        }

        return m_array[index];
    }

  public:
    [[nodiscard]] auto constexpr operator[](From value) & -> To & {
        return m_array[Converter(value)];
    }
};
} // namespace hrm
#endif // INDEXMAP_HPP
