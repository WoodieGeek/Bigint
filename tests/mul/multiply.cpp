#include <bits/stdc++.h>
#include "../../bigint.hpp"

int main() {
    time_t res = std::time(nullptr);
    freopen("in", "r", stdin);
    std::string sa, sb, sc;
    int OK = 0, total = 0;
    while (std::cin >> sa >> sb >> sc) {
        total++;
        Bigint a(sa), b(sb), c(sc), c1(a * b);
        if (c1 == c) 
            OK++;
        else {
            std::cout << sa << " * " << sb << std::endl;
            std::cout << "expected: " << sc << std::endl;
            std::cout << "founded:  " << c1 << std::endl;
        }
            
    }
    printf("Total = %d\nOK = %d\n", total, OK);
    std::cout << "Time: " << std::time(nullptr) - res << std::endl;
    return 0;
}
