#include <iostream>

long long MOD = 1e9 + 7;

long long handle_test_case(long long a, long long b)
{
    if (b == 0)
    {
        return 1;
    }

    long long res{1};
    long long base{a};
    while (b > 0)
    {
        // if the exponent is even, we square the base and half the exponent
        // if the exponent is odd, we multiply res by the current base

        if (b % 2 == 1)
        {
            res = (res * base) % MOD;
            b -= 1;
        }
        else
        {
            base = (base * base) % MOD;
            b >>= 1;
        }
    }

    return res;
}

int main()
{
    int t;
    std::cin >> t;

    while (t--)
    {
        long long a, b;
        std::cin >> a >> b;
        std::cout << handle_test_case(a, b) << std::endl;
    }
}