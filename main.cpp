#include <bits/stdc++.h>
#include "bigint.hpp"

int main() {
    Bigint a(72);
    Bigint b(8);
    Bigint c = a + b;
    Bigint c1("80");
    if (!(c1 == c)) 
        std::cout << "wtf\n";
    std::cout <<"ans\n";
    std::cout << c << std::endl; 
    return 0;
}
