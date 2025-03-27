#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <exception>
#include <sstream>

class LongNumber {
    private:
      std::vector<int8_t> digits;
      int numDecimalDigits;
      bool isNegative;

      void populateWithString(const std::string &str);
      
    public:
        LongNumber();
        LongNumber(const std::vector<int8_t> &digits, int numDecimalDigits=0, bool isNegative=false);
        LongNumber(const std::string &str);
        
        std::string str() const ;
        
        LongNumber operator -() const;
        
        LongNumber operator+(const LongNumber& obj) const ;
        LongNumber operator-(const LongNumber& obj) const ;
        LongNumber operator*(const LongNumber& obj) const ;
        LongNumber operator/(const LongNumber& obj) const ;
        
        bool operator !=(LongNumber const& obj) const ;
        
        bool operator ==(LongNumber const& obj) const ;
        bool operator >(LongNumber const& obj) const ;
        bool operator <(LongNumber const& obj) const ;
        bool operator >=(LongNumber const& obj) const ;
        bool operator <=(LongNumber const& obj) const ;
        
    
        friend std::ostream& operator<<(std::ostream& os, const LongNumber& num) ;
        friend std::istream& operator>>(std::istream& is, LongNumber& num);
  };
  
  
