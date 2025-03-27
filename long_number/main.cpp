




// Program w C++
#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <unordered_map>
#include <functional>
#include "long_number.hpp"



void runTests();
void runCalculator();

int main()
{
    std::cout << "================================== Tests ==================================" << std::endl;
    runTests();
    std::cout << "================================== Calculator ==================================" << std::endl;
    runCalculator();
    
    return 0;
}

void runCalculator() {
    // Odkomentowujcie to co zrobicie w operatorach, zeby bylo dostepne w kalulatorze
    // Dodajcie tez jakies przykladowe testy w runTests
    std::unordered_map<std::string, std::function<std::string(LongNumber&, LongNumber&)>> operations_map = {
        // {"+", [](LongNumber& f1, LongNumber& f2){return (f1 + f2).str();}},
        // {"-", [](LongNumber& f1, LongNumber& f2){return (f1 - f2).str();}},
        // {"*", [](LongNumber& f1, LongNumber& f2){return (f1 * f2).str();}},
        // {"/", [](LongNumber& f1, LongNumber& f2){return (f1 / f2).str();}},
        // {"==", [](LongNumber& f1, LongNumber& f2){return (f1 == f2) ? "True" : "False";}},
        // {"!=", [](LongNumber& f1, LongNumber& f2){return (f1 != f2) ? "True" : "False";}},        
        // {"<", [](LongNumber& f1, LongNumber& f2){return (f1 < f2) ? "True" : "False";}},        
        // {">", [](LongNumber& f1, LongNumber& f2){return (f1 > f2) ? "True" : "False";}}
    };
    
    std::cout << "Available Operations: ";
    std::cout << "[";
    bool first = true;
    for (const auto& op : operations_map) {
        if (!first) std::cout << ", ";
        std::cout << "\"" << op.first << "\"";
        first = false;
    }
    std::cout << "]\n";

    LongNumber in1, in2;
    std::string operation;
    try {
        while(true) {
            std::cout << "Input 1: ";
            std::cin >> in1;
            std::cout << "Operation: ";
            std::cin >> operation;
            std::cout << "Input 2: ";
            std::cin >> in2;
            std::cout << in1 << ' ' << operation << ' ' << in2 << " = " << operations_map[operation](in1, in2) << std::endl;
        }
    } catch (const std::string& error) { 
        std::cout << "Caught error: " << error << '\n';
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    } catch (...) {
        std::cout << "Caught unknown exception\n";
    }
}


void runTests() {
        // Test <<
    LongNumber x1(std::string("52.137"));
    std::cout << x1 << '\n';
    LongNumber x3(std::string("-12312.137"));
    std::cout << x3 << '\n';

    std::vector<int8_t> n = {1,2,3};
    LongNumber x4(n, 1, true);
    std::cout << x4 << '\n';
    try {
        LongNumber x2(std::string(""));
    } catch (const std::string& error) {  // Catch the original exception
        std::cout << "Caught error: " << error << '\n';
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    } catch (...) {
        std::cout << "Caught unknown exception\n";
    }
    
    
}
