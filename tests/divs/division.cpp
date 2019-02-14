#include <bits/stdc++.h>
#include "../../bigint.hpp"

int main() {
    freopen("in", "r", stdin);
    std::string sa, sb, sc;
    int OK = 0, total = 0;
    std::cout.precision(20);
    std::cout << std::fixed;
    double E = 0.000000000001;
    while (std::cin >> sa >> sb >> sc) {
        total++;
        Bigint a(sa), b(sb), c(sc);
        double c1 = a / b;
        if (abs(c1 - std::stod(sc)) < E)
            OK++;
        else {
            std::cout << sa << " / " << sb << std::endl;
            std::cout << "expected: " << sc << std::endl;
            std::cout << "founded:  " << c1 << std::endl;
        }
            
    }
    printf("Total = %d\nOK = %d\n", total, OK);
    return 0;
}
