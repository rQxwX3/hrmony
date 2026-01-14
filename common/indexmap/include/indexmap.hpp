#ifndef INDEXMAP_HPP
#define INDEXMAP_HPP

#include <array>
#include <concepts>
#include <cstddef>
#include <optional>

namespace hrm {
template <typename Converter, typename From>
concept IndexConverter =
    std::invocable<Converter, From> &&
    std::same_as<std::invoke_result_t<Converter, From>, std::size_t>;

template <typename From, typename To, size_t N, typename IndexConverter>
class IndexMap {
  private:
    IndexConverter m_converter;
    std::array<To, N> m_array;

  public:
    explicit IndexMap(IndexConverter converter)
        : m_converter{std::move(converter)} {}

  public:
    [[nodiscard]] auto at(From value) const -> std::optional<To> {
        const auto index{m_converter(value)};

        if (index > N) {
            return {};
        }

        return m_array[index];
    }

    [[nodiscard]] auto at(From value) -> std::optional<To> {
        const auto index{m_converter(value)};

        if (index > N) {
            return {};
        }

        return m_array[index];
    }

  public:
    [[nodiscard]] auto operator[](From value) const & -> const To & {
        return m_array[m_converter(value)];
    }

    [[nodiscard]] auto operator[](From value) & -> To & {
        return m_array[m_converter(value)];
    }
};
} // namespace hrm
#endif // INDEXMAP_HPP
