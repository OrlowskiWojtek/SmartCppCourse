#include "frac.hpp"
#include <cassert>
#include <iostream>

Fraction::Fraction()
    : num(1)
    , denum(1) {}

Fraction::Fraction(int num, int denum)
    : num(num)
    , denum(denum) {

    assert(denum != 0);

    simplify();
}
Fraction::~Fraction() {}

void Fraction::simplify() {
    int nwd = get_nwd();
    num = num / nwd;
    denum = denum / nwd;

    if (denum < 0) {
        denum *= -1;
        num *= -1;
    }
}

int Fraction::get_nwd() {
    int a = num;
    int b = denum;
    int c;

    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }

    return a;
}

int Fraction::get_num() { return num; }

int Fraction::get_denum() { return denum; }

Fraction Fraction::operator+(Fraction b) {
    return Fraction(num * b.denum + b.num * denum, denum * b.denum);
}

Fraction Fraction::operator-(Fraction b) {
    return Fraction(num * b.denum - b.num * denum, denum * b.denum);
}

Fraction Fraction::operator*(Fraction b) {
    return Fraction(num * b.num, denum * b.denum);
}

Fraction Fraction::operator/(Fraction b) {
    return Fraction(num * b.denum, denum * b.num);
}

bool Fraction::operator>(Fraction b) {
    Fraction comp = *this / b;
    return comp.num > comp.denum;
}

bool Fraction::operator<(Fraction b) {
    Fraction comp = *this / b;
    return comp.num < comp.denum;
}

bool Fraction::operator==(Fraction b) {
    Fraction comp = *this / b;
    return (comp.num == 1) && (comp.denum == 1);
}

bool Fraction::operator!=(Fraction b) { return !(*this == b); }

std::ostream &operator<<(std::ostream &os, Fraction &b) {
    os << b.num << " / " << b.denum;
    return os;
}

std::istream &operator>>(std::istream &is, Fraction &b) {
    int a;
    int c;
    std::cout << "Wpisz licznik\n";
    is >> a;
    std::cout << "Wpisz mianownik\n";
    is >> c;

    b.num = a;
    b.denum = c;

    return is;
}
