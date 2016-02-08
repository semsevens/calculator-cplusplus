/*
* Implement of Ex class
*
* By semsevens
*
* Get the value of expression
*
*/

#include <iostream>
#include <cstdlib>    // for exit()
#include <cstring>    // for strlen(). strcpy(), strncpy
#include <cmath>    // for pow()
#include "ex.h"
using std::cin;
using std::cout;
using std::endl;
const int PRECISION = 6;
const int numsize = 20;

// String class methods

// private methods
bool String::CheckPo(int po) const    // check if the position is legal
{
    if (po < 0 || po > length)
    {
        cout << "Insert error, the position is out of range: po="
             << po << endl;
        return false;
    } else
        return true;
}
char * String::GetLine(std::istream & is, char ch, int len)    // get a line of chars by recursion
{
    int length = len;
    char * pc = new char;    // new a temp char
    if (is.get(*pc) && *pc != ch)
    {
        char * ps = GetLine(is, ch, length + 1);    // recursion
        ps[length] = *pc;    // store temp char to the string
        delete pc;    // free temp char
        return ps;    // return the string address
    }
    else
    {
        char * ps = new char[length + 1];
        ps[length] = '\0';
        delete pc;    // free temp char
        return ps;    // return array address
    }
}
int ChToI(char ch)    // char to int
{
    int res = 0;
    switch (ch)
    {
        case '0':
            res = 0;
            break;
        case '1':
            res = 1;
            break;
        case '2':
            res = 2;
            break;
        case '3':
            res = 3;
            break;
        case '4':
            res = 4;
            break;
        case '5':
            res = 5;
            break;
        case '6':
            res = 6;
            break;
        case '7':
            res = 7;
            break;
        case '8':
            res = 8;
            break;
        case '9':
            res = 9;
            break;
        default:
            cout << "ChToI() error: " << ch << endl;
            exit(-1);    // stop the program
    }
    return res;
}
char NToCh(int n)    // number to char
{
    char res = '0';
    switch (n)
    {
        case 0:
            res = '0';
            break;
        case 1:
            res = '1';
            break;
        case 2:
            res = '2';
            break;
        case 3:
            res = '3';
            break;
        case 4:
            res = '4';
            break;
        case 5:
            res = '5';
            break;
        case 6:
            res = '6';
            break;
        case 7:
            res = '7';
            break;
        case 8:
            res = '8';
            break;
        case 9:
            res = '9';
            break;
        default:
            cout << "NToCh() error: " << n << endl;
            exit(-2);    // stop the program
    }
    return res;
}
double SToD(const String & s)    // String to double
{
    double res = 0;
    int indexpoint = -1;
    int i, j, k;
    int sign = 1;
    char num[numsize];
    char front = '\0';
    for (i = 0, j = 0; i < s.len(); i++)
    {
        if (isdigit(s[i]))    // deal with number
            num[j++] = s[i];
        else if (s[i] == '.' && indexpoint == -1 && isdigit(front))    // deal with point
        {
            num[j++] = s[i];
            indexpoint = j - 1;    // one double number can only have one point
        }
        else if (isdigit(front) || front == '.')    // deal with others and end reading
            break;
        if (s[i] == '-')    // deal with the minus
            sign *= -1;
        front = s[i];
    }
    num[j] = '\0';
    if (indexpoint == -1)
    {
        k = j - 1;
        for (i = k; i >= 0; i--)    // only integer part
        {
            res += pow(10, k - i) * ChToI(num[i]);
        }
    }
    else
    {
        k = indexpoint - 1;
        for (i = k; i >= 0; i--)    // integer part
        {
            res += pow(10, k - i) * ChToI(num[i]);
        }
        k = indexpoint + 1;
        for (i = k; i < j; i++)    // decimal part
        {
            res += pow(0.1, i + 1 - k) * ChToI(num[i]);
        }
    }
    res *= sign;
    return res;
}
String DToS(double d)    // double to string
{
    char num[numsize];
    int i, n, tempint;
    int count = 0;
    int integer = 0;
    int numbegin = 0;
    double decimal = 0;
    if (d < 0)
    {
        numbegin = 1;
        d = fabs(d);
        count++;
        num[0] = '-';
    }
    decimal = d - (tempint = integer = int(d));
    for (i = 1; tempint / 10 != 0; i++)    // get count
        tempint /= 10;
    count += i;
    for (i = count - 1; i >= numbegin; i--)    // integer part
    {
        n = integer % 10;
        num[i] = NToCh(n);
        integer /= 10;
    }
    if (decimal > 0)    // judge if it has decimal part
    {
        num[count] = '.';
        for (i = count + 1; i < count + 1 + PRECISION; i++)    // decimal part
        {
            decimal *= 10;
            n = int(decimal);
            num[i] = NToCh(n);
            decimal -= n;
        }
        num[i] = '\0';
    }
    else
        num[count] = '\0';
    return String(num);
}
// constructors
String::String(void)
{
    length = 0;
    pstr = new char[1];    // suit for delete []
    pstr[0] = '\0';
}
String::String(char ch)
{
    length = 1;
    pstr = new char[2];    // suit for delete []
    pstr[0] = ch;
    pstr[1] = '\0';
}
String::String(const char * ps)
{
    length = strlen(ps);
    pstr = new char[length + 1];
    strcpy(pstr, ps);
}
String::String(const String & st)
{
    length = st.length;
    pstr = new char[length + 1];
    strcpy(pstr, st.pstr);
}
String & String::operator=(const String & st)
{
    if (this == &st)
        return *this;    // in case assigning itself
    delete [] pstr;    // free old space
    length = st.length;
    pstr = new char[length + 1];
    strcpy(pstr, st.pstr);
    return *this;
}
// connect two Strings
String String::operator+(const String & st) const
{
    int len = length + st.length;
    char * pt = new char[len + 1];
    strcpy(pt, pstr);
    strcat(pt, st.pstr);
    String temp(pt);
    delete [] pt;
    return temp;
}
String String::operator+(const char * ps) const
{
    int len = length + strlen(ps);
    char * pt = new char[len + 1];
    strcpy(pt, pstr);
    strcat(pt, ps);
    String temp(pt);
    delete [] pt;
    return temp;
}
String String::operator+(const char ch) const
{
    int len = length + 1;
    char * pt = new char[len + 1];
    strcpy(pt, pstr);
    pt[len - 2] = ch;
    pt[len - 1] = '\0';
    String temp(pt);
    delete [] pt;
    return temp;
}
String operator+(const char * ps, const String & st)
{
    int len = st.length + strlen(ps);
    char * pt = new char[len + 1];
    strcpy(pt, ps);
    strcat(pt, st.pstr);
    String temp(pt);
    delete [] pt;
    return temp;
}
String operator+(const char ch, const String & st)
{
    int len = st.length + 1;
    char * pt = new char[len + 1];
    pt[0] = ch;
    pt[1] = '\0';
    strcat(pt, st.pstr);
    String temp(pt);
    delete [] pt;
    return temp;
}
// get a char of target position
char & String::operator[](int po)    // changeable version
{
    po = (po > 0 ? po : 0);
    po = (po < length ? po : length);
    return pstr[po];
}
const char & String::operator[](int po) const    // const version
{
    po = (po > 0 ? po : 0);
    po = (po < length ? po : length);
    return pstr[po];
}
// output
std::ostream & operator<<(std::ostream & os, const String & st)
{
    os << st.pstr;
    return os;
}
// input
std::istream & operator>>(std::istream & is, String & st)
{
    delete [] st.pstr;    // free old space
    st.pstr = st.GetLine(is);
    st.length = strlen(st.pstr);
    return is;
}
// find the target char or String from position po
// and return the fist position, if not find, return -1
int String::find(const String & st, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int slen = length - po;
    if (slen < st.length)    // target string is longer than source string
        return -1;
    bool flag = false;    // default is not find
    int res = -1;    // if not find, it will return -1
    int i, j, k;
    for (i = po; i < length; i++)
    {
        if (st.length > slen - i)    // speed finding rate
            break;
        if (st.pstr[0] = pstr[i])    // find the fist char position
        {
            for (j = 1; j < st.length; j++)
            {
                k = i + j;
                if (pstr[k] != st.pstr[j])
                    break;
            }
            if (j >= st.length )
            {
                res = i;
                flag = true;
            }
        }
        if (flag)    // find it
            break;
    }
    return res;
}
int String::find(const char * ps, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int slen = length - po;
    int tlen = strlen(ps);
    if (slen < tlen)    // target string is longer than source string
        return -1;
    bool flag = false;    // default is not find
    int res = -1;    // if not find, it will return -1
    int i, j, k;
    for (i = po; i < length; i++)
    {
        if (tlen > slen - i)    // speed finding rate
            break;
        if (ps[0] == pstr[i])    // find the fist char position
        {
            for (j = 1; j < tlen; j++)
            {
                k = i + j;
                if (pstr[k] != ps[j])
                    break;
            }
            if (j >= tlen)
            {
                res = i;
                flag = true;
            }
        }
        if (flag)    // find it
            break;
    }
    return res;
}
int String::find(char ch, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int res = -1;
    for (int i = po; i < length; i++)
    {
        if (ch == pstr[i])
        {
            res = i;
            break;
        }
    }
    return res;
}
// find the char from first assignment
// then store the char in the second assignment
int String::orfind(const String & st, char & ch, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int res = -1;
    ch = '\0';
    for (int j = po; j < length; j++)
    {
        for (int i = 0; i < st.length; i++)
        {
            if (st[i] == pstr[j])
            {
                res = j;
                ch = pstr[j];
                break;
            }
        }
        if (ch != '\0')
            break;
    }
    return res;
}
int String::orfind(const char * ps, char & ch, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int res = -1;
    ch = '\0';
    for (int j = po; j < length; j++)
    {
        for (int i = 0; i < strlen(ps); i++)
        {
            if (ps[i] == pstr[j])
            {
                res = j;
                ch = pstr[j];
                break;
            }
        }
        if (ch != '\0')
            break;
    }
    return res;
}
// find target in reversed order,
// if not find, return -1
int String::rfind(const String & st, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int slen = po + 1;
    if (slen < st.length)    // target string is longer than source string
        return -1;
    bool flag = false;    // default is not find
    int res = -1;    // if not find, it will return -1
    int i, j, k;
    for (i = po; i >= 0; i--)
    {
        if (st.length > i + 1)    // speed finding rate
            break;
        if (st.pstr[st.length - 1] = pstr[i])    // find the fist char position
        {
            for (k = i - 1, j = st.length - 2; j >= 0; k--, j--)
            {
                if (pstr[k] != st.pstr[j])
                    break;
            }
            if (j < 0)
            {
                res = i;
                flag = true;
            }
        }
        if (flag)    // find it
            break;
    }
    return res;
}
int String::rfind(const char * ps, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int slen = po + 1;
    int tlen = strlen(ps);
    if (slen < tlen)    // target string is longer than source string
        return -1;
    bool flag = false;    // default is not find
    int res = -1;    // if not find, it will return -1
    int i, j, k;
    for (i = po; i >= 0; i--)
    {
        if (tlen > i + 1)    // speed finding rate
            break;
        if (ps[tlen - 1] == pstr[i])    // find the fist char position
        {
            for (k = i - 1, j = tlen - 2; j >= 0; k--, j--)
            {
                if (pstr[k] != ps[j])
                    break;
            }
            if (j < 0)
            {
                res = i;
                flag = true;
            }
        }
        if (flag)    // find it
            break;
    }
    return res;
}
int String::rfind(char ch, int po) const
{
    if (!CheckPo(po))    // check po
        return -1;
    int res = -1;
    for (int i = po; i >= 0; i--)
    {
        if (ch == pstr[i])
        {
            res = i;
            break;
        }
    }
    return res;
}
// insert a char or String from position po
String & String::insert(const String & st, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    char * pa = new char[po + 1];    // get the front part
    strncpy(pa, pstr, po);
    pa[po] = '\0';
    char* pb = pstr + po;    // get the rear part
    *this = pa + st + pb;    // cat the three parts
    delete pa;    // free the temp space
    return *this;
}
String & String::insert(const char * ps, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    char * pa = new char[po + 1];    // get the front part
    strncpy(pa, pstr, po);
    pa[po] = '\0';
    char* pb = pstr + po;    // get the rear part
    *this = pa + String(ps) + pb;    // cat the three parts
    delete pa;    // free the temp space
    return *this;
}
String & String::insert(char ch, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    char * pa = new char[po + 1];    // get the front part
    strncpy(pa, pstr, po);
    pa[po] = '\0';
    char* pb = pstr + po;    // get the rear part
    *this = pa + String(ch) + pb;    // cat the three parts
    delete pa;    // free the temp space
    return *this;
}
// append a char or String to a String
// in fact, it equals 'operator +''
String & String::append(const String & st)
{
    *this = insert(st, length);
    return *this;
}
String & String::append(const char * ps)
{
    *this = insert(ps, length);
    return *this;
}
String & String::append(char ch)
{
    *this = insert(ch, length);
    return *this;
}
// remove all char or String from a String
String & String::remove(const String & st, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    while ((begin = find(st, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + st.length;    // get the rear part
        *this = String(pa) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::remove(const char * ps, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    while ((begin = find(ps, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + strlen(ps);    // get the rear part
        *this = String(pa) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::remove(char ch, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    while ((begin = find(ch, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + 1;    // get the rear part
        *this = String(pa) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::remove(int poa, int pob)    // remove from position poa to pob
{
    if (!CheckPo(poa) || !CheckPo(pob))    // check poa and pob
        return *this;
    if (poa > pob)    // make sure poa <= pob
    {
        int t;
        t = poa;
        poa = pob;
        pob = t;
    }
    char * pa = new char[poa + 1];    // get the front part
    strncpy(pa, pstr, poa);
    pa[poa] = '\0';
    char * pb = new char[length - pob];    // get the rear part
    strcpy(pb, pstr + pob + 1);
    *this = String(pa) + pb;    // cat the two parts
    delete pa;    // free the temp space
        delete pb;    // free the temp space
    return *this;
}
// replace a part of String by a char or String
  // assign String
String & String::replace(const String & sta, const String & stb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(sta, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + sta.length;    // get the rear part
        *this = pa + stb + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::replace(const char * psa, const String & stb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(psa, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + strlen(psa);    // get the rear part
        *this = pa + stb + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::replace(char ch, const String & stb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(ch, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + 1;    // get the rear part
        *this = pa + stb + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
  // assign char *
String & String::replace(const String & sta, const char * psb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(sta, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + sta.length;    // get the rear part
        *this = pa + String(psb) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::replace(const char * psa, const char * psb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(psa, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + strlen(psa);    // get the rear part
        *this = pa + String(psb) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::replace(char ch, const char * psb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(ch, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + 1;    // get the rear part
        *this = pa + String(psb) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
  // assign char
String & String::replace(const String & sta, char chb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(sta, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + sta.length;    // get the rear part
        *this = pa + String(chb) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::replace(const char * psa, char chb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(psa, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + strlen(psa);    // get the rear part
        *this = pa + String(chb) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
String & String::replace(char cha, char chb, int po)
{
    if (!CheckPo(po))    // check po
        return *this;
    int begin;
    if ((begin = find(cha, po)) != -1)
    {
        char * pa = new char[begin + 1];    // get the front part
        strncpy(pa, pstr, begin);
        pa[begin] = '\0';
        char* pb = pstr + begin + 1;    // get the rear part
        *this = pa + String(chb) + pb;    // cat the two parts
        delete pa;    // free the temp space
    }
    return *this;
}
  // replace from position poa to pob
String & String::replace(const String & sta, int poa, int pob)
{
    if (!CheckPo(poa) || !CheckPo(pob))    // check poa and pob
        return *this;
    if (poa > pob)    // make sure poa <= pob
    {
        int t;
        t = poa;
        poa = pob;
        pob = t;
    }
    char * pa = new char[poa + 1];    // get the front part
    strncpy(pa, pstr, poa);
    pa[poa] = '\0';
    char * pb = new char[length - pob];    // get the rear part
    strcpy(pb, pstr + pob + 1);
    *this = pa + sta + pb;    // cat the two parts
    delete pa;    // free the temp space
    delete pb;    // free the temp space
    return *this;
}
String & String::replace(const char * ps, int poa, int pob)
{
    if (!CheckPo(poa) || !CheckPo(pob))    // check poa and pob
        return *this;
    if (poa > pob)    // make sure poa <= pob
    {
        int t;
        t = poa;
        poa = pob;
        pob = t;
    }
    char * pa = new char[poa + 1];    // get the front part
    strncpy(pa, pstr, poa);
    pa[poa] = '\0';
    char * pb = new char[length - pob];    // get the rear part
    strcpy(pb, pstr + pob + 1);
    *this = pa + String(ps) + pb;    // cat the two parts
    delete pa;    // free the temp space
    delete pb;    // free the temp space
    return *this;
}
String & String::replace(const char ch, int poa, int pob)
{
    if (!CheckPo(poa) || !CheckPo(pob))    // check poa and pob
        return *this;
    if (poa > pob)    // make sure poa <= pob
    {
        int t;
        t = poa;
        poa = pob;
        pob = t;
    }
    char * pa = new char[poa + 1];    // get the front part
    strncpy(pa, pstr, poa);
    pa[poa] = '\0';
    char * pb = new char[length - pob];    // get the rear part
    strcpy(pb, pstr + pob + 1);
    *this = pa + String(ch) + pb;    // cat the two parts
    delete pa;    // free the temp space
    delete pb;    // free the temp space
    return *this;
}
// divide String from position po, count store the number of parts after dividing
// notice: count is from 1 to ...
// use the return value like '(*res)[index]'
String * String::divstr(const String & st, int po, int count) const
{
    if (!CheckPo(po))    // check po
        return NULL;
    String * res;
    int breakpoint;
    if ((breakpoint = find(st, po)) != -1)
    {
        String * res = new String[2];    // create the space to Strings
        int frontlen = breakpoint + 1;
        int middlelen = st.len();
        int rearlen = length - breakpoint - middlelen;
        char * front = new char[frontlen + 1];
        char * rear = new char[rearlen + 1];
        strncpy(front, pstr, frontlen);
        strncpy(rear, pstr + breakpoint + middlelen, rearlen);
        front[frontlen] = '\0';
        rear[rearlen] = '\0';
        res[0] = String(front);
        res[1] = String(rear);
        delete front;
        delete rear;
        return res;
    }
    else
        return NULL;
}
String * String::divstr(const char * ps, int count, int po) const
{
    if (!CheckPo(po))    // check po
        return NULL;
    int breakpoint;
    if ((breakpoint = find(ps, po)) != -1)
    {
        String * res = new String[2];    // create the space to Strings
        int frontlen = breakpoint + 1;
        int middlelen = strlen(ps);
        int rearlen = length - breakpoint - middlelen;
        char * front = new char[frontlen + 1];
        char * rear = new char[rearlen + 1];
        strncpy(front, pstr, frontlen);
        strncpy(rear, pstr + breakpoint + middlelen, rearlen);
        front[frontlen] = '\0';
        rear[rearlen] = '\0';
        res[0] = String(front);
        res[1] = String(rear);
        delete front;
        delete rear;
        return res;
    }
    else
        return NULL;
}
String * String::divstr(char ch, int po, int count) const
{
    if (!CheckPo(po))    // check po
        return NULL;
    int breakpoint;
    if ((breakpoint = find(ch, po)) != -1)
    {
        String * res = new String[2];    // create the space to Strings
        int frontlen = breakpoint + 1;
        int middlelen = 1;
        int rearlen = length - breakpoint - middlelen;
        char * front = new char[frontlen + 1];
        char * rear = new char[rearlen + 1];
        strncpy(front, pstr, frontlen);
        strncpy(rear, pstr + breakpoint + middlelen, rearlen);
        front[frontlen] = '\0';
        rear[rearlen] = '\0';
        res[0] = String(front);
        res[1] = String(rear);
        delete front;
        delete rear;
        return res;
    }
    else
        return NULL;
}
// other methods
double String::tod(void) const    // double to string
{
    return SToD(*this);
}
String String::child(int poa, int pob) const    // return the String's child
{
    if (!CheckPo(poa) || !CheckPo(pob))    // check poa and pob
        return *this;
    if (poa > pob)    // make sure poa <= pob
    {
        int t;
        t = poa;
        poa = pob;
        pob = t;
    }
    int len = pob - poa + 1;
    char * ps = new char[len + 1];
    strncpy(ps, pstr + poa, len);
    ps[len] = '\0';
    String temp(ps);
    delete ps;    // free temp space
    return temp;
}
String String::findex(char ch, int po) const    // find target simple expression by ch, it can be one of "+*-/"
{
    String temp;
    bool flag = false;
    int index, i, j;
    if ((index = find(ch, po)) != -1)
    {
        for (i = index - 1; i >= 0 && (isdigit(pstr[i]) || pstr[i] == '.' || pstr[i] == '-'); i--)    // find the first position
        {
            if (pstr[i] == '-' && i > 0 && (isdigit(pstr[i - 1]) || pstr[i - 1] == '.'))    // in case 1--6+1
                break;
        }
        for (j = index + 1; j < length && (isdigit(pstr[j]) || pstr[j] == '.' || pstr[j] == '-'); j++)    // find the end position
        {
            if (pstr[j] == '-' && j > 0 && (isdigit(pstr[j - 1]) || pstr[j - 1] == '.'))    // in case 1--6+1
                break;
        }
        if (i < index - 1 && j > index + 1)
            flag = true;
    }
    if (flag)
        temp = child(i + 1, j - 1);
    return temp;
}
// Ex class methods
bool Ex::Check(void) const    // if input is illegal, return false
{
    return true;
}
String & Ex::stand(String & st)    // standardize the expression
{
    int index = 0;
    int po = 0;
    // deal with like 3(1+1)2(1-8)(1+1)
    while ((index = st.find('(', po)) != -1)
    {
        if (index > 0 && isdigit(st[index - 1]))
        {
            st.replace("*(", index, index);
            po = index + 2;
        }
        else
            po = index + 1;
    }
    po = 0;
    while ((index = st.find(')', po)) != -1)
    {
        if (index < st.len() && isdigit(st[index + 1]))
        {
            st.replace(")*", index, index);
            po = index + 2;
        }
        else
            po = index + 1;
    }
    while ((index = st.find(")(") != -1))
        st.replace(")(", ")*(");
    return st;
}

String  Ex::simple(String  sim)    // calculate the expression by recursion
{
    String temp;
    int index, count;
    char ch;
    int len = sim.len();
    int numbegin = 0;
    for (int i = 0; i < len; i++)    // skip minus
    {
        if (isdigit(sim[i]))
        {
            numbegin = i;
            break;
        }
    }
    if ((index = sim.orfind("+*-/", ch, numbegin)) == -1)
        return sim;
    else
    {
        String * res = sim.divstr(ch, numbegin);
        double a = res[0].tod();
        double b = res[1].tod();
        delete [] res;
        double r;
        switch (ch)
        {
        case '+':
            r = a + b;
            break;
        case '-':
            r = a - b;
            break;
        case '*':
            r = a * b;
            break;
        case '/':
            r = a / b;
            break;
        default:
            cout << "operator error, ch: " << ch << endl;
            exit(1);
        }
        temp = DToS(r);
        return temp;
    }
}
String Ex::val(void)    // output the expression value
{
    Check();
    stand(out);
    cout << out;
    bracket(out);
    compound(out);
    return out;
}

String & Ex::compound(String & st)    // calculate the compound expression by recursion
{
    muldiv(st);
    addsub(st);
    return st;
}
String & Ex::addsub(String & st)    // calculate all add and subtract
{
    char ch;
    String temp;
    String val;
    int numbegin = 0;
    for (int i = 0; i < st.len(); i++)    // skip minus
    {
        if (isdigit(st[i]))
        {
            numbegin = i;
            break;
        }
    }
    while (st.orfind("+-", ch, numbegin) > 0)
    {
        if (ch == '+' && (temp = st.findex('+', numbegin)).len() > 0)
            ;
        else if (ch == '-' && (temp = st.findex('-', numbegin)).len() > 0)
            ;
        else
            break;
        val = simple(temp);
        st.replace(temp, val);
        numbegin = 0;    // update
        for (int i = 0; i < st.len(); i++)    // skip minus
        {
            if (isdigit(st[i]))
            {
                numbegin = i;
                break;
            }
        }
    }
    return st;
}
String & Ex::muldiv(String & st)    // calculate all multiply and divide
{
    char ch;
    String temp;
    String val;
    while (st.orfind("*/", ch) > 0)
    {
        if (ch == '*' && (temp = st.findex('*')).len() > 0)
            ;
        else if (ch == '/' && (temp = st.findex('/')).len() > 0)
            ;
        else
            break;
        val = simple(temp);
        st.replace(temp, val);
    }
    return st;
}
String & Ex::bracket(String & st)    // calculate all bracket
{
    int leftindex;
    int rightindex;
    while ((leftindex = st.rfind('(', st.len() - 1)) != -1 && (rightindex = st.find(')', leftindex + 1)) != -1 )
    {
        String target = st.child(leftindex + 1, rightindex - 1);
        String val = compound(target);
        st.replace(val, leftindex, rightindex);
    }
    return st;
}
