#include <bits/stdc++.h>
#include "bigint.hpp"
using namespace std;

int main() {
    Bigint a(5);
    Bigint b(100);
    cout << a + a * b - b;
    return 0;
}
