#include "long_number.hpp"
#include <algorithm>

LongNumber::LongNumber() {
    this->digits = std::vector<int8_t>(1, 0);
    this->numDecimalDigits = 0;
    this->isNegative = false;
}

LongNumber::LongNumber(const std::vector<int8_t> &digits, int numDecimalDigits, bool isNegative) {
    if (digits.empty()) {
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

  //  for (int i = 0; i < digits.size(); i++) {
  //      ss << (char)(digits[i] + '0');
  //  }

    if (isNegative) {
        ss << '-';
    }
    if (numDecimalDigits == digits.size()) {
        ss << "0.";
    }

    for (int i = 0; i < digits.size(); i++) {
        if (numDecimalDigits != 0 && numDecimalDigits == digits.size() - i) {
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

    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (dotSeen) numDecimalDigitsTemp++;

        if (c >= '0' && c <= '9') {
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

std::ostream &operator<<(std::ostream &os, const LongNumber &num) {
    os << num.str();
    return os;
}

std::istream &operator>>(std::istream &is, LongNumber &frac) {
    std::string input;
    is >> input;
    frac.populateWithString(input);
    return is;
}

LongNumber LongNumber::operator*(const LongNumber &obj) const {
    int leftSign = this->isNegative ? -1 : 1;
    int rightSign = obj.isNegative ? -1 : 1;
    bool isNegativeOutput = ((leftSign * rightSign) == -1);
    int decimalDigitsOutput = this->numDecimalDigits + obj.numDecimalDigits;

    std::vector<int8_t> longerNumber = (this->digits.size() >= obj.digits.size()) ? (this->digits)
                                                                                         : (obj.digits);
    std::vector<int8_t> shorterNumber = (this->digits.size() < obj.digits.size()) ? (this->digits)
                                                                                         : (obj.digits);

    std::reverse(longerNumber.begin(), longerNumber.end());     // tak się łatwiej mnoży -> nie jest najkorzystniejsze ale ułatwia
    std::reverse(shorterNumber.begin(), shorterNumber.end());   // warto tak zrobić w pierwszej wersji

    std::vector<int8_t> digitsTemp;
    std::vector<int8_t> digitsOutput;

    digitsOutput.resize(longerNumber.size() + shorterNumber.size() - 1, 0);
    int8_t overTen = 0;
    int8_t overTenAddition = 0;
    int8_t temp;

    for(int i = 0; i < shorterNumber.size(); i++){
        digitsTemp.resize(longerNumber.size() + i);
        std::fill(digitsTemp.begin(), digitsTemp.end(), 0);

        for(size_t j = 0; j < longerNumber.size(); j++){
            temp = shorterNumber.at(i) * longerNumber.at(j) + overTen;
            overTen = 0;
            if(temp >= 10){
                overTen = temp / 10;
                temp = temp % 10;
            }
            digitsTemp[i + j] = temp;
        }
        
        if(overTen > 0){
            digitsTemp.insert(digitsTemp.end(), overTen);
            overTen = 0;
        }

        // Można to też zrobić poprzez operator + (jeszcze nie zdefiniowany)
        for(size_t j = 0; j < digitsTemp.size(); j++){
            if(j >= digitsOutput.size()){
                digitsOutput.insert(digitsOutput.end(), 0);
            }
            temp = digitsOutput[j] + digitsTemp[j] + overTenAddition;
            overTenAddition = 0;
            if(temp >= 10){
                overTenAddition = temp / 10;
                temp = temp % 10;
            }
            digitsOutput[j] = temp;
        }
    }

    std::reverse(digitsOutput.begin() , digitsOutput.end());

    return LongNumber(digitsOutput, decimalDigitsOutput, isNegativeOutput);
}

LongNumber LongNumber::operator+(const LongNumber &other) const {
    if (this->isNegative != other.isNegative) {
        LongNumber copy = other;
        copy.isNegative = !copy.isNegative;
        return *this - copy;
    }

    int maxDecimalDigits = std::max(this->numDecimalDigits, other.numDecimalDigits);
    int thisExtraZeros = maxDecimalDigits - this->numDecimalDigits;
    int otherExtraZeros = maxDecimalDigits - other.numDecimalDigits;

    std::vector<int8_t> digits1 = this->digits;
    std::vector<int8_t> digits2 = other.digits;

    digits1.insert(digits1.end(), thisExtraZeros, 0);
    digits2.insert(digits2.end(), otherExtraZeros, 0);

    if (digits1.size() < digits2.size()) {
        digits1.insert(digits1.begin(), digits2.size() - digits1.size(), 0);
    } else if (digits2.size() < digits1.size()) {
        digits2.insert(digits2.begin(), digits1.size() - digits2.size(), 0);
    }

    std::vector<int8_t> resultDigits(digits1.size(), 0);
    int8_t carry = 0;

    for (int i = digits1.size() - 1; i >= 0; i--) {
        int sum = digits1[i] + digits2[i] + carry;
        resultDigits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        resultDigits.insert(resultDigits.begin(), carry);
    }

    return LongNumber(resultDigits, maxDecimalDigits, this->isNegative);
}

LongNumber LongNumber::operator-(const LongNumber &other) const {
    if (this->isNegative != other.isNegative) {
        LongNumber copy = other;
        copy.isNegative = !copy.isNegative;
        return *this + copy;
    }

    LongNumber a = *this;
    LongNumber b = other;
    bool resultNegative = false;

    int maxDecimalDigits = std::max(a.numDecimalDigits, b.numDecimalDigits);
    a.digits.insert(a.digits.end(), maxDecimalDigits - a.numDecimalDigits, 0);
    b.digits.insert(b.digits.end(), maxDecimalDigits - b.numDecimalDigits, 0);

    if (a.digits.size() < b.digits.size()) {
        a.digits.insert(a.digits.begin(), b.digits.size() - a.digits.size(), 0);
    } else if (b.digits.size() < a.digits.size()) {
        b.digits.insert(b.digits.begin(), a.digits.size() - b.digits.size(), 0);
    }

    if (a.digits < b.digits) {
        std::swap(a.digits, b.digits);
        resultNegative = !a.isNegative;
    } else {
        resultNegative = a.isNegative;
    }

    std::vector<int8_t> resultDigits(a.digits.size(), 0);
    int8_t borrow = 0;

    for (int i = a.digits.size() - 1; i >= 0; i--) {
        int diff = a.digits[i] - b.digits[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultDigits[i] = diff;
    }

    while (resultDigits.size() > 1 && resultDigits[0] == 0) {
        resultDigits.erase(resultDigits.begin());
    }

    return LongNumber(resultDigits, maxDecimalDigits, resultNegative);
}
