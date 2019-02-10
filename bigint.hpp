#ifndef __Bigint__
#define __Bigint__

#include <bits/stdc++.h>
#include <vector>
#include <iostream>

class Bigint {
public:
    Bigint();
    Bigint(int x);
    Bigint(const Bigint& x);
    Bigint(const std::string& s);
    Bigint operator + (const Bigint& rhs) const;
    Bigint& operator += (const Bigint& rhs);
    bool operator == (const Bigint& rhs) const;
    friend std::ostream& operator << (std::ostream& os, Bigint& rhs);
private:
    void additionalCode();
private:
    std::vector<int> data_;
    int BASE = 10;
};

#endif

