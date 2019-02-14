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
    Bigint operator + (int rhs) const;
    Bigint& operator += (int rhs);
    Bigint operator * (const Bigint& ths) const;
    Bigint& operator *= (const Bigint& rhs);
    Bigint operator * (int x) const;
    Bigint operator *= (int x);
    Bigint operator - (const Bigint& rhs) const;
    Bigint& operator -= (const Bigint& rhs);
    bool operator == (const Bigint& rhs) const;
    bool operator < (const Bigint& rhs) const;
    bool operator > (const Bigint& rhs) const;
    bool operator >= (const Bigint& rhs) const;
    bool operator <= (const Bigint& rhs) const;
    bool operator != (const Bigint& rhs) const;
    double operator / (Bigint& rhs);
    friend std::ostream& operator << (std::ostream& os, const Bigint& rhs);
private:
    void additionalCode() const;
    void fft(std::vector<std::complex<double>>& a, bool invert);
private:
    mutable std::vector<int> data_;
    int BASE = 10;
    size_t PRECISION = 20;
};

#endif

