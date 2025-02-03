#include <bits/stdc++.h>
using namespace std;

string addLargeNumbers(string s1, string s2)
{
    // make sure s1 >= s2
    if (s2.length() > s1.length())
        swap(s1, s2);
    string res = "";
    int n1 = s1.size(), n2 = s2.size(), carry = 0;
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    for (int i = 0; i < n2; i++)
    {
        int sum = (s1[i] - '0') + (s2[i] - '0') + carry;
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    for (int i = n2; i < n1; i++)
    {
        int sum = carry + (s1[i] - '0');
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    if (carry)
        res.push_back(carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

string multiplyLargeNumbers(string a, string b)
{
    if (a == "0" || b == "0")
        return "0";
    int m = a.size() - 1, n = b.size() - 1, carry = 0;
    string product;
    for (int i = 0; i <= m + n || carry; i++)
    {
        for (int j = max(0, i - n); j <= min(i, m); j++)
            carry += (a[m - j] - '0') * (b[n - i + j] - '0');
        product += carry % 10 + '0';
        carry /= 10;
    }
    reverse(begin(product), end(product));
    return product;
}

bool isGreaterOrEqual(const string &a, const string &b)
{
    if (a.length() != b.length())
        return a.length() > b.length();
    return a >= b;
}

string subtractLargeNumbers(const string &a, const string &b)
{
    string result;
    int borrow = 0;
    int i = a.length() - 1, j = b.length() - 1;
    while (i >= 0 || j >= 0)
    {
        int x = i >= 0 ? a[i] - '0' : 0;
        int y = j >= 0 ? b[j] - '0' : 0;
        int diff = x - y - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        result.push_back(diff + '0');
        i--;
        j--;
    }
    reverse(result.begin(), result.end());
    result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
    return result;
}

string divideLargeNumbers(string s1, string s2)
{
    string ans;
    string temp;

    for (char digit : s1)
    {
        temp += digit;
        temp.erase(0, min(temp.find_first_not_of('0'), temp.size() - 1));
        if (temp.empty())
            temp = "0";

        int count = 0;
        while (isGreaterOrEqual(temp, s2))
        {
            temp = subtractLargeNumbers(temp, s2);
            count++;
        }
        ans += to_string(count);
    }
    ans.erase(0, min(ans.find_first_not_of('0'), ans.size() - 1));
    if (ans.empty())
        return "0";
    return ans;
}

string nthFibonacci(string s)
{
    string a = "1", b = "1", c;
    if (s == "1")
        return a;
    if (s == "2")
        return b;
    s = subtractLargeNumbers(s, "1");
    while (s != "0")
    {
        s = subtractLargeNumbers(s, "1");
        c = addLargeNumbers(a, b);
        b = a;
        a = c;
    }
    return b;
}

string nthFactorial(string s)
{
    if (s == "0" || s == "1")
        return "1";
    string res = "1";
    while (s != "1")
    {
        res = multiplyLargeNumbers(res, s);
        s = subtractLargeNumbers(s, "1");
    }
    return res;
}

string nthCatalan(string s)
{
    if (s == "1")
        return "1";
    string temp = s, den = "1", num = "1";
    while (temp != "1")
    {
        den = multiplyLargeNumbers(den, temp);
        temp = subtractLargeNumbers(temp, "1");
    }
    temp = addLargeNumbers(s, "2");
    string last = multiplyLargeNumbers(s, "2");
    last = addLargeNumbers(last, "1");
    while (temp != last)
    {
        num = multiplyLargeNumbers(num, temp);
        temp = addLargeNumbers(temp, "1");
    }
    return divideLargeNumbers(num, den);
}

int main()
{
    string first = "100000000";
    string second = "99";
    string addResult = addLargeNumbers(first, second);
    string multiplyResult = multiplyLargeNumbers(first, second);
    string subtractResult = subtractLargeNumbers(first, second);
    string divideResult = divideLargeNumbers(first, second);
    string nthFibonacciResult = nthFibonacci(second);
    string nthFactorialResult = nthFactorial(second);
    string nthCatalanResult = nthCatalan(second);
    cout << "Result after adding first and second : " << addResult << "\n";
    cout << "Result after subtracting first and second : " << subtractResult << "\n";
    cout << "Result after multiplying first and second : " << multiplyResult << "\n";
    cout << "Result after dividing first and second : " << divideResult << "\n";
    cout << second << "th Fibonacci Number is : " << nthFibonacciResult << "\n";
    cout << second << "th Factorial is : " << nthFactorialResult << "\n";
    cout << second << "th Catalan Number is : " << nthCatalanResult << "\n";
}
