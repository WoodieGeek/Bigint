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

Bigint::Bigint(const Bigint& x) {
    data_ = x.data_;
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

void Bigint::additionalCode() {
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

std::ostream& operator << (std::ostream& os, Bigint& rhs) {
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






















