#ifndef GROUP_HPP
#define GROUP_HPP

#include <action.hpp>
#include <keys.hpp>

#include <memory>

namespace grp {
class Group {
  private:
    std::unique_ptr<grp::types::Actions> m_actions;

    key::Keys m_leader;

    bool m_isGlobalSubgroup;

  public:
    Group();                                        // global group
    Group(key::Keys leader, bool isGlobalSubgroup); // subgroups

  public:
    [[nodiscard]] auto isGlobalSubgroup() const -> bool;

  public:
    [[nodiscard]] auto getLeader() const -> key::Keys;
    [[nodiscard]] auto
    getAction(key::Keys key) const & -> const types::Action &;

  public:
    auto addAction(key::Keys key, const grp::types::Combinations &combinations)
        -> void;
    auto addAction(std::unique_ptr<grp::Group> group) -> void;
    auto addAction(key::Keys key) -> void;

  public:
    [[nodiscard]] auto getExitKey() const -> key::Keys;
    auto setExitKey(key::Keys exitKey) -> void;
};

inline auto createGlobalGroup() -> grp::Group {
    using key::Keys, comb::Combination;
    auto globalGroup{Group()};
    globalGroup.addAction(key::Keys::I);

    auto rcmdGroup{std::make_unique<grp::Group>(key::Keys::RIGHT_CMD, true)};

    const auto combinations1{
        grp::types::Combinations{
            .array = {Combination({.array = {Keys::RIGHT_CMD, Keys::RIGHT_ALT,
                                             Keys::LEFT_CTRL, Keys::LEFT_SHIFT},
                                   .count = 4})},
            .count = 1},
    };

    rcmdGroup->addAction(Keys::J, combinations1);

    const auto combinations2{
        grp::types::Combinations{
            .array = {Combination(
                          {.array = {Keys::RIGHT_CMD, Keys::T}, .count = 2}),
                      Combination(
                          {.array = {Keys::RIGHT_CMD, Keys::W}, .count = 2})},
            .count = 2},
    };

    rcmdGroup->addAction(Keys::K, combinations2);

    const auto combinations3{
        grp::types::Combinations{
            .array = {Combination({.array = {Keys::S}, .count = 1})},
            .count = 1},
    };

    rcmdGroup->addAction(Keys::A, combinations3);

    const auto combinations4{grp::types::Combinations{
        .array = {Combination({.array = {Keys::H, Keys::I}, .count = 2})},
        .count = 1}};

    rcmdGroup->addAction(Keys::S, combinations4);
    rcmdGroup->addAction(key::Keys::I);

    globalGroup.addAction(std::move(rcmdGroup));

    return globalGroup;
};
} // namespace grp

#endif // GROUP_HPP
