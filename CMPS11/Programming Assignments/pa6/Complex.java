//-----------------------------------------------------------------------------
//
//   Complex.java
//   Seongwoo Choi
//   scho29
//   pa6
//   Represents complex numbers as a pair of doubles
//-----------------------------------------------------------------------------

class Complex{

   //--------------------------------------------------------------------------
   // Private Data Fields 
   //--------------------------------------------------------------------------
   private double re;
   private double im;
   private double[] parse;
   
   //--------------------------------------------------------------------------
   // Public Constant Fields 
   //--------------------------------------------------------------------------
   public static final Complex ONE = Complex.valueOf(1,0);
   public static final Complex ZERO = Complex.valueOf(0,0);
   public static final Complex I = Complex.valueOf(0,1);

   //--------------------------------------------------------------------------
   // Constructors 
   //--------------------------------------------------------------------------
   Complex(double a, double b){
      this.re = a;
      this.im = b;
   }

   Complex(double a){
      this.re = a;
      this.im = 0;
   }

   Complex(String s){
      parse = parseComplex(s);
      this.re = parse[0];
      this.im = parse[1];
   }
   
   static double[] parseComplex(String str){
      double[] part = new double[2];
      String s = str.trim();
      String NUM = "(\\d+\\.\\d*|\\.?\\d+)";
      String SGN = "[+-]?";
      String OP =  "\\s*[+-]\\s*";
      String I =   "i";
      String OR =  "|";
      String REAL = SGN+NUM;
      String IMAG = SGN+NUM+"?"+I;
      String COMP = REAL+OR+
                    IMAG+OR+
                    REAL+OP+NUM+"?"+I;
      
      if( !s.matches(COMP) ){
         throw new NumberFormatException(
                   "Cannot parse input string \""+s+"\" as Complex");
      }
      s = s.replaceAll("\\s","");     
      if( s.matches(REAL) ){
         part[0] = Double.parseDouble(s);
         part[1] = 0;
      }else if( s.matches(SGN+I) ){
         part[0] = 0;
         part[1] = Double.parseDouble( s.replace( I, "1.0" ) );
      }else if( s.matches(IMAG) ){
         part[0] = 0;
         part[1] = Double.parseDouble( s.replace( I , "" ) );
      }else if( s.matches(REAL+OP+I) ){
         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+")"+OP+".+" , "$1" ) );
         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+")"+I , "$1"+"1.0" ) );
      }else{   //  s.matches(REAL+OP+NUM+I) 
         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+").+"  , "$1" ) );
         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+NUM+")"+I , "$1" ) );
      }
      return part;
   }

   //---------------------------------------------------------------------------
   // Public methods 
   //---------------------------------------------------------------------------

   // Complex arithmetic -------------------------------------------------------

   // copy()
   // Return a new Complex equal to this Complex
   Complex copy(){
      Complex co = new Complex(this.re, this.im);
      return co; 
   }
   
   // add()
   // Return a new Complex representing the sum this plus z.
   Complex add(Complex z){
      double x = (this.re + z.re);
      double y = (this.im + z.im);
      Complex sum = new Complex(x,y);
      return sum; 
   }
   
   // negate()
   // Return a new Complex representing the negative of this.
   Complex negate(){
      double x = -this.re;
      double y = -this.im;
      Complex neg = new Complex(x,y);
      return neg;      
   }

   // sub()
   // Return a new Complex representing the difference this minus z.
   Complex sub(Complex z){
      double x = this.re -z.re;
      double y = this.im -z.im;
      Complex subtract = new Complex(x,y);
      return subtract; 
   }

   // mult()
   // Return a new Complex representing the product this times z.
   Complex mult(Complex z){
      double x = ((this.re * z.re) - (this.im * z.im));
      double y = ((this.re * z.im) + (this.im * z.re));
      Complex multiply = new Complex(x, y);
      return multiply;
   }

   // recip()
   // Return a new Complex representing the reciprocal of this.
   // Throw an ArithmeticException with appropriate message if 
   // this.equals(Complex.ZERO).
   Complex recip(){
      if(this.equals(Complex.ZERO)){
         throw new ArithmeticException("Cannot divide by zero.");
      }else{
         double x = (this.re/(Math.pow(this.re, 2)+(Math.pow(this.im, 2))));
         double y = (-this.im/(Math.pow(this.re, 2)+(Math.pow(this.im,2))));
         Complex reciprocal = new Complex(x, y);
         return reciprocal;
      }
   }

   // div()
   // Return a new Complex representing the quotient of this by z.
   // Throw an ArithmeticException with appropriate message if 
   // z.equals(Complex.ZERO).
   Complex div(Complex z){
      if(z.equals(Complex.ZERO)){
         throw new ArithmeticException("Cannot divide by zero.");
      }else{
         double a = z.re;
         double b = z.im;
         double c = this.re;
         double d = this.im;
         double x = ((a*c)+(b*d))/(Math.pow(a,2)+Math.pow(b,2));
         double y = ((a*d)-(b*c))/(Math.pow(a,2)+Math.pow(b,2));
         Complex divide = new Complex(x,y);
         return divide;
      }
   }

   // conj()
   // Return a new Complex representing the conjugate of this Complex.
   Complex conj(){
      double x = this.im*-1;
      Complex conjugate = new Complex(this.re, x);
      return conjugate; 
   }
   
   // Re()
   // Return the real part of this.
   double Re(){
      return re;
   }

   // Im()
   // Return the imaginary part of this.
   double Im(){
      return im;
   }

   // abs()
   // Return the modulus of this Complex, i.e. the distance between 
   // points (0, 0) and (re, im).
   double abs(){
      return Math.hypot(this.re, this.im); 
   }

   // arg()
   // Return the argument of this Complex, i.e. the angle this Complex
   // makes with positive real axis.
   double arg(){
      return Math.atan2(im, re);
   }

   // Other functions ---------------------------------------------------------
   
   // toString()
   // Return a String representation of this Complex.
   // The String returned will be readable by the constructor Complex(String s)
   public String toString(){
      String str = "";   
      if(re<0){
         str += String.valueOf(this.re);
      }else if (re == 0){
         str += "";
      }else{
         str += String.valueOf(this.re);
      }
      if(im<0){
         str += String.valueOf(this.im) + "i";
      }else if (im == 0){
         str += "";
      }else if (re != 0){
         str += "+" + String.valueOf(this.im) + "i";
      }else{
         str += String.valueOf(this.im) +"i";
      }
      return str;
   }

   // equals()
   // Return true iff this and obj have the same real and imaginary parts.
   public boolean equals(Object obj){
      Complex temp = (Complex)obj;
      if (temp.re == this.re && temp.im == this.im){
         return true;
      }
      return false; 
   }

   // valueOf()
   // Return a new Complex with real part a and imaginary part b.
   static Complex valueOf(double a, double b){
      Complex ab = new Complex(a,b);
      return ab; 
   }

   // valueOf()
   // Return a new Complex with real part a and imaginary part 0.
   static Complex valueOf(double a){
      Complex va = new Complex(a,0);
      return va; 
   }

   // valueOf()
   // Return a new Complex constructed from s.
   static Complex valueOf(String s){
      Complex vs = new Complex(s);
      return vs; 
   }

}
