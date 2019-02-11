#ifndef __Bigint__
#define __Bigint__

#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <complex>
#include <math.h>

template <typename T>
void dbg(const std::vector<T>& a) {
    for (auto& it : a) 
        std::cout << it << " ";
    printf("\n");
}

class Bigint {
public:
    Bigint();
    Bigint(int x);
    Bigint(const Bigint& x);
    Bigint(const std::string& s);
    Bigint operator + (const Bigint& rhs) const;
    Bigint& operator += (const Bigint& rhs);
    Bigint operator * (Bigint& ths);
    Bigint& operator *= (Bigint& rhs);
    bool operator == (const Bigint& rhs) const;
    friend std::ostream& operator << (std::ostream& os, Bigint& rhs);
private:
    void additionalCode();
    void fft(std::vector<std::complex<double>>& a, bool invert);
private:
    std::vector<int> data_;
    int BASE = 10;
};

#endif

