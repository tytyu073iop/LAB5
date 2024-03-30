#include "KSet.h"

template <typename T, typename U>
long find(U begin, U end, T num) {
    auto it = begin;
    for (long i = 0; it != end;it.forward()) {
        if (it.get() == num) {
            return i;
        }
        i++;
    }
    return -1;
}

struct Psint {
    int i;
    bool operator==(const Psint& rhs) const {
        return i == rhs.i;
    }
    bool operator<(const Psint& rhs) const {
        return i < rhs.i;
    }
    friend std::ostream& operator<<(std::ostream& os, const Psint& p) {
        return os << p.i;
    }
    Psint(int i) : i(i) {}
};

template <typename T, typename U>
long find2(U begin, U end, T num) {
    auto it = begin;
    for (int i = 0; it != end;i++, it++) {
        if (*it == num) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void testKset() {
    {
        KSet<T> set({T(0),T(3),T(5),T(6),T(8),T(1)});
        std::cout << find(set.begin(), set.end(), T(3)) << std::endl;
        std::cout << find2(set.begin(), set.end(), T(3)) << std::endl;
        std::cout << find(set.begin(), set.end(), T(4)) << std::endl;
        // test inside
        KSet<T> s1;
        s1 >> 2 >> 5 >> 0;
        std::cout << "s1: " << s1 << '\n';
        std::cout << "s1 | set: " << (s1 | set) << '\n';
        std::cout << "s1 & set: " << (s1 & set) << '\n';
        std::cout << "s1 / set: " << (s1 / set) << '\n';
        std::cout << "set.size(): " << set.Size() << '\n';
        std::cout << "set.isempty(): " << set.IsEmpty() << '\n';
        std::cout << "set.isfull(): " << set.IsFull() << '\n';
        {
            KSet<T> s2;
            s2 >> 6;
            std::cout << "s2: " << s2 << '\n';
            s2 = s1;
            std::cout << "s2 = s1: " << s2 << '\n';
            std::cout << "s2 |= set: " << (s2 |= set) << '\n';
            s2.Clear();
            std::cout << "s2 after clear: " << s2 << '\n';
        }
        {
            KSet<T> s2;
            s2 = s1;
            std::cout << "s2 &= set: " << (s2 &= set) << '\n';
        }
        {
            KSet<T> s2;
            s2 = s1;
            std::cout << "s2 /= set: " << (s2 /= set) << '\n';
        }
    }
}

int main() {
    testKset<int>();
    testKset<Psint>();
    return 0;
}