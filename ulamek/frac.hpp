#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <ostream>
class Fraction{
public:

    Fraction();
    Fraction(int num, int denum);
    ~Fraction();

    int get_num();
    int get_denum();

    Fraction operator+(Fraction b);
    Fraction operator-(Fraction b);
    Fraction operator*(Fraction b);
    Fraction operator/(Fraction b);
    bool operator<(Fraction b);
    bool operator>(Fraction b);
    bool operator==(Fraction b);
    bool operator!=(Fraction b);

    friend std::ostream& operator<<(std::ostream &os, Fraction &b);
    friend std::istream& operator>>(std::istream &is, Fraction &b);

private:
    int num;
    int denum;

    int get_nwd();
    void simplify();

};

#endif // !FRACTION_HPP
