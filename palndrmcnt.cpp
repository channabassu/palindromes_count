

#include <iostream>
#include<math.h>
#include<algorithm>

using namespace std;

struct num_status
{
    long long base_num;
    int digits;
    bool inclusive;
};


long long num_with_digits(int digits, bool sml0grt1)
{
    if (!sml0grt1)
        return (long long)pow(10, digits - 1);
    long long num = 9;
    for (int i = 1; i < digits; i++)
        num = num * 10 + 9;
    return num;
}


num_status return_status(long long num,bool sml0grt1)
{
    long long copy = num, rev = 0;
    int digits = 0;
    long long temp = 0;
    bool inclusive = 0;

    while (copy >(long long) 0)
    {
        temp =(copy % 10);
        rev = rev * 10 + temp;
        copy = copy / 10;
        digits++;
    }

    long long num_lastdig = 0, rev_lastdig = 0;
    num_lastdig = num % num_with_digits((digits % 2 == 0) ? (digits / 2) + 1 : (digits + 1) / 2, 0);
    rev_lastdig = rev % num_with_digits((digits % 2 == 0) ? (digits / 2) + 1 : (digits + 1) / 2, 0);
    
    if (num_lastdig == rev_lastdig)
        inclusive = 1;
    else if (!sml0grt1 && rev_lastdig > num_lastdig)
        inclusive = 1;
    else if (sml0grt1 && num_lastdig > rev_lastdig)
        inclusive = 1;

    num_status status;
    status.base_num = num / num_with_digits((digits % 2 == 0) ? (digits / 2) + 1 : (digits + 1) / 2, 0);
    status.digits = digits;
    status.inclusive = inclusive;

    return status;
}

int plndrms_inbtwn(long long a, long long b)
{
    if (a >= b)
        return 0;

    int palindromes = 0;

    num_status small = return_status(a, 0);
    num_status great = return_status(b, 1);
    cout << small.base_num << " " << small.digits << " " << small.inclusive << "\n" << great.base_num << " " << great.digits << " " << great.inclusive<<"\n";

    if (small.digits == great.digits)
    {
        palindromes = great.base_num - small.base_num;

        if (small.inclusive && great.inclusive)
            palindromes++;
        else if (!small.inclusive && !great.inclusive)
            palindromes--;

        return palindromes;
    }

    palindromes += (int)(num_with_digits((small.digits % 2 == 0) ? (small.digits / 2) : (small.digits + 1) / 2, 1) - small.base_num) + (int)small.inclusive;
    palindromes += (int)(great.base_num - num_with_digits((great.digits % 2 == 0) ? (great.digits / 2) : (great.digits + 1) / 2, 0)) + (int)great.inclusive;

    int i = small.digits + 1;
    while (i < great.digits)
    {
        palindromes += 9 * pow(10, (i % 2 == 0) ? (i / 2) - 1 : ((i + 1) / 2) - 1);
        i++;
    }

    return palindromes;
}

string mathop(string a, string b, bool add0sub1, int arg)
{
    string result="";
    int lena = a.length()-1;
    int lenb = b.length()-1;
    int carry = arg;
    int borrow = arg * (-1);

    char opa = 0, opb = 0, res = 0;
    if (add0sub1)
    {
        while (lena >= 0)
        {
            if (lenb >= 0)
                opb = (b[lenb] - '0') + borrow;
            else opb = borrow;

            borrow = 0;
            opa = (a[lena] - '0');
            if (opb > opa)
            {
                opa += 10;
                borrow = 1;
            }
            res = opa - opb;
            //result = string(res+'0',1) + result;
            result.push_back((char)('0' + res));
            lena--;
            lenb--;
        }
        reverse(result.begin(), result.end());
        int i = 0;
        for (i = 0; result[i] == '0'; i++) {  }
        result = result.substr(i);
        return result;
    }
    //char temp = 0;

    while (lena >= 0||lenb>=0)
    {
        if (lenb >= 0)
            opb = b[lenb] - '0';
        else opb = 0;
        if (lena >= 0)
            opa = a[lena] - '0';
        else opa = 0;

        res = opa + opb + carry;

        //temp = (char)((res % 10) + '0');
        /*
        if (temp > '9' || temp < '0')
            cout << "non printable ";
        else cout << temp;
        */

        //result = string((char)(res % 10 + '0'), 1) + result;
        result.push_back((char)(res % 10 + '0'));
        carry = res / 10;

        lena--;
        lenb--;
    }
    //cout << (char)(carry+'0');
    if (carry > 0)
    { //result = string((char)('0' + carry), 1) + result;
        result.push_back((char)(carry + '0'));
    }

    reverse(result.begin(), result.end());
    return result;
}

string palindromesbelow(string num)
{
    int len = num.length();

    if (len == 1)
    {
        num[0] -= 1;
        return num;
    }

    bool inclusive = 0;
    int mid_right = 0, mid_left = 0;
    if (len % 2 == 0)
    {
        mid_right = len / 2; mid_left = mid_right - 1;
    }
    else 
    {
        mid_right = (len / 2) + 1; mid_left = (len / 2) - 1;
    }
    while (mid_right < len && mid_left >= 0)
    {
        if (num[mid_right++] > num[mid_left--])
        {
            inclusive = 1;
            break;
        }
    }

    int base_len = (len + len % 2) / 2;
    string base_num = num.substr(0, base_len);
    //string plndrms = "1" + string('9', (len - len % 2) / 2) + "8";
    string plndrms = "1";
    for (int i = 0; i < ((len - len % 2) / 2)-1; i++)
        plndrms += "9";
    plndrms += "8";

    if (len % 2 == 1)
    {
        base_num[0] -= 1;
        return mathop(plndrms, base_num, 0,(int)inclusive );
    }
    string str = "";
    for (int i = 0; i < (base_len); i++)
        str += "9";
    base_num = mathop(str, base_num, 1,(int)inclusive);
    return mathop(plndrms, base_num, 1, 0);
}

int main()
{
    cout << plndrms_inbtwn(12345678, 234567890123);
    cout << "\n" << mathop(palindromesbelow("234567890123"), palindromesbelow("12345678"), 1, 0);
    return 0;
}
//cout << mathop(palindromesbelow("234567890123"), palindromesbelow("12345678"),1,0);
//cout << plndrms_inbtwn(12345678, 234567890123);

    