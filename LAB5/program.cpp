#include "iterator.h"
#include "KSet.h"

long find(Kset* set, int num) {
    ksi it = set->GetIterator();
    for (int i = 0;;i++) {
        try {
            if (it.get() == num) {
                return i;
            }
            it.forward();
        } catch (ksi::Exception) {
            return -1;
        }
    }
}

long find2(Kset* set, int num) {
    ksi it = set->GetIterator();
    for (int i = 0;;i++) {
        try {
            if (*it == num) {
                return i;
            }
            it++;
        } catch (ksi::Exception) {
            return -1;
        }
    }
}

int main() {
    KSet set({0,3,5,6,8,1});
    std::cout << find(&set, 3) << std::endl;
    std::cout << find2(&set, 3) << std::endl;
    std::cout << find(&set, 4) << std::endl;
    // test inside
    KSet s1;
    s1 >> 2 >> 5 >> 0;
    std::cout << "s1: " << s1 << '\n';
    std::cout << "s1 | set: " << (s1 | set) << '\n';
    std::cout << "s1 & set: " << (s1 & set) << '\n';
    std::cout << "s1 / set: " << (s1 / set) << '\n';
    std::cout << "set.size(): " << set.Size() << '\n';
    std::cout << "set.isempty(): " << set.IsEmpty() << '\n';
    std::cout << "set.isfull(): " << set.IsFull() << '\n';
    {
        KSet s2;
        s2 >> 6;
        std::cout << "s2: " << s2 << '\n';
        s2 = s1;
        std::cout << "s2 = s1: " << s2 << '\n';
        std::cout << "s2 |= set: " << (s2 |= set) << '\n';
        s2.Clear();
        std::cout << "s2 after clear: " << s2 << '\n';
    }
    {
        Kset s2;
        s2 = s1;
        std::cout << "s2 &= set: " << (s2 &= set) << '\n';
    }
    {
        Kset s2;
        s2 = s1;
        std::cout << "s2 /= set: " << (s2 /= set) << '\n';
    }
    return 0;
}