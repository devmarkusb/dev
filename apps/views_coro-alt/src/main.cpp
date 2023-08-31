#include "util/allthethings.h"

#define ENABLE_VIEWS_TRANSFORM_DEMO 0

namespace {
// The idea is to have a container of these but wanting a view of one of its members instead (without a transformed
// copy to store), iterable ideally.
struct S {
    int x{};
    int y{};
};

#if ENABLE_VIEWS_TRANSFORM_DEMO
void want_ys_view(std::ranges::input_range auto ys) {
    for (auto y : ys) {
        std::cout << y << ",";
    }
}
#endif

// Can't use that:
// void want_ys(std::span<const S> ss)

void want_ys_no_span(auto foreach_y) {
    foreach_y([](auto y) {
        std::cout << y << ",";
    });
}

void any_of_ys_no_span(auto any_of_ys) {
    std::cout << "?: " << any_of_ys([](auto y) {
        return y == 20;
    });
}
} // namespace

int main(int, char*[]) {
    std::vector<S> ss{{1, 10}, {2, 20}};
    std::vector<S> ss2{{11, 100}, {12, 200}};

#if ENABLE_VIEWS_TRANSFORM_DEMO
    auto x = std::views::transform(ss, [](auto elem) {
        return elem.y;
    });
    want_ys_view(x);
    std::cout << std::endl;
#endif

#if __cpp_lib_ranges
    want_ys_no_span([&ss, &ss2](auto call_per_elem) {
        std::ranges::for_each(ss, [call_per_elem](const auto& s) {
            call_per_elem(s.y);
        });
        std::ranges::for_each(ss2, [call_per_elem](const auto& s) {
            call_per_elem(s.y);
        });
    });
    std::cout << std::endl;

    any_of_ys_no_span([&ss, &ss2](auto call_per_elem) {
        return std::ranges::any_of(
                   ss,
                   [call_per_elem](const auto& s) {
                       return call_per_elem(s.y);
                   })
               || std::ranges::any_of(ss2, [call_per_elem](const auto& s) {
                      return call_per_elem(s.y);
                  });
    });
#endif
    return 0;
}
