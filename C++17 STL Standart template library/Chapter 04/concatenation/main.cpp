#include <iostream>
#include <functional>

/// f( g( h(params...) ) ) => ONE_LAMBDA_FUNC(params...)
template<typename T, typename ...Ts>
auto concat(T t, Ts ...ts) {
    if constexpr (sizeof...(ts) > 0) {
        return [=](auto ...parameters) {
            return t(concat(ts...)(parameters...));
        };
    } else {
        return t;
    }
}


// Like concat, but for 3 func
template<typename F, typename G, typename H>
auto special_concat(F f, G g, H h) {
    return [=](auto ... params) {
        return f( g( h(params...) ) );
    };
}

int main() {
    auto twice  ([] (int i) { return i * 2; });
    auto thrice ([] (int i) { return i * 3; });

    auto combined (
            concat(twice, thrice, std::plus<int>())
    );

    auto special_combined (
        special_concat(twice, thrice, std::plus<int>())
    );
    std::cout << combined(2, 3) << std::endl;
    std::cout << special_combined(2, 3) << std::endl;
}
