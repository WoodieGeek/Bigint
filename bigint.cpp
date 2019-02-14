#include "bigint.hpp"

Bigint::Bigint() {
    data_.push_back(0);
}

Bigint::Bigint(int x) {
    bool sign = x < 0;
    if (sign)
        x *= -1;
    while (x) {
        data_.push_back(x % BASE);
        x /= BASE;
    }
    data_.push_back(0);
    if (sign)
        additionalCode();
}

Bigint::Bigint(const Bigint& x) : data_(x.data_) {
}

Bigint::Bigint(const std::string& s) {
    bool sign = s[0] == '-';
    data_.reserve(s.size());
    for (auto digit = s.rbegin(); digit != s.rend() - sign; ++digit)
            data_.push_back(*digit - '0');
    data_.push_back(0);
    if (sign)
        additionalCode();
}

void Bigint::additionalCode() const {
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] = (BASE - 1) - data_[i];
    }
    for (size_t i = 0; i < data_.size(); i++) {
        if (data_[i] == BASE - 1)
            data_[i] = 0;
        else {
            data_[i]++;
            break;
        }
    }
}

Bigint Bigint::operator + (const Bigint& rhs) const {
    Bigint result(*this);
    result += rhs;
    return result;
}

Bigint& Bigint::operator += (const Bigint& rhs) {
    if (rhs.data_.size() > data_.size()) {
        size_t last = data_.size();
        data_.resize(rhs.data_.size());
        std::for_each(data_.begin() + last, data_.end(), [&](int& x) { x = data_[last - 1];});
    }
    int sum = 0;
    for (size_t i = 0; i < data_.size(); i++) {
        if (i < rhs.data_.size())
            data_[i] += sum + rhs.data_[i];
        else
            data_[i] += sum + rhs.data_.back();
        sum = data_[i] / BASE;
        data_[i] %= BASE;
    }
    if (data_.back() != 0 && data_.back() <= BASE / 2)
        data_.push_back(0);
    if (data_.back() !=9 && data_.back() > BASE / 2)
        data_.push_back(9);
    return *this;
}

std::ostream& operator << (std::ostream& os, const Bigint& rhs) {
    bool sign = rhs.data_.back() > rhs.BASE / 2;
    if (sign) {
        printf("-");
        rhs.additionalCode();
    }
    bool start = false;
    for (auto digit = rhs.data_.rbegin(); digit != rhs.data_.rend(); ++digit) {
        if (start)
            printf("%d", *digit);
        else if(*digit != 0) {
            start = true;
            printf("%d", *digit);
        }
    }
    if (!start) 
        printf("0");
    if (sign)
        rhs.additionalCode();
    return os;
}

bool Bigint::operator == (const Bigint& rhs) const {
    auto* left = &data_;
    auto* right = &rhs.data_;
    if (left->size() < right->size())
        std::swap(left, right);
    for (size_t i = 0; i < right->size(); i++)
        if ((*right)[i] != (*left)[i])
            return false;
    for (size_t i = right->size(); i < left->size(); i++) 
        if ((*left)[i] != right->back())
                return false;
    return true;
}

Bigint Bigint::operator * (const Bigint& rhs) const {
    Bigint result(*this);
    result *= rhs;
    return result;
}

Bigint& Bigint::operator *= (const Bigint& rhs) {
    bool signLeft = data_.back() >= BASE / 2;
    bool signRIght = rhs.data_.back() >= BASE / 2;
    if (signLeft)
        additionalCode();
    if (signRIght)
        rhs.additionalCode();
    size_t n = 1;
    while (n < std::max(data_.size(), rhs.data_.size()))
        n <<= 1;
    n <<= 1;
    std::vector<std::complex<double>> left(data_.begin(), data_.end());
    std::vector<std::complex<double>> right(rhs.data_.begin(), rhs.data_.end());
    left.resize(n);
    right.resize(n);
    fft(left, false);
    fft(right, false);
    data_.resize(n);
    for (size_t i = 0; i < left.size(); i++) 
        left[i] *= right[i];
    fft(left, true);
    data_.resize(n);
    int sum = 0;
    for (size_t i = 0; i < data_.size(); i++) {
        data_[i] = sum + (int)(left[i].real() + 0.5);
        sum  = data_[i] / BASE;
        data_[i] %= BASE;
    }
    while (sum) {
        data_.push_back(sum % BASE);
        sum /= BASE;
    }
    while (!data_.empty() && !data_.back())
        data_.pop_back();

    if (data_.empty() || data_.back())
        data_.push_back(0);

    if (signLeft ^ signRIght)
        additionalCode();
    return *this;
}

void Bigint::fft(std::vector<std::complex<double>>& a, bool invert) {
    size_t lg = 0, n = a.size();
    while ((1 << lg) < n)
        lg++;
    auto reverse_bits = [&](size_t x) -> size_t {
        size_t result = 0;
        for (size_t i = 0; i < lg; i++) 
            if (x & (1 << i))
                result |= 1 << (lg - 1 - i);
        return result;
    };
    for (size_t i = 0; i < n; i++) {
        size_t j = reverse_bits(i);
        if (i < j)
            std::swap(a[i], a[j]);
    }
    for (size_t len = 2; len <= n; len *= 2) {
        double ang = 2.0 * M_PI / len * (invert ? -1 : 1);
        std::complex<double>  wn(std::cos(ang), std::sin(ang));
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> w(1);
            for (size_t j = 0; j < len / 2; j++) {
                std::complex<double> u  = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wn;
            }
        }

    }
    if (invert) 
        for (size_t i = 0; i < n; i++) 
            a[i] /= n;
}

Bigint& Bigint::operator -= (const Bigint& rhs) {
    rhs.additionalCode();
    *this += rhs;
    rhs.additionalCode();
    return *this;
}

Bigint Bigint::operator - (const Bigint& rhs) const {
    Bigint result(*this);
    result -= rhs;
    return result;
}

Bigint Bigint::operator *= (int x) {
    Bigint X(x);
    *this *= X;
    return *this;
}

Bigint Bigint::operator * (int x) const {
    Bigint X(x);
    X *= *this;
    return X;
}

Bigint& Bigint::operator += (int x) {
    Bigint X(x);
    *this += X;
    return *this;
}

Bigint Bigint::operator + (int x) const  {
    Bigint result(x);
    result += *this;
    return result;
}

bool Bigint::operator < (const Bigint& rhs) const {
    Bigint delta(*this - rhs);
    return delta.data_.back() > BASE / 2;
}

bool Bigint::operator != (const Bigint& rhs) const {
    return !(*this == rhs);
}

bool Bigint::operator > (const Bigint& rhs) const {
    return !(*this < rhs) && (*this != rhs);
}

bool Bigint::operator >= (const Bigint& rhs) const {
    return !(*this < rhs);
}

bool Bigint::operator <= (const Bigint& rhs) const {
    return !(*this > rhs);
}

double Bigint::operator / (Bigint& rhs) {
    bool signLeft = data_.back() > BASE / 2;
    bool signRight = rhs.data_.back() > BASE / 2;
    if (signLeft)
        additionalCode();
    if (signRight)
        rhs.additionalCode();
    std::string ans;
    Bigint current;
    for (auto digit = data_.rbegin(); digit != data_.rend(); ++digit) {
        current *= BASE;
        current += *digit;
        if (current >= rhs) {
            for (int i = BASE - 1; i >= 1; i--) {
                if (rhs * i <= current) {
                    Bigint tmp = rhs * i;
                    ans.push_back('0' + i);
                    current -= tmp;
                    break;
                }
            }
        }
        else 
            ans.push_back('0');
    }
    ans.push_back('.');
    for (size_t iteration = 0; iteration < PRECISION;) { 
        if (current == 0)
            break;
        while (current < rhs) {
            current *= 10;
            ans.push_back('0');
            iteration++; 
        }
        ans.pop_back();
        for (int digit = BASE - 1; digit >= 1; digit--)
            if (rhs * digit <= current) {
                ans.push_back('0' + digit);
                Bigint tmp = rhs * digit;
                current -= tmp;
                break;
            }
    }
    if (signLeft)
        additionalCode();
    if (signRight)
        rhs.additionalCode();
    double d = std::stod(ans);
    if (signLeft ^ signRight)
        d *= -1;
    return d;
}






















