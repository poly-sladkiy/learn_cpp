#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

void print(const vector<int> &v) {
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << endl;
}

int main() {
    vector v{1, 2, 3, 4, 5, 6};
    print(v);

    {
        // remove all "2"
        const auto new_end(remove(begin(v), end(v), 2));
        v.erase(new_end, end(v));
    }
    print(v);

    {
        // remove all odd numbers
        auto odd_number([](int i) { return i % 2 != 0; });
        const auto new_end(
                remove_if(begin(v), end(v), odd_number));
        v.erase(new_end, end(v));
    }
    print(v);

    replace(begin(v), end(v), 4, 123);
    print(v);

    v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    decltype(v) v2, v3;

    auto odd_number([](int i) { return i % 2 != 0; });
    auto even_number([](int i) { return i % 2 == 0; });

    // Copy elements from v to v2 if odd_number return false
    remove_copy_if(begin(v), end(v),
                   back_inserter(v2), odd_number);

    // Copy elements from v to v3 if odd_number return true
    copy_if(begin(v), end(v),
            back_inserter(v3), even_number);

    print(v2);
    print(v3);

    {
        // Just try work with remove_copy
        random_device rd;
        mt19937 g{rd()};

        v.insert(end(v), {3, 4, 3, 3, 4, 3});
        shuffle(begin(v), end(v), g);

        print(v);

        remove_copy(begin(v), end(v), ostream_iterator<int>{cout, ", "}, 3);
    }
    return 0;
}
