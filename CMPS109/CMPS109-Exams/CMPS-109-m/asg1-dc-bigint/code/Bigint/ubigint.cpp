
// James Garbagnati
// jgarbagn
// 1354722

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (unsigned long that) {
   do {
      this->ubig_value.push_back(that % 10);
      that = that / 10;
   } while(that > 0);
}

ubigint::ubigint (const string& that) {
   for (char digit: that) {
      auto itor = ubig_value.begin();
      ubig_value.insert(itor, digit - '0');
   }
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint output;
   int carry = 0;
   int this_size = ubig_value.size();
   int that_size = that.ubig_value.size();
   int size = (this_size > that_size)? 
                  this_size: that_size;
   
   for (int i = 0; i < size; ++i) {
      // Grab either the indexed digit or 0 if OOB
      int this_dig = (i < this_size)? 
                              ubig_value[i]: 0;
      int that_dig = (i < that_size)? 
                              that.ubig_value[i]: 0;
      int temp = this_dig + that_dig + carry;
      output.ubig_value.push_back(temp % 10);
      carry = temp / 10;
   }
   
   if (carry > 0) // So we don't have to trim things
      output.ubig_value.push_back(carry);
   
   return output;
}

ubigint ubigint::operator- (const ubigint& that) const {
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   ubigint output;
   int borrow = 0;
   int size = ubig_value.size();
   int that_size = that.ubig_value.size();
   
   for (int i = 0; i < size; ++i) {
      // Grab either the indexed digit or 0 if OOB
      int this_dig = ubig_value[i];
      int that_dig = (i < that_size)? 
                              that.ubig_value[i]: 0;
      int temp = this_dig - that_dig - borrow;
      output.ubig_value.push_back((temp < 0)? 
                                       temp + 10: temp);
      borrow = (temp < 0)? 1: 0;
   }
   
   output.trim();
   return output;
}

ubigint ubigint::operator* (const ubigint& that) const {
   ubigint output;
   int this_size = ubig_value.size();
   int that_size = that.ubig_value.size();
   output.ubig_value = vector<udigit_t>(this_size + that_size, 0);
   int carry;
   for (int i = 0; i < this_size; ++i) {
      carry = 0;
      for (int j = 0; j < that_size; ++j) {
         int temp = output.ubig_value[i+j] 
                  + (ubig_value[i] * that.ubig_value[j])
                  + carry;
         output.ubig_value[i+j] = temp % 10;
         carry = temp / 10;
      }
      output.ubig_value[i+that_size] = carry;
   }
   
   output.trim();
   return output;
}

void ubigint::multiply_by_2() {
   int carry = 0;
   int size = ubig_value.size();
   for (int i = 0; i < size; ++i) {
      int temp = ubig_value[i] * 2;
      ubig_value[i] = temp % 10 + carry;
      carry = temp / 10; // set the carry
   }
   if (carry > 0) // So we don't have to trim things
      ubig_value.push_back(carry);
}

void ubigint::divide_by_2() {
   int carry = 0;
   int size = ubig_value.size();
   for (int i = size - 1; i >= 0; --i) {
      int temp = ubig_value[i];
      ubig_value[i] = (carry + temp) / 2;
      carry = temp % 2 * 10;
   }
   
   this->trim();
}

ubigint::quot_rem ubigint::divide (const ubigint& that) const {
   static const ubigint zero = 0;
   if (that == zero) throw domain_error ("ubigint::divide: by 0");
   ubigint power_of_2 = 1;
   ubigint divisor = that; // right operand, divisor
   ubigint quotient = 0;
   ubigint remainder = *this; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (zero < power_of_2) {
      if (divisor < remainder || divisor == remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   
   quotient.trim();
   remainder.trim();
   return {quotient, remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return divide (that).first;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return divide (that).second;
}

bool ubigint::operator== (const ubigint& that) const {
   int size = ubig_value.size();
   int that_size = that.ubig_value.size();
   if (size != that_size)
      return false;
   for (int i = 0; i < size; ++i) {
      if (ubig_value[i] != that.ubig_value[i])
         return false;
   }
   return true;
}

bool ubigint::operator< (const ubigint& that) const {
   int size = ubig_value.size();
   int that_size = that.ubig_value.size();
   if (size != that_size) {
      if (size < that_size)
         return true;
      return false;
   }
   for (int i = size - 1; i >= 0; --i) {
      if (ubig_value[i] != that.ubig_value[i]) {
         if (ubig_value[i] < that.ubig_value[i])
            return true;
         return false;
      }
   }
   return false;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   for (int i = that.ubig_value.size() - 1; i >= 0; --i) {
      char temp = that.ubig_value[i] + '0';
      out << temp;
   }
   
   return out;
}

void ubigint::trim() {
   while(ubig_value.size() > 0 && ubig_value.back() == 0)
      ubig_value.pop_back();
   
   // Check if result is null and replace with 0.
   if (ubig_value.size() == 0)
      ubig_value.push_back(0);
}
