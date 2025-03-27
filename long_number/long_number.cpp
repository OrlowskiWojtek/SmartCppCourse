#include "long_number.hpp"


LongNumber::LongNumber() {
    this->digits = std::vector<int8_t>(1, 0);
    this->numDecimalDigits = 0;
    this->isNegative = false;
}

LongNumber::LongNumber(const std::vector<int8_t> &digits, int numDecimalDigits, bool isNegative) {
    if(digits.empty()) {
        throw std::invalid_argument("Empty digits vector");
    }
    numDecimalDigits = std::min(std::max(numDecimalDigits, 0), (int)digits.size());
    this->digits = digits;
    this->numDecimalDigits = numDecimalDigits;
    this->isNegative = isNegative;
}

LongNumber::LongNumber(const std::string &str) {
    populateWithString(str);
}

std::string LongNumber::str() const {
    std::ostringstream ss;

    for(int i=0; i<digits.size(); i++) {
        ss << (char)(digits[i] + '0');
    }

    if (isNegative) {
        ss << '-';
    }
    if(numDecimalDigits == digits.size()) {
        ss << "0.";
    }

    for(int i=0; i<digits.size(); i++) {
        if(numDecimalDigits != 0 && numDecimalDigits == digits.size() - i) {
            ss << '.';
        }
        ss << (char)(digits[i] + '0');
    }
    return ss.str();
}

void LongNumber::populateWithString(const std::string &str) {
    std::vector<int8_t> digitsTemp = {};
    digitsTemp.reserve(str.size());
    int numDecimalDigitsTemp = 0;
    bool dotSeen = false;
    bool isNegativeTemp = false;

    for (int i=0; i<str.size(); i++) {
        char c = str[i];
        if (dotSeen) numDecimalDigitsTemp++;
        
        if(c >= '0' && c <= '9') {
            digitsTemp.push_back(c - '0');
        } else if (c == '.') {
            dotSeen = true;
        } else if (c == '-' && i == 0) {
            isNegativeTemp = true;
        } else {
            throw std::invalid_argument("Invalid input string");
        }
    }
    if (digitsTemp.size() == 0) {
        throw std::invalid_argument("Invalid input string");
    }    
    digits = digitsTemp;
    numDecimalDigits = numDecimalDigitsTemp;
    isNegative = isNegativeTemp;
}

std::ostream& operator<<(std::ostream& os, const LongNumber& num) {
    os << num.str();
    return os;
}

std::istream& operator>>(std::istream& is, LongNumber& frac) {
    std::string input;
    is >> input;
    frac.populateWithString(input);
    return is;
}
