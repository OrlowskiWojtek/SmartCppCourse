#include "frac.hpp"
#include <iostream>
#include <iomanip>

// do kompilacji i uruchomienia: g++ frac.cpp main.cpp -o nazwa && ./nazwa
int main(){
    std::cout << "Pierwszy ułamek\n";
    Fraction test1;
    std::cin >> test1;
    
    std::cout << "Drugi ułamek\n";
    Fraction test2;
    std::cin >> test2;

    Fraction test = test1 / test2;
    std::cout << std::right << std::setw(14) <<"dzielenie: " << test << std::endl;

    test = test1 * test2;
    std::cout << std::right << std::setw(14) << "mnożenie: " << test << std::endl;

    test = test1 + test2;
    std::cout << std::right << std::setw(14) << "dodawanie: " << test << std::endl;

    test = test1 - test2;
    std::cout << std::right << std::setw(14) << "odejmowanie: " << test << std::endl;

    bool pierwszy_wiekszy = test1 > test2;
    std::cout << std::right << std::setw(20) << "pierwszy_wiekszy: " << (pierwszy_wiekszy ? "prawda" : "fałsz") << std::endl;

    bool drugi_wiekszy = test1 < test2;
    std::cout << std::right << std::setw(20) << "drugi_wiekszy: " << (drugi_wiekszy ? "prawda" : "fałsz") << std::endl;

    bool sa_rowne = test1 == test2;
    std::cout << std::right << std::setw(20) << "są_równe: " << (sa_rowne ? "prawda" : "fałsz") << std::endl;

    bool nie_sa_rowne = test1 != test2;
    std::cout << std::right << std::setw(20) << "nie_są_równe: " << (nie_sa_rowne ? "prawda" : "fałsz") << std::endl;
}
