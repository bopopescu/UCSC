/*
* Seongwoo Choi
* scho29@ucsc.edu
*/

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
   
   if (uvalue == 0)
      is_negative = false;
}

bigint bigint::operator+() const {
   return *this;
}

bigint bigint::operator-() const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
   bigint result;
   // If they're different signs
   if (is_negative != that.is_negative) {
      if (uvalue < that.uvalue) {
         result = bigint(that.uvalue - uvalue, that.is_negative);
      } else {
         result = bigint(uvalue - that.uvalue, is_negative);
      }
   } else {
      // If they're the same sign
      result = bigint(uvalue + that.uvalue, is_negative);
   }
   if (result == 0) {
      result.is_negative = false;
   }
   return result;
}

//the code checks the values of the user input and the signs. 
bigint bigint::operator- (const bigint& that) const {
   bigint result;
   // If they're the same sign
   if (is_negative == that.is_negative) {
      if (uvalue < that.uvalue) {
         result = bigint(that.uvalue - uvalue, !is_negative);
      } else {
         result = bigint(uvalue - that.uvalue, is_negative);
      }
   } else {
      // If they're different signs
      result = bigint(uvalue + that.uvalue, is_negative);
   }
   if (result == 0) {
      result.is_negative = false;
   }
   return result;
}

//multiplication is easy since it multiplies two numbers. 
bigint bigint::operator* (const bigint& that) const {
   bigint result = uvalue * that.uvalue;
   if (is_negative == that.is_negative)
      result.is_negative = false;
   else
      result.is_negative = true;
      
   if (result == 0)
      result.is_negative = false;
   return result;
}

//uses to divide two numbers input from the user.
//also the code operator/ code is already given. 
bigint bigint::operator/ (const bigint& that) const {
   bigint result = uvalue / that.uvalue;
   if (is_negative == that.is_negative)
      result.is_negative = false;
   else
      result.is_negative = true;
   
   if (result == 0)
      result.is_negative = false;
   return result;
}
 
bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   result.is_negative = that.is_negative;
   
   if (result == 0)
      result.is_negative = false;
   return result;
}

//we do not need to modify this
bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

//we do not need to modify this
bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? that.uvalue < uvalue
                      : uvalue < that.uvalue;
}

//we do not need to modify this
ostream& operator<< (ostream& out, const bigint& that) {
   return out << (that.is_negative ? "-" : "")
              << that.uvalue;
}

