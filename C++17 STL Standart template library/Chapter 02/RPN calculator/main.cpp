#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <cmath>

template<typename IT>
double evaluate_rpn(IT it, IT end) {
    std::stack<double> val_stack;

    auto pop_stack([&]() {
        auto r(val_stack.top());
        val_stack.pop();
        return r;
    });

    std::map<std::string, double (*)(double, double)> ops{
            {"+", [](double a, double b) { return a + b; }},
            {"-", [](double a, double b) { return a - b; }},
            {"*", [](double a, double b) { return a * b; }},
            {"/", [](double a, double b) { return a / b; }},
            {"^", [](double a, double b) { return std::pow(a, b); }},
            {"%", [](double a, double b) { return std::fmod(a, b); }},
    };

    for (; it != end; ++it) {
        std::stringstream ss{*it};

        if (double val; ss >> val) {
            val_stack.push(val);
        } else {
            assert(val_stack.size() >= 2);
            const auto r{pop_stack()};
            const auto l{pop_stack()};

            try {
                const auto &op(ops.at(*it));
                const double res{op(l, r)};
                val_stack.push(res);
            } catch (const std::out_of_range &e) {
                std::cout << "Invalid operator: " << e.what() << '\n';
            }
        }
    }
    return val_stack.top();
}

int main() {
    try {
        std::cout << evaluate_rpn(std::istream_iterator<std::string>{std::cin}, {}) << '\n';
    } catch (const std::invalid_argument &e) {
        std::cout << "Invalid operator: " << e.what() << '\n';
    }
    return 0;
}

