#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

// �����佺�׳׽��� ü(Sieve Of Eratosthenes)
vector<int> PrimeNumber_SieveOfEratosthenes(int n);
bool IsPrimeNumber(int n);

int main()
{
    int n = 100;

    printf("[Prime Number] - Sieve Of Eratosthenes : %d\n", n);
    {
        vector<int> result = PrimeNumber_SieveOfEratosthenes(n);

        // �Ҽ� ���
        for (int element : result)
        {
            printf("%d ", element);
        }

        printf("\n=> ���� : %d\n", result.size());
    }

    printf("\n");

    printf("[Prime Number?] : %d\n", n);
    {
        bool result = IsPrimeNumber(n);

        if (result)
        {
            printf("O\n");
        }
        else
        {
            printf("X\n");
        }
    }

    return 0;
}

// Time Complexity : O(sqrt(N))
// Space Complexity : O(N)
vector<int> PrimeNumber_SieveOfEratosthenes(int n)
{
    vector<int> result;

    vector<bool> isPrime(n + 1, true);

    isPrime[0] = false;
    isPrime[1] = false;

    int i = 2;

    // for (i = 2; i <= std::sqrt(n); i++)
    while (i * i <= n) // int �ִ� ���� (i * i)
    {
        if (isPrime[i])
        {
            int j = i * i;

            while (j <= n)
            {
                isPrime[j] = false;

                j += i;
            }
        }

        i++;
    }

    for (size_t i = 0; i < isPrime.size(); i++)
    {
        if (isPrime[i])
        {
            result.push_back(i);
        }
    }

    return result;
}

// Time Complexity : O(sqrt(N))
// Space Complexity : O(1)
bool IsPrimeNumber(int n)
{
    bool result = true;

    if (n >= 2)
    {
        int i = 2;

        // for (i = 2; i <= std::sqrt(n); i++)
        while (i * i <= n) // int �ִ� ���� (i * i)
        {
            if (n % i == 0)
            {
                result = false;
                break;
            }

            i++;
        }
    }

    // result == true : Prime Number
    // result == false : Composite Number

    return result;
}
