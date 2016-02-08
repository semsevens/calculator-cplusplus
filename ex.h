/*
* Definition of Ex class
*
* By semsevens
*
* Get the value of expression
*
*/

#ifndef EX_H_
#define EX_H_

// String class
class String
{
    private:
        char * pstr;
        int length;
        bool CheckPo(int po) const;    // check if the position is legal
        char * GetLine(std::istream & is, char ch = '\n', int len = 0);    // get a line of chars by recursion
    public:
        String(void);
        String(char ch);
        String(const char * ps);
        String(const String & st);
        ~String(void) { delete [] pstr; }
        String & operator=(const String & st);
        // get a char of target position
        char & operator[](int po);
        const char & operator[](int po) const;
        // connect two Strings
        String operator+(const String & st) const;
        String operator+(const char * ps) const;
        String operator+(char ch) const;
        friend String operator+(const char * ps, const String & st);
        friend String operator+(const char ch, const String & st);
        // input and output
        friend std::ostream & operator<<(std::ostream & os, const String & st);
        friend std::istream & operator>>(std::istream & is, String & st);
        // find the target char or String from position po
        // and return the fist position, if not find, return -1
        int find(const String & st, int po = 0) const;
        int find(const char * ps, int po = 0) const;
        int find(char ch, int po = 0) const;
        // find the char from first assignment
        // then store the char in the second assignment
        int orfind(const String & st, char & ch, int po = 0) const;
        int orfind(const char * ps, char & ch, int po = 0) const;
        // find target in reversed order,
        // if not find, return -1
        int rfind(const String & st, int po) const;
        int rfind(const char * ps, int po) const;
        int rfind(char ch, int po) const;
        // insert a char or String from position po
        String & insert(const String & st, int po = 0);
        String & insert(const char * ps, int po = 0);
        String & insert(char ch, int po = 0);
        // append a char or String to a String
        // in fact, it equals 'operator +''
        String & append(const String & st);
        String & append(const char * ps);
        String & append(char ch);
        // remove all char or String from a String begin with po
        String & remove(const String & st, int po = 0);
        String & remove(const char * ps, int po = 0);
        String & remove(char ch, int po = 0);
        String & remove(int poa, int pob);    // remove from position pa to pb
        // replace a part of String by a char or String
          // assign String
        String & replace(const String & sta, const String & stb, int po = 0);
        String & replace(const char * psa, const String & stb, int po = 0);
        String & replace(char ch, const String & stb, int po = 0);
          // assign char *
        String & replace(const String & sta, const char * psb, int po = 0);
        String & replace(const char * psa, const char * psb, int po = 0);
        String & replace(char ch, const char * psb, int po = 0);
          // assign char
        String & replace(const String & sta, char chb, int po = 0);
        String & replace(const char * psa, char chb, int po = 0);
        String & replace(char cha, char chb, int po = 0);
          // replace from position poa to pob
        String & replace(const String & sta, int poa, int pob);
        String & replace(const char * ps, int poa, int pob);
        String & replace(const char ch, int poa, int pob);
        // divide String, count store the number of parts after dividing
        String * divstr(const String & st, int po = 0, int count = 0) const;
        String * divstr(const char * ps, int po = 0, int count = 0) const;
        String * divstr(char ch, int po = 0, int count = 0) const;
        // other methods
        int len(void) const { return length; }
        double tod(void) const;    // double to string
        String child(int poa = 0, int pob = 0) const;    // return the String's child
        String findex(char ch, int po = 0) const;    // find target simple expression by ch, it can be one of "+*-/"
};
int ChToI(char ch);    // char to int
char NToCh(int n);    // number to char
double SToD(const String & s);    // String to double
String DToS(double d);    // double to string

// Expression class
class Ex
{
    private:
        String in;
        String out;
        bool Check(void) const;    // if input is illegal, return false
        bool Cal(void);    // calculate the expression by recursion
    public:
        Ex(const String & i) : in(i), out(i) { }
        String val(void);    // output the expression value
        String simple(String sim);    // calculate the simple expression by recursion
        String & compound(String & st);    // calculate the compound expression by recursion
        String & addsub(String & st);    // calculate all add and subtract
        String & muldiv(String & st);    // calculate all multiply and divide
        String & bracket(String & st);    // calculate all bracket
        String & stand(String & st);    // standardize the expression
};

#endif
